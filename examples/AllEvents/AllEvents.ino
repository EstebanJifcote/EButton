#include "Arduino.h"
#include "EButton.h"

EButton button(2);

// ------- Printing event details --------
void print(EButton &btn) {
	Serial.print(F(" [pressed="));
	Serial.print(btn.isButtonPressed());
	Serial.print(F(", clicks="));
	Serial.print(btn.getClicks());
	Serial.print(F(", startTime="));
	Serial.print(btn.getStartTime());
	Serial.print(F(", lastTransitionTime="));
	Serial.print(btn.getLastTransitionTime());
	Serial.println(F("]"));
}

// ------- Handler methods --------
void transitionHandler(EButton &btn) {
	Serial.print(F("TRANSITION"));
	print(btn);
}
void eachClickHandler(EButton &btn) {
	Serial.print(F("EACH_CLICK"));
	print(btn);
}
void singleClickHandler(EButton &btn) {
	Serial.print(F("SINGLE_CLICK"));
	print(btn);
}
void doubleClickHandler(EButton &btn) {
	Serial.print(F("DOUBLE_CLICK"));
	print(btn);
}
void anyClickHandler(EButton &btn) {
	Serial.print(F("ANY_CLICK"));
	print(btn);
}

void pressStartHandler(EButton &btn) {
	Serial.print(F("PRESS_START"));
	print(btn);
}

unsigned long t;
void duringPressHandler(EButton &btn) {
	if ((unsigned long) (millis() - t) > 1000) {
		// Print once a second
		Serial.print(F("DURING_PRESS"));
		print(btn);
		t = millis();
	}
}

void pressEndHandler(EButton &btn) {
	Serial.print(F("PRESS_END"));
	print(btn);
}

// ------- Setting up the driver and registering listeners --------
void setup() {
	Serial.begin(115200);
	Serial.println(F("\nEButton Demo"));

	button.setDebounceTime(EBUTTON_DEFAULT_DEBOUNCE);		// not required if using default
	button.setClickTime(EBUTTON_DEFAULT_CLICK);				// not required if using default
	button.setLongPressTime(EBUTTON_DEFAULT_LONG_PRESS);	// not required if using default

	button.attachTransition(transitionHandler);
	button.attachEachClick(eachClickHandler);
	button.attachAnyClick(anyClickHandler);
	button.attachSingleClick(singleClickHandler);
	button.attachDoubleClick(doubleClickHandler);
	button.attachLongPressStart(pressStartHandler);
	button.attachDuringLongPress(duringPressHandler);
	button.attachLongPressEnd(pressEndHandler);
}

void loop() {
	// Ticking the driver in a loop
	button.tick();
}
