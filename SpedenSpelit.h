#ifndef SPEDENSPELIT_H
#define SPEDENSPELIT_H
#include <arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "buzzer.h"
#include "eeprom.h"
#include <TimerOne.h>


extern volatile int buttonNumber;
struct gameStruct {
  volatile int state;              // enum gameStates
  volatile int mode;               // enum GameModes
  volatile int index;              // current game step
  volatile int values[250];        // game values
  volatile int score;              // user score
  volatile int highScore1;         // high score fetched from EEPROM
  volatile int highScore2;         // high score fetched from EEPROM
  volatile int timer;              // used as an ingame timer
  volatile bool waitForUserInput;  // bool whether the game is waiting for userinput or not
  float frequency;                 // gamespeed modifier
  volatile bool cheat;             // is cheatmode enabled
};
extern gameStruct game;

enum GameStates {
  MAINMENU,
  GAME,
  STARTGAME,
  STOPGAME
};

enum GameModes {
  MODE1,
  MODE2
};


/*
  initializeTimer() subroutine intializes Arduino Timer1 module to
  give interrupts at rate 1Hz
*/
void initializeTimer(void);
// Intoduce TIMER1_COMPA_vect Interrupt SeRvice (ISR) function for timer.
ISR(TIMER1_COMPA_vect);

/*
  initializeGame() subroutine is used to initialize all variables
  needed to store random numbers and player button push data.
  This function is called from startTheGame() function.
  
*/
void initializeGame(void);

/*
  checkGame() subroutine is used to check the status
  of the Game after each player button press.
  
  If the latest player button press is wrong, the game stops
  and if the latest press was right, game display is incremented
  by 1.
  
  Parameters
  byte lastButtonPress of the player 0 or 1 or 2 or 3
  
*/
void checkGame(int);


/*
  startTheGame() subroutine calls InitializeGame()
  function and enables Timer1 interrupts to start
  the Game.
*/
void startGame(void);

void stopGame(void);


#endif