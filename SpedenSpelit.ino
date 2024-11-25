#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"
#include "buzzer.h"

// used for communicating between loop() and interrupts
extern volatile int buttonNumber = -1;    // for buttons interrupt handler
volatile bool newTimerInterrupt = false;  // for timer interrupt handler

// state switching
volatile int gameState = MAINMENU;  // 0 menu, 1 game, 2 game, 3 started, 4 gameover
volatile int selectedGame = -1;

// scores
int score = 0;
int highScore = 0;

// game 1 logic
volatile int game1Values[99];
volatile int newNumber;

//game 2 logic
volatile int game2Values[99];
volatile int timer;
volatile int stepCount;
bool waitingForInput = false;

int buttonNotes[4] = { TURQOISE_NOTE, YELLOW_NOTE, RED_NOTE, GREEN_NOTE };

void setup() {
  // Initializing all modules here
  initButtonsAndButtonInterrupts();
  initializeDisplay();
  initializeLeds();
  initializeBuzzer();
}

void loop() {
  // check what state the game is in and call the correct function to handle the gamestate.
  switch (gameState) {
    case MAINMENU:
      handleMenu();
      break;
    case GAME:
      switch (selectedGame) {
        case GAMEMODE1:
          game1Logic();
          break;
        case GAMEMODE2:
          game2Logic();
          break;
      }
      break;
    case GAMESTART:
      startGame();
      break;
    case GAMEOVER:
      stopGame();
      break;
  }
}

void initializeTimer(void) {
  // see requirements for the function from SpedenSpelit.h
  TCCR1A = 0;           // Init Timer1
  TCCR1B = 0;           // Init Timer1
  TCCR1B |= B00000011;  // Prescalar = 64
  OCR1A = 62500;        // Timer Compare1A Register
  TIMSK1 |= B00000010;  // Enable Timer COMPA Interrupt
}

ISR(TIMER1_COMPA_vect) {
  if (gameState == GAME) {
    if (newNumber > 9) {
      OCR1A += 46875; // Advance The COMPA Register
    } else {
      OCR1A += 62500;  // Advance The COMPA Register
    }
    if (selectedGame == GAMEMODE1) {
      newTimerInterrupt = true;
    }
    if (selectedGame == GAMEMODE2) {
      OCR1A += 62500;  // Advance The COMPA Register
      if (waitingForInput) {
        // in the second game you have 30 seconds to answer if the game is waiting for user input
        if (timer >= 30) {
          gameState = GAMEOVER;
        }
        timer++;
      }
    }
  }
}


void checkGame(byte userInput) {
  // check if the last played button was correct
  if (game1Values[score] == userInput) {
    playSound(buttonNotes[userInput], 4);
    flashLed(userInput);
    score++;
  } else {
    gameState = GAMEOVER;
  }
  if (selectedGame == 1) {
  }
}


void handleMenu() {
  setAllLeds();
  switch (buttonNumber) {
    case -1:
      break;
    case 0:
      selectedGame = GAMEMODE1;
      playSound(buttonNotes[buttonNumber], 4);
      flashLedMenu(buttonNumber);
      break;
    case 1:
      selectedGame = GAMEMODE2;
      playSound(buttonNotes[buttonNumber], 4);
      flashLedMenu(buttonNumber);
      break;
    case 4:
      gameState = GAMESTART;
      break;
  }
}

void initializeGame() {
  switch (selectedGame) {
    case GAMEMODE1:
      for (int i = 0; i <= 100; i++) {
        game1Values[i] = random(0, 3);
      }
      playTune(GAMESTART_TUNE);
      break;
    case GAMEMODE2:
      //game2Values = {};
      break;
  }
  gameState = GAME;
}

void startGame() {
  clearAllLeds();
  initializeGame();
}

void game1Logic() {
  if (buttonNumber >= 0) {
    if (0 <= buttonNumber < 4) {
      checkGame(buttonNumber);
      buttonNumber = -1;
    }
  }
  if (newTimerInterrupt) {
    flashLed(game1Values[newNumber]);
    playSound(game1Values[newNumber], 4);
    newNumber++;
    if (newNumber > score + 5) {
      gameState = GAMEOVER;
    }
    newTimerInterrupt = false;
  }
}

void game2Logic() {
  if (waitingForInput) {
    if (buttonNumber >= 0) {
      if (0 <= buttonNumber < 4) {
        checkGame(buttonNumber);
        buttonNumber = -1;
      }
    }
  }
}

void stopGame() {
  // game ended, handle saving high score and ending the game
  if (score > highScore) {
    highScore = score;
    score = 0;
    playTune(HIGHSCORE_TUNE);
  } else {
    score = 0;
    playTune(GAMEOVER_TUNE);
  }
  gameState = MAINMENU;
  selectedGame = -1;
}
