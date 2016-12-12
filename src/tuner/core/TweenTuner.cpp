#include "TweenTuner.h"

namespace cmd {

	namespace tuner_internal {

		//--------------------------------------------------------------
		TweenTuner::TweenTuner() {
			easing = NULL;
		}

		//--------------------------------------------------------------
		TweenTuner::~TweenTuner() {
			easing = NULL;
		}





		//--------------------------------------------------------------
		void TweenTuner::implSetupParameter() {
			// Setup label
			easingFunctionLabels = { Linear::None.getName() };
			easingTypeLabels = { "In", "Out", "InOut" };
			regex reg("(.*)InOut");
			smatch match;
			vector<const Easing*> easings = getEasings();
			for (vector<const Easing*>::iterator it = easings.begin(); it != easings.end(); ++it) {
				const Easing* easing = *it;
				string name = easing->getName();
				if (regex_match(name, match, reg)) {
					easingFunctionLabels.push_back(match[1]);
				}
			}

			// Setup parameter
			duration.set("duration", 1, 0, 10);

			easingIndex.set("easingIndex", 0, 0, easingFunctionLabels.size() - 1);
			easingType = "";
			easingName.set("easingName", Linear::None.getName());
			easing = &Linear::None;
		};

		//--------------------------------------------------------------
		void TweenTuner::implSetupGui(ofxGuiGroupExtended& gui) {
			// Duration
			{
				durationSlider.setup(duration);
				durationSlider.addListener(this, &TweenTuner::durationSliderHandler);
				gui.add(&durationSlider);
			}

			gui.add(new ofxGuiSpacer("interval"));

			// Easing
			{
				easingNameLabel.setup(easingName);
				easingNameLabel.setShowLabelName(false);
				gui.add(&easingNameLabel);

				easingIndexSlider.setup(easingIndex);
				easingIndexSlider.addListener(this, &TweenTuner::easingIndexSliderHandler);
				gui.add(&easingIndexSlider);

				easingTypeRadioButton.setup(easingTypeLabels, -1, 3, "Type");
				easingTypeRadioButton.addListener(this, &TweenTuner::easingTypeRadioButtonHandler);
				gui.add(easingTypeRadioButton.getGui());

				updateEasing();
			}
		};

		//--------------------------------------------------------------
		void TweenTuner::implApplyToCommand() {
			Tween* tween = getCommand<Tween>();
			if (tween != NULL) {
				tween->setDuration(duration);
				tween->setEasing(*easing);
			}
		};

		//--------------------------------------------------------------
		void TweenTuner::implLoad(ofxXmlSettings& settings, bool isLoaded) {
			// Get tween if exist
			Tween* tween = getCommand<Tween>();

			if (!isLoaded && tween != NULL) {
				// If saved setting is not found and tween is exist, UI values is set from tween command
				duration = tween->getDuration();
				easing = &tween->getEasing();
			} else {

				// Otherwise, UI values is set from default
				duration = settings.getValue("duration", duration);
				easing = &getEasingByName(settings.getValue("easing", easing->getName()));
			}

			// Synth easing
			{
				string name = easing->getName();
				regex reg("(.*?)((In|Out)+)");
				smatch match;
				if (regex_match(name, match, reg)) {
					string functionLabel = match[1];
					string typeLabel = match[2];
					easingIndex = distance(easingFunctionLabels.begin(), std::find(easingFunctionLabels.begin(), easingFunctionLabels.end(), functionLabel));
					easingType = typeLabel;
				} else {
					easingIndex = 0;
					easingType = "";
				}

				easingTypeRadioButton.select(easingType);
				updateEasing();
			}
		};

		//--------------------------------------------------------------
		void TweenTuner::implSave(ofxXmlSettings& settings) {
			settings.setValue("duration", duration);
			settings.setValue("easing", easing->getName());
		};





		//--------------------------------------------------------------
		void TweenTuner::updateEasing() {
			string functionLabel = easingFunctionLabels[easingIndex];
			string typeLabel = easingType;

			easing = &getEasingByName(functionLabel + typeLabel);

			if (easing->getName() == Linear::None.getName()) {
				easingName = easing->getName();
			} else {
				easingName = functionLabel + " " + typeLabel;
			}

			easingIndexSlider.setName(functionLabel);
		}





		//--------------------------------------------------------------
		void TweenTuner::durationSliderHandler(float& value) {
			applyToCommand();
		}

		//--------------------------------------------------------------
		void TweenTuner::easingIndexSliderHandler(int& value) {
			easingType = easingTypeRadioButton.getSelectedLabel();

			if (easingIndex == 0) {
				easingTypeRadioButton.select(-1);
			} else {
				if (easingType == "") {
					easingTypeRadioButton.select(0);
					easingType = easingTypeRadioButton.getSelectedLabel();
				}
			}

			updateEasing();
			applyToCommand();
		}

		//--------------------------------------------------------------
		void TweenTuner::easingTypeRadioButtonHandler(int& value) {
			easingType = easingTypeRadioButton.getSelectedLabel();
			updateEasing();
			applyToCommand();
		}
	}
}




