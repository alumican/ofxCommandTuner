#pragma once

#include <regex>
#include "Tuner.h"
#include "RadioButton.h"

namespace cmd {

	namespace tuner_internal {

		class TweenTuner : public Tuner {

			// ----------------------------------------
			//
			// MEMBER
			//
			// ----------------------------------------

		public:

		protected:

		private:
			ofParameter<float> duration;

			const Easing* easing;
			ofParameter<int> easingIndex;
			string easingType;
			ofParameter<string> easingName;

			vector<string> easingFunctionLabels;
			vector<string> easingTypeLabels;

			ofxFloatSlider durationSlider;
			ofxLabelExtended easingNameLabel;
			ofxIntSlider easingIndexSlider;
			RadioButton easingTypeRadioButton;





			// ----------------------------------------
			//
			// METHOD
			//
			// ----------------------------------------

		public:
			TweenTuner();
			virtual ~TweenTuner();

		protected:
			virtual void implSetupParameter();
			virtual void implSetupGui(ofxGuiGroupExtended& gui);
			virtual void implApplyToCommand();
			virtual void implLoad(ofxXmlSettings& settings, bool isLoaded);
			virtual void implSave(ofxXmlSettings& settings);

		private:
			void updateEasing();

			void durationSliderHandler(float& value);
			void easingIndexSliderHandler(int& value);
			void easingTypeRadioButtonHandler(int& value);
		};
	}
}




