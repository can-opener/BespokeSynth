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
/*
  ==============================================================================

    NoteHocket.h
    Created: 19 Dec 2019 10:40:58pm
    Author:  Ryan Challinor

  ==============================================================================
*/

#pragma once

#include <iostream>
#include "NoteEffectBase.h"
#include "IDrawableModule.h"
#include "Checkbox.h"
#include "INoteSource.h"
#include "Slider.h"

class NoteHocket : public INoteReceiver, public INoteSource, public IDrawableModule, public IFloatSliderListener
{
public:
   NoteHocket();
   static IDrawableModule* Create() { return new NoteHocket(); }


   void CreateUIControls() override;

   void PlayNote(double time, int pitch, int velocity, int voiceIdx, ModulationParameters modulation) override;
   void SendCC(int control, int value, int voiceIdx = -1) override;

   void FloatSliderUpdated(FloatSlider* slider, float oldVal) override {}

   virtual void LoadLayout(const ofxJSONElement& moduleInfo) override;
   virtual void SetUpFromSaveData() override;
   virtual void SaveLayout(ofxJSONElement& moduleInfo) override;

private:
   //IDrawableModule
   void DrawModule() override;
   void GetModuleDimensions(float& width, float& height) override
   {
      width = mWidth;
      height = mHeight;
   }
   bool Enabled() const override { return true; }

   void SendNoteToIndex(int index, double time, int pitch, int velocity, int voiceIdx, ModulationParameters modulation);

   static const int kMaxDestinations = 5;
   float mWeight[kMaxDestinations];
   FloatSlider* mWeightSlider[kMaxDestinations];
   AdditionalNoteCable* mDestinationCables[kMaxDestinations];
   float mWidth;
   float mHeight;
   int mLastNoteDestinations[128];
};
