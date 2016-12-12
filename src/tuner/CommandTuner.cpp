#include "CommandTuner.h"

namespace cmd {

	//--------------------------------------------------------------
	CommandTuner::CommandTuner() {
	}

	//--------------------------------------------------------------
	CommandTuner::~CommandTuner() {
		setIsKeyboardEnabled(false);
		hide();
		panel.clear();
	}





	//--------------------------------------------------------------
	void CommandTuner::setup() {
		panel.setup("ofxCommandTuner", "", 20, 20);
		panel.setName("ofxCommandTuner");

		panel.setSize(350, 0);

		isKeyboardEnabled = false;
		setIsKeyboardEnabled(true);
		setToggleKey(OF_KEY_RETURN);

		isShown = true;
		hide();
	}

	//--------------------------------------------------------------
	void CommandTuner::show() {
		if (isShown) return;
		isShown = true;

		ofAddListener(ofEvents().update, this, &CommandTuner::updateHandler);
		ofAddListener(ofEvents().draw, this, &CommandTuner::drawHandler);

		update();
	}

	//--------------------------------------------------------------
	void CommandTuner::hide() {
		if (!isShown) return;
		isShown = false;

		ofRemoveListener(ofEvents().update, this, &CommandTuner::updateHandler);
		ofRemoveListener(ofEvents().draw, this, &CommandTuner::drawHandler);
	}

	//--------------------------------------------------------------
	void CommandTuner::toggle() {
		isShown ? hide() : show();
	}

	//--------------------------------------------------------------
	void CommandTuner::update() {
	}

	//--------------------------------------------------------------
	void CommandTuner::draw() {
		panel.draw();
	}





	//--------------------------------------------------------------
	void CommandTuner::addTween(string commandName) {
		tuner_internal::TweenTuner* tuner = new tuner_internal::TweenTuner();
		tuner->setup(commandName);

		ofxGuiGroupExtended* group = tuner->getGui();
		panel.add(new ofxGuiSpacer("spacer-" + commandName));
		panel.add(group);
		group->minimize();

		tuners.push_back(tuner);
	}

	//--------------------------------------------------------------
	void CommandTuner::addWait(string commandName) {
	}





	//--------------------------------------------------------------
	void CommandTuner::updateHandler(ofEventArgs& event) {
		update();
	}

	//--------------------------------------------------------------
	void CommandTuner::drawHandler(ofEventArgs& event) {
		draw();
	}

	//--------------------------------------------------------------
	void CommandTuner::keyPressedHandler(ofKeyEventArgs& event) {
		if (event.key == toggleKey) {
			toggle();
		}
	}





	//--------------------------------------------------------------
	bool CommandTuner::getIsKeyboardEnabled() {
		return isKeyboardEnabled;
	}

	//--------------------------------------------------------------
	void CommandTuner::setIsKeyboardEnabled(bool isEnabled) {
		if (isEnabled == isKeyboardEnabled) return;
		isKeyboardEnabled = isEnabled;
		if (isKeyboardEnabled) {
			ofAddListener(ofEvents().keyPressed, this, &CommandTuner::keyPressedHandler);
		} else {
			ofRemoveListener(ofEvents().keyPressed, this, &CommandTuner::keyPressedHandler);
		}
	}

	//--------------------------------------------------------------
	bool CommandTuner::getToggleKey() {
		return toggleKey;
	}

	//--------------------------------------------------------------
	void CommandTuner::setToggleKey(int key) {
		toggleKey = key;
	}





	//--------------------------------------------------------------
	bool CommandTuner::getIsShown() {
		return isShown;
	}
}




