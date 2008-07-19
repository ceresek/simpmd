/*

SIM_CORE.C

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

#include "sim_common.h"


//--------------------------------------------------------------------------
// System Status Variables

// MemData      Simulated memory array
// MemMask      Distinguishes readable and writable memory

byte MemData [65536];
bool MemMask [65536];

//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// Main

int main (int iArgC, char *apArgV [])
{
  return (0);
}

//--------------------------------------------------------------------------

