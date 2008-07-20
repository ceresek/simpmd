/*

SIM_DISPLAY.C

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

#include <assert.h>

#include <SDL/SDL.h>

#include "sim_common.h"


//--------------------------------------------------------------------------
// Data

/// Singleton screen surface.
static SDL_Surface *pScreen;

/// Paint timer
static SDL_TimerID iPaintTimer;


static SDL_Color sColorBlack = {   0,   0,   0 };
static SDL_Color sColorWhite = { 255, 255, 255 };
static SDL_Color sColorGray  = { 192, 192, 192 };

#define DSP_COLOR_BLACK         0
#define DSP_COLOR_WHITE         1
#define DSP_COLOR_GRAY          2


/// Base address of the video memory
#define PMD_VRAM_BASE           0xC000
/// Width of the visible video memory line in bytes
#define PMD_VRAM_WIDTH          48
/// Width of the invisible video memory line in bytes
#define PMD_VRAM_BLANK          16
/// Height of the video memory area in lines
#define PMD_VRAM_HEIGHT         256

/// Gray attribute mask
#define PMD_PIXEL_GRAY          (1 << 6)
/// Blinking attribute bask
#define PMD_PIXEL_BLINK         (1 << 7)

/// Blinking rate in miliseconds
#define PMD_BLINK_RATE          512

/// Screen paint rate in miliseconds
#define PMD_REFRESH             20

//--------------------------------------------------------------------------
// Screen paint

/** Paint the screen content.
 *
 *  Decodes the memory content of the simulated machine
 *  and paints the screen content accordingly, using
 *  direct writing and double buffering.
 */
void DSPPaint ()
{
  // Determine whether blinking pixels would now be visible
  bool bBlinkVisible = (SDL_GetTicks () / PMD_BLINK_RATE) & 1;

  SDL_LockSurface (pScreen);

  // Just decode the memory content and paint the screen content
  byte *pSource = & MemData [PMD_VRAM_BASE];
  byte *pTarget = (byte *) pScreen->pixels;
  for (int iLine = 0 ; iLine < PMD_VRAM_HEIGHT ; iLine ++)
  {
    for (int iByte = 0 ; iByte < PMD_VRAM_WIDTH ; iByte ++)
    {
      byte iData = *pSource;

      // All pixels in one byte share color
      byte iColor = (iData & PMD_PIXEL_GRAY) ? iColor = DSP_COLOR_GRAY
                                             : iColor = DSP_COLOR_WHITE;
      if ((iData & PMD_PIXEL_BLINK) && !bBlinkVisible) iColor = DSP_COLOR_BLACK;

      // The inner cycle is unrolled for speed

#define DSPPaintPixel                                           \
  *pTarget = (iData & 1) ? iColor : DSP_COLOR_BLACK;            \
  iData >>= 1;                                                  \
  pTarget ++;

      DSPPaintPixel
      DSPPaintPixel
      DSPPaintPixel
      DSPPaintPixel
      DSPPaintPixel
      DSPPaintPixel

#undef DSPPaintPixel

      pSource ++;
    }

    pSource += PMD_VRAM_BLANK;
    pTarget += pScreen->pitch - PMD_VRAM_WIDTH * 6;
  }

  SDL_UnlockSurface (pScreen);

  // Make the content visible
  SDL_Flip (pScreen);
}

//--------------------------------------------------------------------------
// Timer handlers

/** Handler for painting the screen content.
 *
 *  Pushes an event corresponding to the timer on the
 *  event queue to maintain the threading rules.
 */
Uint32 DSPPaintTimer (Uint32 iInterval, void *pArgs)
{
  SDL_Event sEvent;
  sEvent.type = SDL_USEREVENT;
  sEvent.user.code = 0;
  sEvent.user.data1 = NULL;
  sEvent.user.data2 = NULL;
  SDL_PushEvent (&sEvent);

  return (PMD_REFRESH);
}

//--------------------------------------------------------------------------
// Initialization and shutdown

void DSPInitialize ()
{
  SDL_WM_SetCaption ("SimPMD", "SimPMD");

  // Create the surface to draw upon ...
  pScreen = SDL_SetVideoMode (288, 256, 8, SDL_HWSURFACE | SDL_DOUBLEBUF);
  assert (pScreen != NULL);

  // Create a palette with the required colors ...
  SDL_SetColors (pScreen, &sColorBlack, DSP_COLOR_BLACK, 1);
  SDL_SetColors (pScreen, &sColorWhite, DSP_COLOR_WHITE, 1);
  SDL_SetColors (pScreen, &sColorGray,  DSP_COLOR_GRAY,  1);

  // Start the timer that paints the screen repeatedly ...
  iPaintTimer = SDL_AddTimer (PMD_REFRESH, DSPPaintTimer, NULL);
}


void DSPShutdown ()
{
  // Stop the timer that paints the screen repeatedly ...
  SDL_RemoveTimer (iPaintTimer);

  // Freeing the screen might be unnecessary ...
  SDL_FreeSurface (pScreen);
}

//--------------------------------------------------------------------------

