#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"
#include "pins.h"
#include "buzzer.h"

// Use these 2 volatile variables for communicating between
// loop() function and interrupt handlers
extern volatile int buttonNumber = -1;    // for buttons interrupt handler
volatile bool newTimerInterrupt = false;  // for timer interrupt handler
volatile bool gameStarted = false;


void setup() {
  /*
    Initialize all modules here
  */
  initButtonsAndButtonInterrupts();
  initializeDisplay();
  initializeLeds();
  initializeBuzzer();
}

void loop() {
  if (buttonNumber >= 0) {
    // start the game if buttonNumber == 4
    // check the game if 0<=buttonNumber<4
    if (gameStarted) {
      if (0 <= buttonNumber < 4) {
        checkGame(buttonNumber);
        buttonNumber = -1;
      }
    } else {
      if (buttonNumber == 4) {
        startTheGame();
      }
    }
  }

  if (newTimerInterrupt == true) {
    // new random number must be generated
    // and corresponding let must be activated
    newTimerInterrupt = false;
  }
}

void initializeTimer(void) {
  // see requirements for the function from SpedenSpelit.h
}
ISR(TIMER1_COMPA_vect) {
  /*
  Communicate to loop() that it's time to make new random number.
  Increase timer interrupt rate after 10 interrupts.
  */
  newTimerInterrupt = true;
}


void checkGame(byte nbrOfButtonPush) {
  // check if the last played button was correct
  switch (nbrOfButtonPush) {
    case 0:
      playSound(TURQOISE_NOTE, 4);
      break;
    case 1:
      playSound(YELLOW_NOTE, 4);
      break;
    case 2:
      playSound(RED_NOTE, 4);
      break;
    case 3:
      playSound(GREEN_NOTE, 4);
      break;
    case default:
      assert(FALSE);
  }
}


void initializeGame() {
  // see requirements for the function from SpedenSpelit.h
}

void startGame() {
  // see requirements for the function from SpedenSpelit.h
  playTune(STARTGAME_TONE);
  initializeGame(void);
}

void stopGame() {
  // game ended, handle saving high score and ending the game
}
