#pragma once

#include "ofMain.h"
#include "ofxGuiExtended.h"
#include "ofxXmlSettings.h"
#include "ofxCommand.h"
#include "core/TweenTuner.h"

namespace cmd {

	class CommandTuner {

		// ----------------------------------------
		//
		// MEMBER
		//
		// ----------------------------------------

	public:

	protected:

	private:
		bool isShown;
		bool isKeyboardEnabled;
		int toggleKey;
		vector<tuner_internal::TweenTuner*> tuners;
		ofxPanelExtended panel;





		// ----------------------------------------
		//
		// METHOD
		//
		// ----------------------------------------

	public:
		CommandTuner();
		~CommandTuner();

		void setup();
		void show();
		void hide();
		void toggle();

		void addTween(string commandName);
		void addWait(string commandName);

		bool getIsKeyboardEnabled();
		void setIsKeyboardEnabled(bool isEnabled);

		bool getToggleKey();
		void setToggleKey(int key);

		bool getIsShown();

	protected:

	private:
		void update();
		void draw();

		void updateHandler(ofEventArgs& event);
		void drawHandler(ofEventArgs& event);
		void keyPressedHandler(ofKeyEventArgs& event);
	};
}




