/**
    bespoke synth, a software modular synthesizer
    Copyright (C) 2021 Ryan Challinor (contact: awwbees@gmail.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/
//
//  SingleOscillatorVoice.h
//  modularSynth
//
//  Created by Ryan Challinor on 12/4/13.
//
//

#ifndef __modularSynth__SingleOscillatorVoice__
#define __modularSynth__SingleOscillatorVoice__

#include <iostream>
#include "OpenFrameworksPort.h"
#include "IMidiVoice.h"
#include "IVoiceParams.h"
#include "ADSR.h"
#include "EnvOscillator.h"
#include "LFO.h"
#include "BiquadFilter.h"

#define SINGLEOSCILLATOR_NO_CUTOFF 10000

class OscillatorVoiceParams : public IVoiceParams
{
public:
   ::ADSR mAdsr;
   float mVol;
   float mPulseWidth;
   bool mSync;
   float mSyncFreq;
   float mMult;
   OscillatorType mOscType;
   float mDetune;
   float mShuffle;
   float mPhaseOffset;
   int mUnison;
   float mUnisonWidth;
   float mSoften;

   float mFilterCutoffMax;
   float mFilterCutoffMin;
   float mFilterQ;
   ::ADSR mFilterAdsr;

   float mVelToVolume;
   float mVelToEnvelope;

   bool mLiteCPUMode;
};

class SingleOscillatorVoice : public IMidiVoice
{
public:
   SingleOscillatorVoice(IDrawableModule* owner = nullptr);
   ~SingleOscillatorVoice();

   // IMidiVoice
   void Start(double time, float amount) override;
   void Stop(double time) override;
   void ClearVoice() override;
   bool Process(double time, ChannelBuffer* out, int oversampling) override;
   void SetVoiceParams(IVoiceParams* params) override;
   bool IsDone(double time) override;

   static float GetADSRScale(float velocity, float velToEnvelope);

   static const int kMaxUnison = 8;

private:
   void DoParameterUpdate(int samplesIn,
                          float& pitch,
                          float& freq,
                          float& vol);

   struct OscData
   {
      OscData()
      : mPhase(0)
      , mSyncPhase(0)
      , mOsc(kOsc_Square)
      , mDetuneFactor(0)
      {}
      float mPhase;
      float mSyncPhase;
      Oscillator mOsc;
      float mDetuneFactor;
      float mCurrentPhaseInc;
   };
   OscData mOscData[kMaxUnison];
   ::ADSR mAdsr;
   OscillatorVoiceParams* mVoiceParams;

   ::ADSR mFilterAdsr;
   BiquadFilter mFilterLeft;
   BiquadFilter mFilterRight;
   bool mUseFilter;

   IDrawableModule* mOwner;
};

#endif /* defined(__modularSynth__SingleOscillatorVoice__) */
