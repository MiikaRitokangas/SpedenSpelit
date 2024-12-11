#ifndef LEDS_H
#define LEDS_H
#include <arduino.h>

//Analog pins defined
#define LED_0 A2
#define LED_1 A3
#define LED_2 A4
#define LED_3 A5

extern byte gameStartLeds[];  // LEDs for the "start game sound"
extern byte gameStartAltLeds[];  // LEDs for the "alternative start game sound"
extern byte gameOverLeds[];  // LEDs for the "game over sound"
extern byte highScoreLeds[];  // LEDs for the "high score sound"
extern byte speedUpLeds[];

/*
  initializeLeds() subroutine intializes analog pins A2,A3,A4,A5
  to be used as outputs. Speden Spelit leds are connected to those
  pins.
*/
void initializeLeds();

// Function to flash a single LED 
void flashLed(int);
// Function to flash a single LED for menu operations
void flashLedMenu(int);

static int ledDuration = 500;
static int ledOffDuration = 200;

// Function to toggle multiple LEDs on and off
void toggleLeds(byte, int, int);
// Function to handle LED patterns based on the provided note value
void handleLeds(byte, int);

/*
  setLed(byte) sets correct led number given as 0,1,2 or 3
  led number 0 corresponds to led connected at Arduino pin A2
  led number 1 => Arduino pin A3
  led number 2 => Arduino pin A4
  led number 3 => Arduino pin A5

  parameters:
  byte ledNumber is 0,1,2 or 3
*/
void setLed(byte ledNumber);

/*
  clearAllLeds(void) subroutine clears all leds
*/
void clearAllLeds(void);

/*
  setAllLeds subroutine sets all leds
*/
void setAllLeds(void);

/*
  show1() subroutine shows numbers 0,1,...,15 as binary numbers
  waits a bit and repeats number "show"
*/
void show1(void);

/*
  show2(int) subroutine shows leds 0,1,2,3,0,1,2,3,.... with increasing
  changing rate. And when top change speed has been reached

    Parameters:

  int rounds: This parameter determines how many times 0,1,2,3 sequence
              is shown.
*/
void show2(int);

#endif
