#include "Tuner.h"

namespace cmd {

	namespace tuner_internal {

		//--------------------------------------------------------------
		Tuner::Tuner() {
		}

		Tuner::~Tuner() {
			container.clear();
		};





		//--------------------------------------------------------------
		void Tuner::setup(string commandName) {
			this->commandName = commandName;

			// Parameters
			implSetupParameter();
			load();

			// Interface
			container.setup(commandName);
			container.setName(commandName);

			implSetupGui(container);

			container.add(new ofxGuiSpacer("spacer"));

			loadButton.setup("Load");
			loadButton.addListener(this, &Tuner::loadButtonHandler);
			container.add(&loadButton);

			saveButton.setup("Save");
			saveButton.addListener(this, &Tuner::saveButtonHandler);
			container.add(&saveButton);
		}

		//--------------------------------------------------------------
		void Tuner::load() {
			bool isLoaded = settings.load("ofxcommandtuner/" + commandName + ".xml");
			implLoad(settings, isLoaded);
			if (isLoaded) {
				applyToCommand();
			}
		}

		void Tuner::save() {
			implSave(settings);
			settings.save("ofxcommandtuner/" + commandName + ".xml");
		}

		//--------------------------------------------------------------
		void Tuner::applyToCommand() {
			implApplyToCommand();
		}





		//--------------------------------------------------------------
		void Tuner::loadButtonHandler() {
			load();
		}

		void Tuner::saveButtonHandler() {
			save();
		}





		//--------------------------------------------------------------
		string Tuner::getCommandName() {
			return commandName;
		}

		ofxGuiGroupExtended* Tuner::getGui() {
			return &container;
		}





		//--------------------------------------------------------------
		void Tuner::implSetupParameter() {
		}

		void Tuner::implSetupGui(ofxGuiGroupExtended& gui) {
		}

		void Tuner::implApplyToCommand() {
		}

		void Tuner::implLoad(ofxXmlSettings& settings, bool isLoaded) {
		}

		void Tuner::implSave(ofxXmlSettings& settings) {
		}
	}
}




