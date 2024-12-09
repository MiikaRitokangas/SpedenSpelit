#include "buttons.h"
#include "SpedenSpelit.h"

void initButtonsAndButtonInterrupts(void) {
  // See requirements for this function from buttons.h
  pinMode(BUTTON0_PIN, INPUT_PULLUP);  //setting button pinMode to INPUT_PULLUP
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(BUTTON3_PIN, INPUT_PULLUP);
  pinMode(BUTTON4_PIN, INPUT_PULLUP);
  PCICR = B00000100;   // enables port D as interupt AKA group 2
  PCMSK2 = B01111100;  // enables pins D2-D6
}

volatile unsigned long lastTimePressedButton = 0;  //last time interupt happened
static int debounceDelay = 50;                     // delay duration

ISR(PCINT2_vect) {
  /*
     Here you implement logic for handling
	 interrupts from 2,3,4,5 pins for Game push buttons
	 and for pin 6 for start Game push button.
   */

  //button debounce works, but ignores rapid button presses

  if (millis() - lastTimePressedButton > debounceDelay) {  //ignores input if it comes within debounceDelay from last imput
    lastTimePressedButton = millis();

    byte readButton0 = digitalRead(BUTTON0_PIN);  //reading button input
    byte readButton1 = digitalRead(BUTTON1_PIN);
    byte readButton2 = digitalRead(BUTTON2_PIN);
    byte readButton3 = digitalRead(BUTTON3_PIN);
    byte readButton4 = digitalRead(BUTTON4_PIN);

    if (readButton0 == LOW) {
      buttonNumber = 0;
    }
    //button 1
    if (readButton1 == LOW) {
      buttonNumber = 1;
    }
    //button 2
    if (readButton2 == LOW) {
      buttonNumber = 2;
    }
    //button 3
    if (readButton3 == LOW) {
      buttonNumber = 3;
    }
    //button 4
    if (readButton4 == LOW) {
      buttonNumber = 4;
    }
    lastTimePressedButton = millis();
  }
}