#include "RadioButton.h"

namespace cmd {

	namespace tuner_internal {

		//--------------------------------------------------------------
		RadioButton::RadioButton() {
		}

		//--------------------------------------------------------------
		RadioButton::~RadioButton() {
			container.clear();
		}





		//--------------------------------------------------------------
		void RadioButton::setup(const vector<string> labels, int defaultSelected, int numCols, string name) {
			this->labels = labels;

			container.setup(name, numCols);
			container.setName(name);
			container.allowMultipleActiveToggles(false);

			for (vector<string>::const_iterator it = labels.begin(); it != labels.end(); ++it) {
				ofxMinimalButton* button = new ofxMinimalButton(*it);
				buttons.push_back(button);
				container.add(button);
			}

			selectedLabel = "";
			selectedIndex = -1;
			select(defaultSelected);
		}





		//--------------------------------------------------------------
		void RadioButton::select(int index) {
			if (index < 0 || index >= buttons.size()) index = -1;
			if (index == selectedIndex) return;
			selectedIndex = index;

			removeListeners();

			int numButtons = buttons.size();
			for (int i = 0; i < numButtons; ++i) {
				ofxMinimalButton* button = buttons[i];
				button->getParameter().cast<bool>() = i == selectedIndex;
			}
			selectedLabel = selectedIndex != -1 ? labels[selectedIndex] : "";

			addListeners();

			ofNotifyEvent(onSelect, selectedIndex, this);
		}

		//--------------------------------------------------------------
		void RadioButton::select(string label) {
			int index = distance(labels.begin(), std::find(labels.begin(), labels.end(), label));
			if (index < labels.size()) {
				select(index);
			}
		}





		//--------------------------------------------------------------
		void RadioButton::addListeners() {
			for (vector<ofxMinimalButton*>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
				(*it)->addListener(this, &RadioButton::buttonHandler);
			}
		}

		//--------------------------------------------------------------
		void RadioButton::removeListeners() {
			for (vector<ofxMinimalButton*>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
				(*it)->removeListener(this, &RadioButton::buttonHandler);
			}
		}





		//--------------------------------------------------------------
		void RadioButton::buttonHandler(const void* sender) {
			ofxMinimalButton* button = const_cast<ofxMinimalButton*>(static_cast<const ofxMinimalButton*>(sender));
			if (!ofGetMousePressed()) {
				select(button->getName());
			}
		}





		//--------------------------------------------------------------
		int RadioButton::getNumButtons() {
			return buttons.size();
		}

		//--------------------------------------------------------------
		const vector<string> RadioButton::getLabels() {
			return labels;
		}

		//--------------------------------------------------------------
		int RadioButton::getSelectedIndex() {
			return selectedIndex;
		}

		//--------------------------------------------------------------
		string RadioButton::getSelectedLabel() {
			return selectedLabel;
		}

		//--------------------------------------------------------------
		ofxGuiGroup* RadioButton::getGui() {
			return &container;
		}
	}
}




