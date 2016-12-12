#pragma once

#include "ofMain.h"
#include "ofxGuiExtended.h"

namespace cmd {

	namespace tuner_internal {

		class RadioButton {

			// ----------------------------------------
			//
			// MEMBER
			//
			// ----------------------------------------

		public:
			ofEvent<int> onSelect;

		protected:

		private:
			ofxGuiMatrix container;

			vector<string> labels;
			vector<ofxMinimalButton*> buttons;

			string selectedLabel;
			int selectedIndex;





			// ----------------------------------------
			//
			// METHOD
			//
			// ----------------------------------------

		public:
			RadioButton();
			~RadioButton();

			void setup(const vector<string> labels, int defaultSelected = 0, int numCols = 1, string name = "");

			void select(int index);
			void select(string label);

			ofxGuiGroup* getGui();
			int getNumButtons();
			const vector<string> getLabels();
			int getSelectedIndex();
			string getSelectedLabel();

			template<class ListenerClass, typename ListenerMethod>
			void addListener(ListenerClass* listener, ListenerMethod method) {
				ofAddListener(onSelect, listener, method);
			};

			template<class ListenerClass, typename ListenerMethod>
			void removeListener(ListenerClass* listener, ListenerMethod method) {
				ofRemoveListener(onSelect, listener, method);
			};

		protected:

		private:
			void addListeners();
			void removeListeners();

			void buttonHandler(const void* sender);
		};
	}
}




