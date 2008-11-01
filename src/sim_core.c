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

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>

#include "sim_common.h"


//--------------------------------------------------------------------------
// System Status Variables

/// Simulated memory array.
byte MemData [65536];
/// Distinguishes readable and writable memory.
bool MemMask [65536];



//--------------------------------------------------------------------------
// Main

int main (int iArgC, char *apArgV [])
{
  // Module initialization

  SDL_Init (SDL_INIT_TIMER | SDL_INIT_VIDEO);

  CPUInitialize ();
  DSPInitialize ();
  KBDInitialize ();
  SNDInitialize ();
  TAPInitialize ();
  TIMInitialize ();

  // Temporary test with processor thread

  int hMonitor = open ("../data/monitors/M1", O_RDONLY);
  read (hMonitor, MemData + 0x8000, 4096);
  close (hMonitor);

//  int hGame = open ("../data/games-pmd1/KURE", O_RDONLY);
//  lseek (hGame, 0x3F, SEEK_SET);
//  read (hGame, MemData, 6379-0x3F);
//  close (hGame);

  int hGame = open ("../data/games-pmd1/KANKAN", O_RDONLY);
  lseek (hGame, 0x3F, SEEK_SET);
  read (hGame, MemData, 6977-0x3F);
  close (hGame);

  SDL_Thread *pProcessor = SDL_CreateThread (CPUThread, NULL);

  // Event loop

  bool bQuit = false;
  SDL_Event sEvent;

  while (!bQuit)
  {
    SDL_WaitEvent (&sEvent);
    switch (sEvent.type)
    {
      case SDL_KEYUP:
      case SDL_KEYDOWN:
        KBDEventHandler ((SDL_KeyboardEvent *) &sEvent);
        break;
      case SDL_VIDEORESIZE:
        DSPResizeHandler ((SDL_ResizeEvent *) &sEvent);
        break;
      case SDL_USEREVENT:
        DSPPaintHandler ();
        break;
      case SDL_QUIT:
        bQuit = true;
        break;
    }
  }

  // Module shutdown

  TIMShutdown ();
  TAPShutdown ();
  SNDShutdown ();
  KBDShutdown ();
  DSPShutdown ();
  CPUShutdown ();

  SDL_Quit ();

  return (0);
}


//--------------------------------------------------------------------------

