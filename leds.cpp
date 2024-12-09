#include <Arduino.h>
#include "leds.h"

byte gameStartLeds[] { 0, 1, 1, 2, 1, 50, 3, 0 }; // LEDs for start game sound 50 = break
byte gameStartAltLeds[] { 1, 0, 2, 4, 3, 7}; // LEDs for start game alternative sound
byte gameOverLeds[] {14, 14, 14}; //  LEDs for game over sound
byte highScoreLeds[] {12, 10, 7, 5, 6, 5, 4, 3, 1, 2, 0, 50}; //  LEDs for high score sound

//Intializes analog pins A2,A3,A4,A5 to be used as outputs.
void initializeLeds()
{
  // see requirements for this function from leds.h
  pinMode(LED_0, OUTPUT); // Pin A2
  pinMode(LED_1, OUTPUT); // Pin A3
  pinMode(LED_2, OUTPUT); // Pin A4
  pinMode(LED_3, OUTPUT); // Pin A5
}

// need a solution for blinking leds without using delay, for example, setting a flag for a led to be blinked once and handling it in the main loop() with millis
// Flash a single LED
void flashLed(int ledNumber) {
  setLed(ledNumber); // LED on
  delay(ledDuration);
  setLed(ledNumber);  // LED off
}

// Flash a single LED for menu operations
void flashLedMenu(int ledNumber) {
  setLed(ledNumber);   // LED on
  delay(ledOffDuration);
  setLed(ledNumber);   // LED off
}

// Toggle multiple LEDs on and off with delay
void toggleLeds(byte leds[], int count, int delayTime) {
  for (int i = 0; i < count; i++) {
    setLed(leds[i]);
  }
  delay(delayTime);
  for (int i = 0; i < count; i++) {
    setLed(leds[i]);
  }
}

// Handle specific LED patterns based on the note
void handleLeds(byte note, int ledDelay) {
  switch (note) {
    case 4: { // Binary 0011: Turn on LEDs 0 and 1
        byte leds[] = {0, 1};
        toggleLeds(leds, 2, ledDelay);
        break;
      }
    case 5: { // Binary 0101: Turn on LEDs 0 and 2
        byte leds[] = {0, 2};
        toggleLeds(leds, 2, ledDelay);
        break;
      }
    case 6: { // Binary 0110: Turn on LEDs 1 and 2
        byte leds[] = {1, 2};
        toggleLeds(leds, 2, ledDelay);
        break;
      }
    case 7: { // Binary 0111: Turn on LEDs 0, 1, 2
        byte leds[] = {0, 1, 2};
        toggleLeds(leds, 3, ledDelay);
        break;
      }
    case 8: { // Binary 1001: Turn on LEDs 0 and 3
        byte leds[] = {0, 3};
        toggleLeds(leds, 2, ledDelay);
        break;
      }
    case 9: { // Binary 1010: Turn on LEDs 1 and 3
        byte leds[] = {1, 3};
        toggleLeds(leds, 2, ledDelay);
        break;
      }
    case 10: { // Binary 1011: Turn on LEDs 0, 1, 3
        byte leds[] = {0, 1, 3};
        toggleLeds(leds, 3, ledDelay);
        break;
      }
    case 11: { // Binary 1100: Turn on LEDs 2 and 3
        byte leds[] = {2, 3};
        toggleLeds(leds, 2, ledDelay);
        break;
      }
    case 12: { // Binary 1101: Turn on LEDs 0, 2, 3
        byte leds[] = {0, 2, 3};
        toggleLeds(leds, 3, ledDelay);
        break;
      }
    case 13: { // Binary 1110: Turn on LEDs 1, 2, 3
        byte leds[] = {1, 2, 3};
        toggleLeds(leds, 3, ledDelay);
        break;
      }
    case 14: { // Binary 1111: Turn on all LEDs
        byte leds[] = {0, 1, 2, 3};
        toggleLeds(leds, 4, ledDelay);
        break;
      }
    default:
      setLed(note);   // Turn on a single LED
      delay(ledDelay);// Delay
      setLed(note);   // Turn off
      break;
  }
}

// Set specific LED on/off.
// If the LED is off it will go on or if it's already on it will go off
void setLed(byte ledNumber)
{
  // see requirements for this function from leds.h
  //  LED 0
  if (ledNumber == 0) {
    int ledVal = digitalRead(LED_0);  //Read LED current value
    if (ledVal == HIGH) {
      digitalWrite(LED_0, LOW); // Set LED off
    }
    else {
      digitalWrite(LED_0, HIGH); // Set LED on
    }
  }
  //  LED 1
  if (ledNumber == 1) {
    int ledVal = digitalRead(LED_1);  //Read LED current value
    if (ledVal == HIGH) {
      digitalWrite(LED_1, LOW); // Set LED off
    }
    else {
      digitalWrite(LED_1, HIGH); // Set LED on
    }
  }
  //  LED 2
  if (ledNumber == 2) {
    int ledVal = digitalRead(LED_2);  //Read LED current value
    if (ledVal == HIGH) {
      digitalWrite(LED_2, LOW); // Set LED off
    }
    else {
      digitalWrite(LED_2, HIGH); // Set LED on
    }
  }
  //  LED 3
  if (ledNumber == 3) {
    int ledVal = digitalRead(LED_3);  //Read LED current value
    if (ledVal == HIGH) {
      digitalWrite(LED_3, LOW); // Set LED off
    }
    else {
      digitalWrite(LED_3, HIGH); // Set LED on
    }
  }
}

// Set all LEDs off
void clearAllLeds()
{
  // see requirements for this function from leds.h
  digitalWrite(LED_0, LOW); // Set LED 0 off
  digitalWrite(LED_1, LOW); // Set LED 1 off
  digitalWrite(LED_2, LOW); // Set LED 2 off
  digitalWrite(LED_3, LOW); // Set LED 3 off
}

// Set all LEDs on
void setAllLeds()
{
  // see requirements for this function from leds.h
  digitalWrite(LED_0, HIGH); // Set LED 0 on
  digitalWrite(LED_1, HIGH); // Set LED 1 on
  digitalWrite(LED_2, HIGH); // Set LED 2 on
  digitalWrite(LED_3, HIGH); // Set LED 3 on
}

// Shows numbers 0,1,...,15 as binary numbers
void show1()
{
  // see requirements for this function from leds.h
  // Loop for numbers 0-15
  for (int i = 0; i < 16; i++) {
    int number = i;
    byte numInBinary = 0;
    //  Loop for get binary from number
    for (byte b = 0; b < 4; b++) {
      numInBinary = bitRead(number, b); //  Read number as binary
      //  If the binary value is 1 set a specific LED on
      //  or if the binary value is 0 set specific LED off
      if (numInBinary == 1) {
        // Check what LED we need to set on
        switch (b) {
          case 0:
            digitalWrite(LED_0, HIGH);
            break;
          case 1:
            digitalWrite(LED_1, HIGH);
            break;
          case 2:
            digitalWrite(LED_2, HIGH);
            break;
          case 3:
            digitalWrite(LED_3, HIGH);
            break;
          default:
            break;
        }
      }
      else {
        // Check what LED we need to set off
        switch (b) {
          case 0:
            digitalWrite(LED_0, LOW);
            break;
          case 1:
            digitalWrite(LED_1, LOW);
            break;
          case 2:
            digitalWrite(LED_2, LOW);
            break;
          case 3:
            digitalWrite(LED_3, LOW);
            break;
          default:
            break;
        }
      }
    }
    // Delay between numbers
    delay(1250);
  }
  clearAllLeds();
}

//shows leds 0,1,2,3,0,1,2,3,.... with increasing changing rate.
//int rounds: This parameter determines how many times 0,1,2,3 sequence is shown.
void show2(int rounds)
{
  // see requirements for this function from leds.h
  int firstDelay = (100 * rounds);  // Delay for first round
  int delayDecreaser = 0;
  int delayOverflow = 0;
  // Check if rounds is over 10
  if (rounds > 10) {
    delayOverflow = rounds - 10;
  }
  // Loop for how many times to show 0,1,2,3 sequence
  for (int i = 0; i < rounds; i++) {
    // Increasing delayDecreaser by round
    delayDecreaser = (i * (10 * (rounds - delayOverflow)));
    // Decreasing delay
    int delaY = firstDelay - delayDecreaser;
    digitalWrite(LED_0, HIGH); // Set LED 0 on
    delay(delaY);              // Delay
    digitalWrite(LED_1, HIGH); // Set LED 1 on
    delay(delaY);              // Delay
    digitalWrite(LED_2, HIGH); // Set LED 2 on
    delay(delaY);              // Delay
    digitalWrite(LED_3, HIGH); // Set LED 3 on
    delay(delaY);              // Delay
    clearAllLeds();            // Set all LEDs off
    delay(delaY);              // Delay
  }
}
