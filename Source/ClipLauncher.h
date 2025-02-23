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
//  ClipLauncher.h
//  Bespoke
//
//  Created by Ryan Challinor on 1/17/15.
//
//

#ifndef __Bespoke__ClipLauncher__
#define __Bespoke__ClipLauncher__

#include <iostream>
#include "IAudioSource.h"
#include "EnvOscillator.h"
#include "IDrawableModule.h"
#include "Checkbox.h"
#include "Slider.h"
#include "DropdownList.h"
#include "Transport.h"
#include "ClickButton.h"
#include "OpenFrameworksPort.h"
#include "JumpBlender.h"

class Sample;
class Looper;

class ClipLauncher : public IAudioSource, public IDrawableModule, public IFloatSliderListener, public IIntSliderListener, public IDropdownListener, public ITimeListener, public IButtonListener
{
public:
   ClipLauncher();
   ~ClipLauncher();
   static IDrawableModule* Create() { return new ClipLauncher(); }


   void CreateUIControls() override;
   void Init() override;

   int GetRowY(int idx);

   //IAudioSource
   void Process(double time) override;
   void SetEnabled(bool enabled) override { mEnabled = enabled; }

   void CheckboxUpdated(Checkbox* checkbox) override;
   void FloatSliderUpdated(FloatSlider* slider, float oldVal) override;
   void IntSliderUpdated(IntSlider* slider, int oldVal) override;
   void DropdownClicked(DropdownList* list) override;
   void DropdownUpdated(DropdownList* list, int oldVal) override;
   void ButtonClicked(ClickButton* button) override;
   void OnTimeEvent(double time) override;

   virtual void LoadLayout(const ofxJSONElement& moduleInfo) override;
   virtual void SetUpFromSaveData() override;

private:
   void RecalcPos(double time, int idx);

   //IDrawableModule
   void DrawModule() override;
   bool Enabled() const override { return mEnabled; }
   void GetModuleDimensions(float& width, float& height) override;

   class SampleData
   {
   public:
      SampleData()
      : mSample(nullptr)
      , mNumBars(1)
      , mVolume(1)
      , mGrabCheckbox(nullptr)
      , mPlayCheckbox(nullptr)
      , mClipLauncher(nullptr)
      , mIndex(0)
      , mPlay(false)
      , mHasSample(false)
      {
      }
      ~SampleData();

      void Init(ClipLauncher* launcher, int index);
      void Draw();

      Sample* mSample;
      int mNumBars;
      float mVolume;
      Checkbox* mGrabCheckbox;
      Checkbox* mPlayCheckbox;
      ClipLauncher* mClipLauncher;
      int mIndex;
      bool mPlay;
      bool mHasSample;
   };

   Looper* mLooper;

   float mVolume;
   FloatSlider* mVolumeSlider;

   std::vector<SampleData> mSamples;
   JumpBlender mJumpBlender;
   ofMutex mSampleMutex;
};

#endif /* defined(__Bespoke__ClipLauncher__) */
