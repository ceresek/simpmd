/*

SIM_SPEAKER.C

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

/// Singleton audio specification.
static SDL_AudioSpec sAudioSpec;

/** Singleton cyclic audio buffer.
 *
 *  The particular size of the audio buffer is not really
 *  all that important, proper size operator is used in
 *  code. It must not be too large though, otherwise
 *  timing imprecisions might lead to accumulated
 *  latency.
 */
static byte aAudioBuffer [1024];
/// Head of the cyclic audio buffer.
static byte *volatile pAudioBufferHead;
/// Tail of the cyclic audio buffer.
static byte *volatile pAudioBufferTail;
/// Mutex protecting the cyclic audio buffer.
static SDL_mutex *pAudioBufferLock;

/// Last generated value of simulated clock
static int iLastClock;
/// Last written value of simulated speaker.
static byte iLastSpeaker;

/// Desired sampling rate of the audio output.
#define PMD_AUDIO_RATE          44100

/// Speaker frequency mask.
#define PMD_SPEAKER_FREQUENCY   (3 << 0)
/// Speaker enable mask.
#define PMD_SPEAKER_ENABLE      (1 << 2)


//--------------------------------------------------------------------------
// Buffer operations

/// Increments pointer in the cyclic audio buffer.
byte *SNDIncrementInBuffer (byte *pPosition)
{
  byte *pResult = pPosition + 1;
  if (pResult >= aAudioBuffer + sizeof (aAudioBuffer))
  {
    pResult -= sizeof (aAudioBuffer);
  }
  return (pResult);
}


/** Flushes the cyclic audio buffer.
 */
void SNDFlushBuffer ()
{
  SDL_LockMutex (pAudioBufferLock);
  pAudioBufferHead = pAudioBufferTail;
  SDL_UnlockMutex (pAudioBufferLock);
}


/** Reads pattern from the cyclic audio buffer.
 *
 *  @arg pBuffer The buffer to fill.
 *  @arg iCount  The number of samples.
 */
void SNDReadBuffer (byte *pBuffer, int iCount)
{
  byte bData = 0;
  SDL_LockMutex (pAudioBufferLock);
  for (int i = 0 ; i < iCount ; i ++)
  {
    if (pAudioBufferHead != pAudioBufferTail)
    {
      bData = *pAudioBufferHead;
      pAudioBufferHead = SNDIncrementInBuffer (pAudioBufferHead);
    }
    *pBuffer = bData;
    pBuffer ++;
  }
  SDL_UnlockMutex (pAudioBufferLock);
}


/** Writes pattern to the cyclic audio buffer.
 *
 *  @arg iSample The value to put.
 *  @arg iCount  The number of samples.
 */
void SNDWriteBuffer (byte bSample, int iCount)
{
  SDL_LockMutex (pAudioBufferLock);
  for (int i = 0 ; i < iCount ; i ++)
  {
    (*pAudioBufferTail) = bSample;
    pAudioBufferTail = SNDIncrementInBuffer (pAudioBufferTail);
    if (pAudioBufferTail == pAudioBufferHead)
    {
      pAudioBufferHead = SNDIncrementInBuffer (pAudioBufferHead);
    }
  }
  SDL_UnlockMutex (pAudioBufferLock);
}


//--------------------------------------------------------------------------
// Sound generation

/** Synchronizes simulated clock and actual time.
 */
void SNDSynchronize ()
{
  // Synchronize the time.
  iLastClock = Clock;
  // Synchronize the buffer.
  SNDFlushBuffer ();
}


/** Generate sound.
 *
 *  Calculates position and generates sound.
 *
 *  @arg iSpeaker Speaker register value.
 */
void SNDGenerate (byte iSpeaker)
{
  // Calculate current position in the cyclic audio buffer
  // based on the known sampling rate and the known clock
  // frequency.
  int iDeltaInClocks = Clock - iLastClock;
  int iDeltaInSamples = (iDeltaInClocks * PMD_AUDIO_RATE) / PMD_CLOCK;

  // Fill the buffer with the required number of samples.
  SNDWriteBuffer ((iSpeaker & PMD_SPEAKER_ENABLE) ? 255 : 0, iDeltaInSamples);

  // Avoid accumulative error by only advancing the clock by sample value.
  iDeltaInClocks = (iDeltaInSamples * PMD_CLOCK) / PMD_AUDIO_RATE;
  iLastClock += iDeltaInClocks;
}


//--------------------------------------------------------------------------
// Port operations

/** Write to speaker register.
 *
 *  Fills the cyclic audio buffer by data corresponding
 *  to the simulated speaker. Only the binary speaker
 *  output is simulated for now.
 *
 *  @arg iClock Current value of simulated clock.
 *  @arg iData The written value.
 */
void SNDWriteSpeaker (byte iData)
{
  // Generate whatever sound was heard until now.
  SNDGenerate (iLastSpeaker);
  // Set what sound is heard from now on.
  iLastSpeaker = iData;
}


//--------------------------------------------------------------------------
// Callback handlers

/** Handler for filling the sound buffer.
 *
 *  @arg pParameters Callback parameters.
 *  @arg pBuffer Sound buffer address.
 *  @arg iLength Sound buffer length.
 */
void SNDFillBufferCallback (void *pParameters, Uint8 *pBuffer, int iLength)
{
  // Generate whatever sound was heard until now.
  SNDGenerate (iLastSpeaker);
  // Fill the buffer with the generated sound.
  SNDReadBuffer (pBuffer, iLength);
}


//--------------------------------------------------------------------------
// Initialization and shutdown

void SNDInitialize ()
{
  // Initialize the cyclic audio buffer ...
  pAudioBufferLock = SDL_CreateMutex ();
  SDL_LockMutex (pAudioBufferLock);
  pAudioBufferHead = aAudioBuffer;
  pAudioBufferTail = aAudioBuffer;
  SDL_UnlockMutex (pAudioBufferLock);

  // Prepare audio parameters ...
  sAudioSpec.freq = PMD_AUDIO_RATE;
  sAudioSpec.format = AUDIO_U8;
  sAudioSpec.samples = 512;
  sAudioSpec.channels = 1;
  sAudioSpec.userdata = NULL;
  sAudioSpec.callback = SNDFillBufferCallback;

  // Open the audio device ...
  int iResult = SDL_OpenAudio (&sAudioSpec, NULL);
  assert (iResult == 0);

  // Check if audio parameters were granted ...
  assert (sAudioSpec.freq == PMD_AUDIO_RATE);
  assert (sAudioSpec.format == AUDIO_U8);

  // Start the callback ...
  SDL_PauseAudio (0);
}


void SNDShutdown ()
{
  // Close the audio device ...
  SDL_CloseAudio ();

  // Free the audio buffer mutex ...
  SDL_DestroyMutex (pAudioBufferLock);
}


//--------------------------------------------------------------------------

