#include <Arduino.h>
#include <Mouse.h>
#include <Keyboard.h>

// Rotary Encoder Inputs
#define CLK A3
#define DT A2
#define SW A1
#define LED 17

// Dial variables
int currentStateCLK;
int lastStateCLK;
int counter = 0;

// Button variables
int stateLED = LOW;
int btnRead = 0;
long debounce = 200;
long time = 0;

void setup()
{
	// Set encoder pins as inputs
	pinMode(CLK, INPUT_PULLUP);
	pinMode(DT, INPUT_PULLUP);
	pinMode(SW, INPUT_PULLUP);
	pinMode(LED, OUTPUT);

	Keyboard.begin();

	lastStateCLK = digitalRead(CLK);
}

void loop()
{
	// Dial turn
	currentStateCLK = digitalRead(CLK);

	if (currentStateCLK != lastStateCLK && currentStateCLK == 1) {
		counter = digitalRead(DT) != currentStateCLK ? 1 : -1;

		if (stateLED == HIGH) {
			
			Keyboard.press(KEY_LEFT_SHIFT);
		}

		Mouse.move(0, 0, counter);
		Keyboard.release(KEY_LEFT_SHIFT);
	}

	lastStateCLK = currentStateCLK;
	
	// Button click
	int tempRead = digitalRead(SW);
	
	if (tempRead == HIGH && btnRead == LOW && millis() - time > debounce) {
		if (stateLED == HIGH)
			stateLED = LOW;
		else
			stateLED = HIGH;
		time = millis();
	}

	digitalWrite(LED, stateLED);
	btnRead = tempRead;
}