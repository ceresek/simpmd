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

static RegisterPairUnion (B,C);
static RegisterPairUnion (D,E);
static RegisterPairUnion (H,L);
static RegisterPairUnion (F,A);

#define RegBC (RegisterPairBC.Pair)
#define RegDE (RegisterPairDE.Pair)
#define RegHL (RegisterPairHL.Pair)
#define RegFA (RegisterPairFA.Pair)

#define RegB (RegisterPairBC.One.B)
#define RegC (RegisterPairBC.One.C)
#define RegD (RegisterPairDE.One.D)
#define RegE (RegisterPairDE.One.E)
#define RegH (RegisterPairHL.One.H)
#define RegL (RegisterPairHL.One.L)
#define RegF (RegisterPairFA.One.F)
#define RegA (RegisterPairFA.One.A)

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

//--------------------------------------------------------------------------
// Helper Variables

static byte abParity [256];

//--------------------------------------------------------------------------
// Helper Macros

/** Writes a byte to simulated memory array if it is writable
 *
 * This is an inline function rather than a macro
 * to avoid evaluating arguments multiple times.
 *
 */
inline void MemWriteByte (word iAddr, byte iData)
{
  if (MemMask [iAddr]) MemData [iAddr] = iData;
}

/** Writes a word to simulated memory array if it is writable
 *
 * This is an inline function rather than a macro
 * to avoid evaluating arguments multiple times.
 *
 */
inline void MemWriteWord (word iAddr, word iData)
{
  MemWriteByte (iAddr, iData);
  MemWriteByte (iAddr + 1, iData >> 8);
}

/// Pushes a word onto the stack in the simulated memory array
inline void MemPushWord (word iData)
{
  RegSP -= 2;
  MemWriteWord (RegSP, iData);
}

/// Pops a byte from the stack in the simulated memory array
#define MemPopByte (MemData [RegSP ++])
/// Pops a word from the stack in the simulated memory array
#define MemPopWord (MemPopByte + 256 * MemPopByte)

/// Fetches a byte from simulated memory array at PC and shifts PC
#define MemFetchByte (MemData [RegPC ++])
/// Fetches a word from simulated memory array at PC and shifts PC
#define MemFetchWord (MemFetchByte + 256 * MemFetchByte)

/// Expands its argument with all registers
#define InstAllRegisters(I)                     \
  I (B)                                         \
  I (C)                                         \
  I (D)                                         \
  I (E)                                         \
  I (H)                                         \
  I (L)                                         \
  I (A)

/// Expands its arguments with all register pairs
#define InstAllRegisterPairs(I)                 \
  I (BC,B,C)                                    \
  I (DE,D,E)                                    \
  I (HL,H,L)

/// Expands its arguments with all conditions
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


inline void FlagsPack ()
// Packs the value of individual flag variables into the flag register
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

inline void FlagsUnpack ()
// Unpacks the value of individual flag variables from the flag register
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
// Arithmetic Operations
//
// ADD, ADI, ADC, ACI, SUB, SUI, SBB, SBI, INR, DCR, INX, DCX, DAD, DAA

// ADD from register

#define InstADDSrc(S)                           \
void InstADD##S ()                              \
{                                               \
  MathGenericSZHPC (RegA,+,Reg##S,Binary)       \
  RegA = iResult;                               \
}

InstAllRegisters (InstADDSrc)

#undef InstADDSrc

// ADD from memory

void InstADDM ()
{
  MathGenericSZHPC (RegA,+,MemData [RegHL],Binary)
  RegA = iResult;
}

// ADI

void InstADI ()
{
  byte iOperand = MemFetchByte;
  MathGenericSZHPC (RegA,+,iOperand,Binary)
  RegA = iResult;
}

// ADC from register

#define InstADCSrc(S)                           \
void InstADC##S ()                              \
{                                               \
  MathGenericSZHPC (RegA,+,Reg##S,Carry)        \
  RegA = iResult;                               \
}

InstAllRegisters (InstADCSrc)

#undef InstADCSrc

// ADC from memory

void InstADCM ()
{
  MathGenericSZHPC (RegA,+,MemData [RegHL],Carry)
  RegA = iResult;
}

// ACI

void InstACI ()
{
  byte iOperand = MemFetchByte;
  MathGenericSZHPC (RegA,+,iOperand,Carry)
  RegA = iResult;
}

// SUB from register

#define InstSUBSrc(S)                           \
void InstSUB##S ()                              \
{                                               \
  MathGenericSZHPC (RegA,-,Reg##S,Binary)       \
  RegA = iResult;                               \
}

InstAllRegisters (InstSUBSrc)

#undef InstSUBSrc

// SUB from memory

void InstSUBM ()
{
  MathGenericSZHPC (RegA,-,MemData [RegHL],Binary)
  RegA = iResult;
}

// SUI

void InstSUI ()
{
  byte iOperand = MemFetchByte;
  MathGenericSZHPC (RegA,-,iOperand,Binary)
  RegA = iResult;
}

// SBB from register

#define InstSBBSrc(S)                           \
void InstSBB##S ()                              \
{                                               \
  MathGenericSZHPC (RegA,-,Reg##S,Carry)        \
  RegA = iResult;                               \
}

InstAllRegisters (InstSBBSrc)

#undef InstSBBSrc

// SBB from memory

void InstSBBM ()
{
  MathGenericSZHPC (RegA,-,MemData [RegHL],Carry)
  RegA = iResult;
}

// SBI

void InstSBI ()
{
  byte iOperand = MemFetchByte;
  MathGenericSZHPC (RegA,-,iOperand,Carry)
  RegA = iResult;
}

// INR register

#define InstINRDst(D)                           \
void InstINR##D ()                              \
{                                               \
  MathGenericSZHP (Reg##D,+,1,Binary)           \
  Reg##D = iResult;                             \
}

InstAllRegisters (InstINRDst)

#undef InstINRDst

// INR memory

void InstINRM ()
{
  MathGenericSZHP (MemData [RegHL],+,1,Binary)
  MemWriteByte (RegHL, iResult);
}

// DCR register

#define InstDCRDst(D)                           \
void InstDCR##D ()                              \
{                                               \
  MathGenericSZHP (Reg##D,-,1,Binary)           \
  Reg##D = iResult;                             \
}

InstAllRegisters (InstDCRDst)

#undef InstDCRDst

// DCR memory

void InstDCRM ()
{
  MathGenericSZHP (MemData [RegHL],-,1,Binary)
  MemWriteByte (RegHL, iResult);
}

// INX

#define InstINXDst(D,H,L)                       \
void InstINX##D ()                              \
{                                               \
  Reg##D ++;                                    \
}

InstAllRegisterPairs (InstINXDst)

#undef InstINXDst

// DCX

#define InstDCXDst(D,H,L)                       \
void InstDCX##D ()                              \
{                                               \
  Reg##D --;                                    \
}

InstAllRegisterPairs (InstDCXDst)

#undef InstDCXDst

// DAD

// This code assumes that sizeof (uint) is more than a word ...

#define InstDADSrc(S,H,L)                       \
void InstDAD##S ()                              \
{                                               \
  uint iResult = RegHL + Reg##S;                \
  FlagC = (iResult > 65535);                    \
  RegHL = iResult;                              \
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
}

//--------------------------------------------------------------------------
// Logical Operations
//
// ANA, ANI, XRA, XRI, ORA, ORI, CMP, CPI, RLC, RRC, RAL, RAR, CMA, CMC, STC

// ANA from register

#define InstANASrc(S)                           \
void InstANA##S ()                              \
{                                               \
  LogicalGenericSZHPC (RegA,&,Reg##S)           \
  RegA = iResult;                               \
}

InstAllRegisters (InstANASrc)

#undef InstANASrc

// ANA from memory

void InstANAM ()
{
  LogicalGenericSZHPC (RegA,&,MemData [RegHL])
  RegA = iResult;
}

// ANI

void InstANI ()
{
  byte iOperand = MemFetchByte;
  LogicalGenericSZHPC (RegA,&,iOperand)
  RegA = iResult;
}

// XRA from register

#define InstXRASrc(S)                           \
void InstXRA##S ()                              \
{                                               \
  LogicalGenericSZHPC (RegA,^,Reg##S)           \
  RegA = iResult;                               \
}

InstAllRegisters (InstXRASrc)

#undef InstXRASrc

// XRA from memory

void InstXRAM ()
{
  LogicalGenericSZHPC (RegA,^,MemData [RegHL])
  RegA = iResult;
}

// XRI

void InstXRI ()
{
  byte iOperand = MemFetchByte;
  LogicalGenericSZHPC (RegA,^,iOperand)
  RegA = iResult;
}

// ORA from register

#define InstORASrc(S)                           \
void InstORA##S ()                              \
{                                               \
  LogicalGenericSZHPC (RegA,|,Reg##S)           \
  RegA = iResult;                               \
}

InstAllRegisters (InstORASrc)

#undef InstORASrc

// ORA from memory

void InstORAM ()
{
  LogicalGenericSZHPC (RegA,|,MemData [RegHL])
  RegA = iResult;
}

// ORI

void InstORI ()
{
  byte iOperand = MemFetchByte;
  LogicalGenericSZHPC (RegA,|,iOperand)
  RegA = iResult;
}

// CMP from register

#define InstCMPSrc(S)                           \
void InstCMP##S ()                              \
{                                               \
  MathGenericSZHPC (RegA,-,Reg##S,Binary)       \
}

InstAllRegisters (InstCMPSrc)

#undef InstCMPSrc

// CMP from memory

void InstCMPM ()
{
  MathGenericSZHPC (RegA,-,MemData [RegHL],Binary)
}

// CPI

void InstCPI ()
{
  byte iOperand = MemFetchByte;
  MathGenericSZHPC (RegA,-,iOperand,Binary)
}

// RLC

void InstRLC ()
{
  FlagC = (RegA & 0x80);
  RegA = (RegA << 1) | (FlagC ? 0x1 : 0);
}

// RRC

void InstRRC ()
{
  FlagC = (RegA & 0x1);
  RegA = (RegA >> 1) | (FlagC ? 0x80 : 0);
}

// RAL

void InstRAL ()
{
  bool bOverflow = (RegA & 0x80);
  RegA = (RegA << 1) | (FlagC ? 0x1 : 0);
  FlagC = bOverflow;
}

// RAR

void InstRAR ()
{
  bool bOverflow = (RegA & 0x1);
  RegA = (RegA >> 1) | (FlagC ? 0x80 : 0);
  FlagC = bOverflow;
}

// CMA

void InstCMA ()
{
  RegA = ~RegA;
}

// CMC

void InstCMC ()
{
  FlagC = !FlagC;
}

// STC

void InstSTC ()
{
  FlagC = true;
}

//--------------------------------------------------------------------------
// Branch Operations
//
// JMP, CALL, RET, RST, PCHL

// JMP

void InstJMP ()
{
  RegPC = MemFetchWord;
}

// JMP conditional

#define InstJMPCon(C,E)                         \
void InstJ##C ()                                \
{                                               \
  word iTarget = MemFetchWord;                  \
  if (E) RegPC = iTarget;                       \
}

InstAllConditions (InstJMPCon)

#undef InstJMPCon

// CALL

void InstCALL ()
{
  word iTarget = MemFetchWord;
  MemPushWord (RegPC);
  RegPC = iTarget;
}

// CALL conditional

#define InstCALLCon(C,E)                        \
void InstC##C ()                                \
{                                               \
  word iTarget = MemFetchWord;                  \
  if (E)                                        \
  {                                             \
    MemPushWord (RegPC);                        \
    RegPC = iTarget;                            \
  }                                             \
}

InstAllConditions (InstCALLCon)

#undef InstCALLCon

// RET

void InstRET ()
{
  RegPC = MemPopWord;
}

// RET conditional

#define InstRETCon(C,E)                         \
void InstR##C ()                                \
{                                               \
  if (E) RegPC = MemPopWord;                    \
}

InstAllConditions (InstRETCon)

#undef InstRETCon

// RST

#define InstRSTVec(V)                           \
void InstRST##V ()                              \
{                                               \
  MemPushWord (RegPC);                          \
  RegPC = V * 8;                                \
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
}

//--------------------------------------------------------------------------
// Transfer Operations
//
// MOV, MVI, LXI, LDA, STA, LHLD, SHLD, LDAX, STAX, XCHG

// MOV between generic registers

#define InstMOVDstSrc(D,S)                      \
void InstMOV##D##S ()                           \
{                                               \
  Reg##D = Reg##S;                              \
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
}

InstAllRegisters (InstMOVMemSrc)

#undef InstMOVMemSrc

// MOV from memory to register

#define InstMOVMemDst(D)                        \
void InstMOV##D##M ()                           \
{                                               \
  Reg##D = MemData [RegHL];                     \
}

InstAllRegisters (InstMOVMemDst)

#undef InstMOVMemDst

// MVI to register

#define InstMVIDst(D)                           \
void InstMVI##D ()                              \
{                                               \
  Reg##D = MemFetchByte;                        \
}

InstAllRegisters (InstMVIDst)

#undef InstMVIDst

// MVI to memory

void InstMVIM ()
{
  MemWriteByte (RegHL, MemFetchByte);
}

// LXI

#define InstLXIDst(D,H,L)                       \
void InstLXI##D ()                              \
{                                               \
  Reg##D = MemFetchWord;                        \
}

InstAllRegisterPairs (InstLXIDst)

#undef InstLXIDst

// LDA

void InstLDA ()
{
  RegA = MemData [MemFetchWord];
}

// STA

void InstSTA ()
{
  MemWriteByte (MemFetchWord, RegA);
}

// LHLD

void InstLHLD ()
{
  RegHL = MemData [MemFetchWord];
}

// SHLD

void InstSHLD ()
{
  int iAddr = MemFetchWord;
  MemWriteWord (iAddr, RegHL);
}

// LDAX

#define InstLDAXSrc(S,H,L)                      \
void InstLDAX##S ()                             \
{                                               \
  RegA = MemData [Reg##S];                      \
}

InstAllRegisterPairs (InstLDAXSrc)

#undef InstLDAXSrc

// STAX

#define InstSTAXSrc(S,H,L)                      \
void InstSTAX##S ()                             \
{                                               \
  MemWriteByte (MemData [Reg##S], RegA);        \
}

InstAllRegisterPairs (InstSTAXSrc)

#undef InstSTAXSrc

// XCHG

void InstXCHG ()
{
  int iTemp = RegDE;
  RegDE = RegHL;
  RegHL = iTemp;
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
}


void CPUShutdown ()
{
}

//--------------------------------------------------------------------------

