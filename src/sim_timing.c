/*

SIM_TIMING.C

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

#include <time.h>

#include <SDL/SDL.h>

#include "sim_common.h"


//--------------------------------------------------------------------------
// Data

/// Last synchronized value of actual time
static struct timespec sLastTime;
/// Last synchronized value of simulated clock
static int iLastClock;


//--------------------------------------------------------------------------
// Sleeping

/// Synchronizes simulated clock and actual time.
void TIMSynchronize ()
{
  clock_gettime (CLOCK_MONOTONIC, &sLastTime);
  iLastClock = Clock;
}


/// Advances simulated clock and actual time by sleeping.
void TIMAdvance (int iClock)
{
  // Convert the simulated clock delta into the actual time delta
  ulong iSleep = iClock - iLastClock;
  iSleep *= 1000000000;
  iSleep /= PMD_CLOCK;

  // Convert the actual time delta into the actual time required
  // for the sleep function and sleep until that time is reached
  ulong iNanos = sLastTime.tv_nsec + iSleep;
  sLastTime.tv_nsec = iNanos % 1000000000;
  sLastTime.tv_sec += iNanos / 1000000000;
  clock_nanosleep (CLOCK_MONOTONIC, TIMER_ABSTIME, &sLastTime, NULL);

  // Update the last simulated clock
  iLastClock = iClock;
}


//--------------------------------------------------------------------------
// Initialization and shutdown

void TIMInitialize ()
{
  // Nothing really ...
}


void TIMShutdown ()
{
  // Nothing really ...
}


//--------------------------------------------------------------------------

