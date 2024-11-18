#include "buttons.h"
#include "SpedenSpelit.h"

void initButtonsAndButtonInterrupts(void)
{
  // See requirements for this function from buttons.h
  pinMode(BUTTON0_PIN, INPUT_PULLUP); //setting button pinMode to INPUT_PULLUP
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(BUTTON3_PIN, INPUT_PULLUP);
  pinMode(BUTTON4_PIN, INPUT_PULLUP);
  PCICR = B00000100; // enables port D as interupt AKA group 2
  PCMSK2 = B01111100; // enables pins D2-D6
}

ISR(PCINT2_vect) {
   /*
     Here you implement logic for handling
	 interrupts from 2,3,4,5 pins for Game push buttons
	 and for pin 6 for start Game push button.
   */
  byte readButton0 = digitalRead(BUTTON0_PIN);  //reading button input
  byte readButton1 = digitalRead(BUTTON1_PIN);
  byte readButton2 = digitalRead(BUTTON2_PIN);
  byte readButton3 = digitalRead(BUTTON3_PIN);
  byte readButton4 = digitalRead(BUTTON4_PIN);

  static unsigned long lastTimePressedButton0 = 0; //last time interupt happened
  static unsigned long lastTimePressedButton1 = 0;
  static unsigned long lastTimePressedButton2 = 0;
  static unsigned long lastTimePressedButton3 = 0;
  static unsigned long lastTimePressedButton4 = 0;
  unsigned long debounceTimeButton0 = millis();
  unsigned long debounceTimeButton1 = millis();
  unsigned long debounceTimeButton2 = millis();
  unsigned long debounceTimeButton3 = millis();
  unsigned long debounceTimeButton4 = millis();
  int debounceDelay = 155; // delay of 155 ms

  //button debounce works, but ignores rapid button presses

  //button 0
  if(debounceTimeButton0 - lastTimePressedButton0 > debounceDelay){ //ignores input if it comes within debounceDelay from last imput
    if(readButton0 == LOW){
      Serial.print("Pressed button ");  //button debug
      Serial.println(BUTTON0_PIN - 2);  //button debug
      buttonNumber = 0;
    }
  }
  lastTimePressedButton0 = debounceTimeButton0;

  //button 1
  if(debounceTimeButton1 - lastTimePressedButton1 > debounceDelay){ //ignores input if it comes within debounceDelay from last imput
    if(readButton1 == LOW){
      Serial.print("Pressed button ");  //button debug
      Serial.println(BUTTON1_PIN - 2);  //button debug
      buttonNumber = 1;
    }
  }
  lastTimePressedButton1 = debounceTimeButton1;

  //button 2
  if(debounceTimeButton2 - lastTimePressedButton2 > debounceDelay){ //ignores input if it comes within debounceDelay from last imput
    if(readButton2 == LOW){
      Serial.print("Pressed button ");  //button debug
      Serial.println(BUTTON2_PIN - 2);  //button debug
      buttonNumber = 2;
    }
  }
  lastTimePressedButton2 = debounceTimeButton2;

  //button 3
  if(debounceTimeButton3 - lastTimePressedButton3 > debounceDelay){ //ignores input if it comes within debounceDelay from last imput
    if(readButton3 == LOW){
      Serial.print("Pressed button ");  //button debug
      Serial.println(BUTTON3_PIN - 2);  //button debug
      buttonNumber = 3;
    }
  }
  lastTimePressedButton3 = debounceTimeButton3;

  //button 4
  if(debounceTimeButton4 - lastTimePressedButton4 > debounceDelay){ //ignores input if it comes within debounceDelay from last imput
    if(readButton4 == LOW){
      Serial.print("Pressed button ");  //button debug
      Serial.println(BUTTON4_PIN - 2);  //button debug
      buttonNumber = 4;
    }
  }
  lastTimePressedButton4 = debounceTimeButton4;
}