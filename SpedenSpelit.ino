#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"
#include "pins.h"
#include "buzzer.h"

// Use these 2 volatile variables for communicating between
// loop() function and interrupt handlers
extern volatile int buttonNumber = -1;           // for buttons interrupt handler
volatile bool newTimerInterrupt = false;  // for timer interrupt handler


void setup()
{
  /*
    Initialize here all modules
  */
  initButtonsAndButtonInterrupts();
  initializeDisplay();
  initializeLeds();
  initializeBuzzer();
}

void loop()
{
  if(buttonNumber>=0)
  {
     // start the game if buttonNumber == 4
     // check the game if 0<=buttonNumber<4
     switch (buttonNumber) {
      case BUTTON0_PIN:
        playSound(TURQOISE_NOTE, 4);
      case BUTTON1_PIN:
        playSound(YELLOW_NOTE, 4);
      case BUTTON2_PIN:
        playSound(RED_NOTE, 4);
      case BUTTON3_PIN:
        playSound(GREEN_NOTE, 4);
      case BUTTON4_PIN:
        playTune(STARTGAME_TONE);
        startTheGame();
     }
  }

  if(newTimerInterrupt == true)
  {
     // new random number must be generated
     // and corresponding let must be activated
  }
}

void initializeTimer(void)
{
	// see requirements for the function from SpedenSpelit.h
}
ISR(TIMER1_COMPA_vect)
{
  /*
  Communicate to loop() that it's time to make new random number.
  Increase timer interrupt rate after 10 interrupts.
  */
  
}


void checkGame(byte nbrOfButtonPush)
{
	// see requirements for the function from SpedenSpelit.h
}


void initializeGame()
{
	// see requirements for the function from SpedenSpelit.h
}

void startTheGame()
{
   // see requirements for the function from SpedenSpelit.h
}

