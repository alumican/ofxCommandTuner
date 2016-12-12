#pragma once

#include "ofMain.h"
#include "ofxGuiExtended.h"
#include "ofxXmlSettings.h"
#include "ofxCommand.h"

namespace cmd {

	namespace tuner_internal {

		class Tuner {

			// ----------------------------------------
			//
			// MEMBER
			//
			// ----------------------------------------

		public:

		protected:

		private:
			string commandName;
			ofxXmlSettings settings;

			ofxGuiGroupExtended container;
			ofxMinimalButton loadButton;
			ofxMinimalButton saveButton;





			// ----------------------------------------
			//
			// METHOD
			//
			// ----------------------------------------

		public:
			Tuner();
			virtual ~Tuner();

			void setup(string commandName);

			string getCommandName();
			ofxGuiGroupExtended* getGui();

		protected:
			virtual void implSetupParameter();
			virtual void implSetupGui(ofxGuiGroupExtended& gui);
			virtual void implApplyToCommand();
			virtual void implLoad(ofxXmlSettings& settings, bool isLoaded);
			virtual void implSave(ofxXmlSettings& settings);

			void applyToCommand();

			template <class T>
			T* getCommand() {
				return dynamic_cast<T*>(Command::getCommandByName(commandName));
			};

		private:
			void load();
			void save();

			void loadButtonHandler();
			void saveButtonHandler();
		};
	}
}




