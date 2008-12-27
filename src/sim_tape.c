/*

SIM_TAPE.C

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

#include <popt.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#include <SDL/SDL.h>

#include "sim_common.h"


//--------------------------------------------------------------------------
// Command Line Options

/// Tape input. What file to open as tape input.
static char *pArgTapeInput = NULL;
/// Tape output. What file to open as tape output.
static char *pArgTapeOutput = NULL;

/// Module command line options table.
struct poptOption asTAPOptions [] =
{
  { "tape-in", 'i', POPT_ARG_STRING,
      &pArgTapeInput, 0,
      "file to open as tape input", "file" },
  { "tape-out", 'o', POPT_ARG_STRING,
      &pArgTapeOutput, 0,
      "file to open as tape output", "file" },
  POPT_TABLEEND
};


//--------------------------------------------------------------------------
// Data

/// Tape input file handle.
static int hTapeInput = INVALID_HANDLE;
/// Tape output file handle.
static int hTapeOutput = INVALID_HANDLE;


//--------------------------------------------------------------------------
// Port operations

/** Read from tape data register.
 */
byte TAPReadData ()
{
  byte iData = 0;
  if (hTapeInput != INVALID_HANDLE)
  {
    read (hTapeInput, &iData, 1);
  }
  return (iData);
}


/** Write to tape data register.
 *
 *  @arg iData The written value.
 */
void TAPWriteData (byte iData)
{
  if (hTapeOutput != INVALID_HANDLE)
  {
    write (hTapeOutput, &iData, 1);
  }
}


//--------------------------------------------------------------------------
// Initialization and shutdown

void TAPInitialize ()
{
  // If tape input or tape output was specified, open it.
  if (pArgTapeInput)  hTapeInput  = open (pArgTapeInput, O_RDONLY);
  if (pArgTapeOutput) hTapeOutput = open (pArgTapeOutput, O_WRONLY);
}


void TAPShutdown ()
{
  // Close tape input and tape output.
  if (hTapeInput  != INVALID_HANDLE) close (hTapeInput);
  if (hTapeOutput != INVALID_HANDLE) close (hTapeOutput);
}


//--------------------------------------------------------------------------

