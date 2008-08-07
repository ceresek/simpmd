/*

SIM_PROCESSOR.C

Copyright 2008 Petr Tuma

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

*/

#include <iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_endian.h>

#include "sim_common.h"


//--------------------------------------------------------------------------
// Processor Status Variables

// Registers

// The registers are stored in unions that allow
// access to the two individual bytes as well
// as to the combined word ...

#if SDL_BYTEORDER == SDL_LIL_ENDIAN
#  define RegisterPairStruct(H,L) struct { byte L; byte H; }
#endif

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#  define RegisterPairStruct(H,L) struct { byte H; byte L; }
#endif

#define RegisterPairUnion(H,L) union { word Pair; RegisterPairStruct (H,L) One; } RegisterPair##H##L

static RegisterPairUnion (A,F);
static RegisterPairUnion (B,C);
static RegisterPairUnion (D,E);
static RegisterPairUnion (H,L);

#define RegAF (RegisterPairAF.Pair)
#define RegBC (RegisterPairBC.Pair)
#define RegDE (RegisterPairDE.Pair)
#define RegHL (RegisterPairHL.Pair)

#define RegA (RegisterPairAF.One.A)
#define RegF (RegisterPairAF.One.F)
#define RegB (RegisterPairBC.One.B)
#define RegC (RegisterPairBC.One.C)
#define RegD (RegisterPairDE.One.D)
#define RegE (RegisterPairDE.One.E)
#define RegH (RegisterPairHL.One.H)
#define RegL (RegisterPairHL.One.L)

static word RegPC;
static word RegSP;

// Individual flag variables, kept because it is easier to
// manipulate the individual variables than the flag register.
// Note that the two representations of flags are not kept
// synchronized, rather, individual flag variables take
// precendence over the flag register ...

static bool FlagS;
static bool FlagZ;
static bool FlagH;
static bool FlagP;
static bool FlagC;

// Processor clock counter for timing purposes ...

static int Clock;


//--------------------------------------------------------------------------
// Helper Variables

static byte abParity [256];

//--------------------------------------------------------------------------
// Helper Functions

// These are mostly inline functions rather than
// macros to avoid evaluating arguments multiple
// times.

/// Writes a byte to simulated memory array if it is writable.
inline void MemWriteByte (word iAddr, byte iData)
{
  if (MemMask [iAddr]) MemData [iAddr] = iData;
}

/// Writes a word to simulated memory array if it is writable.
inline void MemWriteWord (word iAddr, word iData)
{
  MemWriteByte (iAddr, iData);
  MemWriteByte (iAddr + (word) 1, iData >> 8);
}

/// Pushes a word onto the stack in the simulated memory array.
inline void MemPushWord (word iData)
{
  RegSP -= 2;
  MemWriteWord (RegSP, iData);
}

/// Pops a byte from the stack in the simulated memory array.
inline byte MemPopByte ()
{
  return (MemData [RegSP ++]);
}
/// Pops a word from the stack in the simulated memory array.
inline word MemPopWord ()
{
  byte iLow = MemPopByte ();
  byte iHigh = MemPopByte ();
  return (iLow + ((word) iHigh << 8));
}

/// Fetches a byte from simulated memory array at PC and shifts PC.
inline byte MemFetchByte ()
{
  return (MemData [RegPC ++]);
}
/// Fetches a word from simulated memory array at PC and shifts PC.
inline word MemFetchWord ()
{
  byte iLow = MemFetchByte ();
  byte iHigh = MemFetchByte ();
  return (iLow + ((word) iHigh << 8));
}


/// Expands its argument with all registers.
#define InstAllRegisters(I)                     \
  I (B)                                         \
  I (C)                                         \
  I (D)                                         \
  I (E)                                         \
  I (H)                                         \
  I (L)                                         \
  I (A)

/// Expands its arguments with all register pairs.
#define InstAllRegisterPairs(I)                 \
  I (BC,B)                                      \
  I (DE,D)                                      \
  I (HL,H)                                      \
  I (SP,SP)

/// Expands its arguments with all conditions.
#define InstAllConditions(I)                    \
  I (M,FlagS)                                   \
  I (P,!FlagS)                                  \
  I (Z,FlagZ)                                   \
  I (NZ,!FlagZ)                                 \
  I (PE,FlagP)                                  \
  I (PO,!FlagP)                                 \
  I (C,FlagC)                                   \
  I (NC,!FlagC)


//--------------------------------------------------------------------------
// Control Operations


/// Packs the value of individual flag variables into the flag register.
inline void FlagsPack ()
{
  // The calculation assumes that FALSE is 0 and
  // TRUE is 1, which is what the standard says
  RegF = 128 * FlagS +
          64 * FlagZ +
          16 * FlagH +
           4 * FlagP +
           2         +
           1 * FlagC;
}

/// Unpacks the value of individual flag variables from the flag register.
inline void FlagsUnpack ()
{
  // The calculation assumes that assignment of nonzero value
  // to boolean will be TRUE, which is what the standard says
  FlagS = RegF & 128;
  FlagZ = RegF & 64;
  FlagH = RegF & 16;
  FlagP = RegF & 4;
  FlagC = RegF & 1;
}


//==========================================================================
// PROCESSOR INSTRUCTIONS
//==========================================================================
// Functions that implement the individual processor instructions.
// They are sorted in the same way as in the processor manuals.
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// Helper Macros

// This code assumes that sizeof (uint) is more than a byte ...

#define MathExpandBinaryFull(L,O,R) ((uint) L) O ((uint) R)
#define MathExpandBinaryHalf(L,O,R) ((uint) L & 0xF) O ((uint) R & 0xF)

#define MathExpandCarryFull(L,O,R) ((uint) L) O ((uint) R) O (uint) FlagC
#define MathExpandCarryHalf(L,O,R) ((uint) L & 0xF) O ((uint) R & 0xF) O (uint) FlagC

// MathGeneric - Performs an arbitrary arithmetic operation
#define MathGeneric(L,O,R,X)                    \
  uint iResult = MathExpand##X##Full (L,O,R);

// MathGenericSZHP - Performs an arbitrary arithmetic operation and adjusts SZHP
#define MathGenericSZHP(L,O,R,X)                \
  MathGeneric(L,O,R,X)                          \
  FlagS = (iResult > 127);                      \
  FlagZ = ((byte) iResult == 0);                \
  FlagH = MathExpand##X##Half (L,O,R) > 0xF;    \
  FlagP = abParity [(byte) iResult];

// MathGenericSZHPC - Performs an arbitrary arithmetic operation and adjusts SZHPC
#define MathGenericSZHPC(L,O,R,X)               \
  MathGenericSZHP(L,O,R,X)                      \
  FlagC = (iResult > 255);

// LogicalGenericSZHPC - Performs an arbitrary logical operation and adjusts SZHPC
#define LogicalGenericSZHPC(L,O,R)              \
  byte iResult = L O R;                         \
  FlagS = (iResult > 127);                      \
  FlagZ = (iResult == 0);                       \
  FlagH = false;                                \
  FlagP = abParity [iResult];                   \
  FlagC = false;

//--------------------------------------------------------------------------
// Transfer Operations
//
// MOV, MVI, LXI, LDA, STA, LHLD, SHLD, LDAX, STAX, XCHG

// MOV between generic registers

#define InstMOVDstSrc(D,S)                      \
void InstMOV##D##S ()                           \
{                                               \
  Reg##D = Reg##S;                              \
  Clock += 5;                                   \
}

#define InstMOVDst(S)                           \
  InstMOVDstSrc (B,S)                           \
  InstMOVDstSrc (C,S)                           \
  InstMOVDstSrc (D,S)                           \
  InstMOVDstSrc (E,S)                           \
  InstMOVDstSrc (H,S)                           \
  InstMOVDstSrc (L,S)                           \
  InstMOVDstSrc (A,S)

InstAllRegisters (InstMOVDst)

#undef InstMOVDstSrc
#undef InstMOVDst

// MOV from register to memory

#define InstMOVMemSrc(S)                        \
void InstMOVM##S ()                             \
{                                               \
  MemWriteByte (RegHL, Reg##S);                 \
  Clock += 7;                                   \
}

InstAllRegisters (InstMOVMemSrc)

#undef InstMOVMemSrc

// MOV from memory to register

#define InstMOVMemDst(D)                        \
void InstMOV##D##M ()                           \
{                                               \
  Reg##D = MemData [RegHL];                     \
  Clock += 7;                                   \
}

InstAllRegisters (InstMOVMemDst)

#undef InstMOVMemDst

// MVI to register

#define InstMVIDst(D)                           \
void InstMVI##D ()                              \
{                                               \
  Reg##D = MemFetchByte ();                     \
  Clock += 7;                                   \
}

InstAllRegisters (InstMVIDst)

#undef InstMVIDst

// MVI to memory

void InstMVIM ()
{
  MemWriteByte (RegHL, MemFetchByte ());
  Clock += 10;
}

// LXI

#define InstLXIDst(D,N)                         \
void InstLXI##N ()                              \
{                                               \
  Reg##D = MemFetchWord ();                     \
  Clock += 10;                                  \
}

InstAllRegisterPairs (InstLXIDst)

#undef InstLXIDst

// LDA

void InstLDA ()
{
  RegA = MemData [MemFetchWord ()];
  Clock += 13;
}

// STA

void InstSTA ()
{
  MemWriteByte (MemFetchWord (), RegA);
  Clock += 13;
}

// LHLD

void InstLHLD ()
{
  RegHL = MemData [MemFetchWord ()];
  Clock += 16;
}

// SHLD

void InstSHLD ()
{
  int iAddr = MemFetchWord ();
  MemWriteWord (iAddr, RegHL);
  Clock += 16;
}

// LDAX

#define InstLDAXSrc(S,N)                        \
void InstLDAX##N ()                             \
{                                               \
  RegA = MemData [Reg##S];                      \
  Clock += 7;                                   \
}

InstAllRegisterPairs (InstLDAXSrc)

#undef InstLDAXSrc

// STAX

#define InstSTAXSrc(S,N)                        \
void InstSTAX##N ()                             \
{                                               \
  MemWriteByte (MemData [Reg##S], RegA);        \
  Clock += 7;                                   \
}

InstAllRegisterPairs (InstSTAXSrc)

#undef InstSTAXSrc

// XCHG

void InstXCHG ()
{
  int iTemp = RegDE;
  RegDE = RegHL;
  RegHL = iTemp;
  Clock += 4;
}

//--------------------------------------------------------------------------
// Arithmetic Instructions
//
// ADD, ADI, ADC, ACI, SUB, SUI, SBB, SBI, INR, DCR, INX, DCX, DAD, DAA

// ADD from register

#define InstADDSrc(S)                           \
void InstADD##S ()                              \
{                                               \
  MathGenericSZHPC (RegA,+,Reg##S,Binary)       \
  RegA = iResult;                               \
  Clock += 4;                                   \
}

InstAllRegisters (InstADDSrc)

#undef InstADDSrc

// ADD from memory

void InstADDM ()
{
  MathGenericSZHPC (RegA,+,MemData [RegHL],Binary)
  RegA = iResult;
  Clock += 7;
}

// ADI

void InstADI ()
{
  byte iOperand = MemFetchByte ();
  MathGenericSZHPC (RegA,+,iOperand,Binary)
  RegA = iResult;
  Clock += 7;
}

// ADC from register

#define InstADCSrc(S)                           \
void InstADC##S ()                              \
{                                               \
  MathGenericSZHPC (RegA,+,Reg##S,Carry)        \
  RegA = iResult;                               \
  Clock += 4;                                   \
}

InstAllRegisters (InstADCSrc)

#undef InstADCSrc

// ADC from memory

void InstADCM ()
{
  MathGenericSZHPC (RegA,+,MemData [RegHL],Carry)
  RegA = iResult;
  Clock += 7;
}

// ACI

void InstACI ()
{
  byte iOperand = MemFetchByte ();
  MathGenericSZHPC (RegA,+,iOperand,Carry)
  RegA = iResult;
  Clock += 7;
}

// SUB from register

#define InstSUBSrc(S)                           \
void InstSUB##S ()                              \
{                                               \
  MathGenericSZHPC (RegA,-,Reg##S,Binary)       \
  RegA = iResult;                               \
  Clock += 4;                                   \
}

InstAllRegisters (InstSUBSrc)

#undef InstSUBSrc

// SUB from memory

void InstSUBM ()
{
  MathGenericSZHPC (RegA,-,MemData [RegHL],Binary)
  RegA = iResult;
  Clock += 7;
}

// SUI

void InstSUI ()
{
  byte iOperand = MemFetchByte ();
  MathGenericSZHPC (RegA,-,iOperand,Binary)
  RegA = iResult;
  Clock += 7;
}

// SBB from register

#define InstSBBSrc(S)                           \
void InstSBB##S ()                              \
{                                               \
  MathGenericSZHPC (RegA,-,Reg##S,Carry)        \
  RegA = iResult;                               \
  Clock += 4;                                   \
}

InstAllRegisters (InstSBBSrc)

#undef InstSBBSrc

// SBB from memory

void InstSBBM ()
{
  MathGenericSZHPC (RegA,-,MemData [RegHL],Carry)
  RegA = iResult;
  Clock += 7;
}

// SBI

void InstSBI ()
{
  byte iOperand = MemFetchByte ();
  MathGenericSZHPC (RegA,-,iOperand,Carry)
  RegA = iResult;
  Clock += 7;
}

// INR register

#define InstINRDst(D)                           \
void InstINR##D ()                              \
{                                               \
  MathGenericSZHP (Reg##D,+,1,Binary)           \
  Reg##D = iResult;                             \
  Clock += 5;                                   \
}

InstAllRegisters (InstINRDst)

#undef InstINRDst

// INR memory

void InstINRM ()
{
  MathGenericSZHP (MemData [RegHL],+,1,Binary)
  MemWriteByte (RegHL, iResult);
  Clock += 10;
}

// DCR register

#define InstDCRDst(D)                           \
void InstDCR##D ()                              \
{                                               \
  MathGenericSZHP (Reg##D,-,1,Binary)           \
  Reg##D = iResult;                             \
  Clock += 5;                                   \
}

InstAllRegisters (InstDCRDst)

#undef InstDCRDst

// DCR memory

void InstDCRM ()
{
  MathGenericSZHP (MemData [RegHL],-,1,Binary)
  MemWriteByte (RegHL, iResult);
  Clock += 10;
}

// INX

#define InstINXDst(D,N)                         \
void InstINX##N ()                              \
{                                               \
  ++ Reg##D;                                    \
  Clock += 5;                                   \
}

InstAllRegisterPairs (InstINXDst)

#undef InstINXDst

// DCX

#define InstDCXDst(D,N)                         \
void InstDCX##N ()                              \
{                                               \
  -- Reg##D;                                    \
  Clock += 5;                                   \
}

InstAllRegisterPairs (InstDCXDst)

#undef InstDCXDst

// DAD

// This code assumes that sizeof (uint) is more than a word ...

#define InstDADSrc(S,N)                         \
void InstDAD##N ()                              \
{                                               \
  uint iResult = RegHL + Reg##S;                \
  FlagC = (iResult > 65535);                    \
  RegHL = iResult;                              \
  Clock += 10;                                  \
}

InstAllRegisterPairs (InstDADSrc)

#undef InstDADSrc

// DAA

// Not at all sure how DAA should really set the flags ...

void InstDAA ()
{
  uint iResult = RegA;
  // Correct the lower nibble ...
  if ((iResult & 0xF) > 0x9 || FlagH)
  {
    iResult += 0x6;
    FlagH = (iResult & 0xF) < 0x6;
  }
  else FlagH = false;
  // Correct the upper nibble
  if ((iResult & 0xF0) > 0x90 || FlagC)
  {
    iResult += 0x60;
    FlagC = (iResult & 0xF0) < 0x60;
  }
  else FlagC = false;
  // Set the remaining flags ...
  FlagS = (iResult > 127);
  FlagZ = ((byte) iResult == 0);
  FlagP = abParity [(byte) iResult];
  // Store the result ...
  RegA = iResult;
  // Update the clock ...
  Clock += 4;
}

//--------------------------------------------------------------------------
// Logical Instructions
//
// ANA, ANI, XRA, XRI, ORA, ORI, CMP, CPI, RLC, RRC, RAL, RAR, CMA, CMC, STC

// ANA from register

#define InstANASrc(S)                           \
void InstANA##S ()                              \
{                                               \
  LogicalGenericSZHPC (RegA,&,Reg##S)           \
  RegA = iResult;                               \
  Clock += 4;                                   \
}

InstAllRegisters (InstANASrc)

#undef InstANASrc

// ANA from memory

void InstANAM ()
{
  LogicalGenericSZHPC (RegA,&,MemData [RegHL])
  RegA = iResult;
  Clock += 7;
}

// ANI

void InstANI ()
{
  byte iOperand = MemFetchByte ();
  LogicalGenericSZHPC (RegA,&,iOperand)
  RegA = iResult;
  Clock += 7;
}

// XRA from register

#define InstXRASrc(S)                           \
void InstXRA##S ()                              \
{                                               \
  LogicalGenericSZHPC (RegA,^,Reg##S)           \
  RegA = iResult;                               \
  Clock += 4;                                   \
}

InstAllRegisters (InstXRASrc)

#undef InstXRASrc

// XRA from memory

void InstXRAM ()
{
  LogicalGenericSZHPC (RegA,^,MemData [RegHL])
  RegA = iResult;
  Clock += 7;
}

// XRI

void InstXRI ()
{
  byte iOperand = MemFetchByte ();
  LogicalGenericSZHPC (RegA,^,iOperand)
  RegA = iResult;
  Clock += 7;
}

// ORA from register

#define InstORASrc(S)                           \
void InstORA##S ()                              \
{                                               \
  LogicalGenericSZHPC (RegA,|,Reg##S)           \
  RegA = iResult;                               \
  Clock += 4;                                   \
}

InstAllRegisters (InstORASrc)

#undef InstORASrc

// ORA from memory

void InstORAM ()
{
  LogicalGenericSZHPC (RegA,|,MemData [RegHL])
  RegA = iResult;
  Clock += 7;
}

// ORI

void InstORI ()
{
  byte iOperand = MemFetchByte ();
  LogicalGenericSZHPC (RegA,|,iOperand)
  RegA = iResult;
  Clock += 7;
}

// CMP from register

#define InstCMPSrc(S)                           \
void InstCMP##S ()                              \
{                                               \
  MathGenericSZHPC (RegA,-,Reg##S,Binary)       \
  Clock += 4;                                   \
}

InstAllRegisters (InstCMPSrc)

#undef InstCMPSrc

// CMP from memory

void InstCMPM ()
{
  MathGenericSZHPC (RegA,-,MemData [RegHL],Binary)
  Clock += 7;
}

// CPI

void InstCPI ()
{
  byte iOperand = MemFetchByte ();
  MathGenericSZHPC (RegA,-,iOperand,Binary)
  Clock += 7;
}

// RLC

void InstRLC ()
{
  FlagC = (RegA & 0x80);
  RegA = (RegA << 1) | (FlagC ? 0x1 : 0);
  Clock += 4;
}

// RRC

void InstRRC ()
{
  FlagC = (RegA & 0x1);
  RegA = (RegA >> 1) | (FlagC ? 0x80 : 0);
  Clock += 4;
}

// RAL

void InstRAL ()
{
  bool bOverflow = (RegA & 0x80);
  RegA = (RegA << 1) | (FlagC ? 0x1 : 0);
  FlagC = bOverflow;
  Clock += 4;
}

// RAR

void InstRAR ()
{
  bool bOverflow = (RegA & 0x1);
  RegA = (RegA >> 1) | (FlagC ? 0x80 : 0);
  FlagC = bOverflow;
  Clock += 4;
}

// CMA

void InstCMA ()
{
  RegA = ~RegA;
  Clock += 4;
}

// CMC

void InstCMC ()
{
  FlagC = !FlagC;
  Clock += 4;
}

// STC

void InstSTC ()
{
  FlagC = true;
  Clock += 4;
}

//--------------------------------------------------------------------------
// Branch Instructions
//
// JMP, CALL, RET, RST, PCHL

// JMP

void InstJMP ()
{
  RegPC = MemFetchWord ();
  Clock += 10;
}

// JMP conditional

#define InstJMPCon(C,E)                         \
void InstJ##C ()                                \
{                                               \
  word iTarget = MemFetchWord ();               \
  if (E) RegPC = iTarget;                       \
  Clock += 10;                                  \
}

InstAllConditions (InstJMPCon)

#undef InstJMPCon

// CALL

void InstCALL ()
{
  word iTarget = MemFetchWord ();
  MemPushWord (RegPC);
  RegPC = iTarget;
  Clock += 17;
}

// CALL conditional

#define InstCALLCon(C,E)                        \
void InstC##C ()                                \
{                                               \
  word iTarget = MemFetchWord ();               \
  if (E)                                        \
  {                                             \
    MemPushWord (RegPC);                        \
    RegPC = iTarget;                            \
    Clock += 6;                                 \
  }                                             \
  Clock += 11;                                  \
}

InstAllConditions (InstCALLCon)

#undef InstCALLCon

// RET

void InstRET ()
{
  RegPC = MemPopWord ();
  Clock += 10;
}

// RET conditional

#define InstRETCon(C,E)                         \
void InstR##C ()                                \
{                                               \
  if (E)                                        \
  {                                             \
    RegPC = MemPopWord ();                      \
    Clock += 6;                                 \
  }                                             \
  Clock += 5;                                   \
}

InstAllConditions (InstRETCon)

#undef InstRETCon

// RST

#define InstRSTVec(V)                           \
void InstRST##V ()                              \
{                                               \
  MemPushWord (RegPC);                          \
  RegPC = V * 8;                                \
  Clock += 11;                                  \
}

InstRSTVec (0)
InstRSTVec (1)
InstRSTVec (2)
InstRSTVec (3)
InstRSTVec (4)
InstRSTVec (5)
InstRSTVec (6)
InstRSTVec (7)

#undef InstRSTVec

// PCHL

void InstPCHL ()
{
  RegPC = RegHL;
  Clock += 5;
}

//--------------------------------------------------------------------------
// Stack Operations
//
// PUSH, POP, XTHL, SPHL

// PUSH

#define InstPUSHSrc(D,N)                        \
void InstPUSH##N ()                             \
{                                               \
  MemPushWord (Reg##D);                         \
  Clock += 11;                                  \
}

InstAllRegisterPairs (InstPUSHSrc)

#undef InstPUSHSrc

// PUSH PSW

void InstPUSHPSW ()
{
  FlagsPack ();
  MemPushWord (RegAF);
  Clock += 11;
}

// POP

#define InstPOPDst(D,N)                         \
void InstPOP##N ()                              \
{                                               \
  Reg##D = MemPopWord ();                       \
  Clock += 10;                                  \
}

InstAllRegisterPairs (InstPOPDst)

#undef InstPOPDst

// POP PSW

void InstPOPPSW ()
{
  RegAF = MemPopWord ();
  FlagsUnpack ();
  Clock += 10;
}

// XTHL

void InstXTHL ()
{
  word iData = RegHL;
  RegL = MemData [RegSP];
  RegH = MemData [RegSP + (word) 1];
  MemWriteWord (RegSP, iData);
  Clock += 18;
}

// SPHL

void InstSPHL ()
{
  RegSP = RegHL;
  Clock += 5;
}

//--------------------------------------------------------------------------
// Special Operations
//
// IN, OUT, EI, DI, HLT, NOP

// IN

void InstIN ()
{
  int iPort = MemFetchByte ();
  switch (iPort)
  {
    case 0xF5:  RegA = KBDReadRow ();
                break;
    default:    RegA = 0xFF;
                break;
  }
  Clock += 10;
}

// OUT

void InstOUT ()
{
  int iPort = MemFetchByte ();
  switch (iPort)
  {
    case 0xF4:  KBDWriteColumn (RegA);
                break;
  }
  Clock += 10;
}

// EI

void InstEI ()
{
  // No interrupts were used in this computer
  Clock += 4;
}

// DI

void InstDI ()
{
  // No interrupts were used in this computer
  Clock += 4;
}

// HLT

void InstHLT ()
{
  // No interrupts were used in this computer and
  // therefore the instruction should halt forever
  -- RegPC;
  Clock += 7;
}

// NOP

void InstNOP ()
{
  // Guess what :-)
  Clock += 4;
}

//--------------------------------------------------------------------------
// Execution

/// A table of functions implementing the individual instructions.
static void (*apInstructionTable [256]) () =
{
        // 00h
        InstNOP,        InstLXIB,       InstSTAXB,      InstINXB,
        InstINRB,       InstDCRB,       InstMVIB,       InstRLC,
        InstNOP,        InstDADB,       InstLDAXB,      InstDCXB,
        InstINRC,       InstDCRC,       InstMVIC,       InstRRC,
        // 10h
        InstNOP,        InstLXID,       InstSTAXD,      InstINXD,
        InstINRD,       InstDCRD,       InstMVID,       InstRAL,
        InstNOP,        InstDADD,       InstLDAXD,      InstDCXD,
        InstINRE,       InstDCRE,       InstMVIE,       InstRAR,
        // 20h
        InstNOP,        InstLXIH,       InstSHLD,       InstINXH,
        InstINRH,       InstDCRH,       InstMVIH,       InstDAA,
        InstNOP,        InstDADH,       InstLHLD,       InstDCXH,
        InstINRL,       InstDCRL,       InstMVIL,       InstCMA,
        // 30h
        InstNOP,        InstLXISP,      InstSTA,        InstINXSP,
        InstINRM,       InstDCRM,       InstMVIM,       InstSTC,
        InstNOP,        InstDADSP,      InstLDA,        InstDCXSP,
        InstINRA,       InstDCRA,       InstMVIA,       InstCMC,
        // 40h
        InstNOP,        InstMOVBC,      InstMOVBD,      InstMOVBE,
        InstMOVBH,      InstMOVBL,      InstMOVBM,      InstMOVBA,
        InstMOVCB,      InstNOP,        InstMOVCD,      InstMOVCE,
        InstMOVCH,      InstMOVCL,      InstMOVCM,      InstMOVCA,
        // 50h
        InstMOVDB,      InstMOVDC,      InstNOP,        InstMOVDE,
        InstMOVDH,      InstMOVDL,      InstMOVDM,      InstMOVDA,
        InstMOVEB,      InstMOVEC,      InstMOVED,      InstNOP,
        InstMOVEH,      InstMOVEL,      InstMOVEM,      InstMOVEA,
        // 60h
        InstMOVHB,      InstMOVHC,      InstMOVHD,      InstMOVHE,
        InstNOP,        InstMOVHL,      InstMOVHM,      InstMOVHA,
        InstMOVLB,      InstMOVLC,      InstMOVLD,      InstMOVLE,
        InstMOVLH,      InstNOP,        InstMOVLM,      InstMOVLA,
        // 70h
        InstMOVMB,      InstMOVMC,      InstMOVMD,      InstMOVME,
        InstMOVMH,      InstMOVML,      InstHLT,        InstMOVMA,
        InstMOVAB,      InstMOVAC,      InstMOVAD,      InstMOVAE,
        InstMOVAH,      InstMOVAL,      InstMOVAM,      InstNOP,
        // 80h
        InstADDB,       InstADDC,       InstADDD,       InstADDE,
        InstADDH,       InstADDL,       InstADDM,       InstADDA,
        InstADCB,       InstADCC,       InstADCD,       InstADCE,
        InstADCH,       InstADCL,       InstADCM,       InstADCA,
        // 90h
        InstSUBB,       InstSUBC,       InstSUBD,       InstSUBE,
        InstSUBH,       InstSUBL,       InstSUBM,       InstSUBA,
        InstSBBB,       InstSBBC,       InstSBBD,       InstSBBE,
        InstSBBH,       InstSBBL,       InstSBBM,       InstSBBA,
        // 0A0h
        InstANAB,       InstANAC,       InstANAD,       InstANAE,
        InstANAH,       InstANAL,       InstANAM,       InstANAA,
        InstXRAB,       InstXRAC,       InstXRAD,       InstXRAE,
        InstXRAH,       InstXRAL,       InstXRAM,       InstXRAA,
        // 0B0h
        InstORAB,       InstORAC,       InstORAD,       InstORAE,
        InstORAH,       InstORAL,       InstORAM,       InstORAA,
        InstCMPB,       InstCMPC,       InstCMPD,       InstCMPE,
        InstCMPH,       InstCMPL,       InstCMPM,       InstCMPA,
        // 0C0h
        InstRNZ,        InstPOPB,       InstJNZ,        InstJMP,
        InstCNZ,        InstPUSHB,      InstADI,        InstRST0,
        InstRZ,         InstRET,        InstJZ,         InstNOP,
        InstCZ,         InstCALL,       InstACI,        InstRST1,
        // 0D0h
        InstRNC,        InstPOPD,       InstJNC,        InstOUT,
        InstCNC,        InstPUSHD,      InstSUI,        InstRST2,
        InstRC,         InstNOP,        InstJC,         InstIN,
        InstCC,         InstNOP,        InstSBI,        InstRST3,
        // 0E0h
        InstRPO,        InstPOPH,       InstJPO,        InstXTHL,
        InstCPO,        InstPUSHH,      InstANI,        InstRST4,
        InstRPE,        InstPCHL,       InstJPE,        InstXCHG,
        InstCPE,        InstNOP,        InstXRI,        InstRST5,
        // 0F0h
        InstRP,         InstPOPPSW,     InstJP,         InstNOP,
        InstCP,         InstPUSHPSW,    InstORI,        InstRST6,
        InstRM,         InstSPHL,       InstJM,         InstNOP,
        InstCM,         InstNOP,        InstCPI,        InstRST7
};


/// Resets the processor.
void CPUReset ()
{
  // The computer used an invertor on the address bus to
  // fetch the very first instruction after reset from
  // 8000h. Since this instruction was a jump, this
  // was effectively the same as initializing the
  // program counter at 8000h.

  RegPC = 0x8000;

  // Counting clock from zero is not strictly necessary ...

  Clock = 0;

  // No other initialization is done at reset.
}


/// Executes the processor instructions.
void CPUExecute ()
{
  // Synchronize the simulated clock and the actual time
  TIMSynchronize (Clock);

  while (true)
  {
//!@#@!
std::cout << std::hex << (int) RegPC << " " << (int) MemData [RegPC] << " A" << (int) RegA << " BC" << (int) RegBC << " DE" << (int) RegDE << " HL" << (int) RegHL << " SP" << (int) RegSP << std::endl;
//#@!@#
    byte bCode = MemFetchByte ();
    apInstructionTable [bCode] ();

    // Advance the simulated clock and the actual time by sleeping
    TIMAdvance (Clock);
  }
}

//--------------------------------------------------------------------------
// Threads

int CPUThread (void *pArgs)
{
  CPUExecute ();
}

//--------------------------------------------------------------------------
// Initialization and shutdown

void CPUInitialize ()
{
  // Calculate the contents of the parity lookup array

  for (int iValue = 0 ; iValue < 256 ; iValue ++)
  {
    bool bParity = false;
    for (int iMask = 1 ; iMask < 256 ; iMask <<= 1)
    {
      if (iValue & iMask)
      {
        bParity = ~bParity;
      }
    }
    abParity [iValue] = bParity;
  }

  // Make the entire memory writable

  for (int iAddr = 0 ; iAddr < 65536 ; iAddr ++)
  {
    MemMask [iAddr] = true;
  }

  // Reset the processor

  CPUReset ();
}


void CPUShutdown ()
{
}

//--------------------------------------------------------------------------

