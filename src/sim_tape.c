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

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#include <SDL/SDL.h>

#include "sim_common.h"


//--------------------------------------------------------------------------
// Data

/// Tape input file handle.
static int hTapeInput;


//--------------------------------------------------------------------------
// Port operations

/** Read from tape data register.
 */
byte TAPReadData ()
{
  byte iData;
  read (hTapeInput, &iData, 1);
  return (iData);
}


/** Write to tape data register.
 *
 *  @arg iData The written value.
 */
void TAPWriteData (byte iData)
{
}


//--------------------------------------------------------------------------
// Initialization and shutdown

void TAPInitialize ()
{
  hTapeInput = open ("../data/games-pmd1/MANIC-1", O_RDONLY);
}


void TAPShutdown ()
{
  close (hTapeInput);
}


//--------------------------------------------------------------------------

