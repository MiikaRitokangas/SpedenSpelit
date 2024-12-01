#include "SpedenSpelit.h"

// used for communicating between loop() and interrupts
extern volatile int buttonNumber = -1;    // for buttons interrupt handler
volatile bool newtimerInterrupt = false;  // for game.timer interrupt handler

extern gameStruct game = { MAINMENU, -1, 0, {}, 0, readHighscore(MODE1), readHighscore(MODE2), 0, false, 1.0 };  // TODO implement high score fetching (EEPROM.read(0) << 8) + EEPROM.read(1)

int buttonNotes[4] = { TURQOISE_NOTE, YELLOW_NOTE, RED_NOTE, GREEN_NOTE };

void setup() {
  // Initializing all modules here
  Serial.begin(9600);
  initButtonsAndButtonInterrupts();
  initializeDisplay();
  initializeLeds();
  initializeBuzzer();
  interrupts();
}

void loop() {
  // check what state the game is in and call the correct function to handle the game.state.
  switch (game.state) {
    case MAINMENU:
      handleMenu();
      break;
    case GAME:
      switch (game.mode) {
        case MODE1:
          game1Logic();
          break;
        case MODE2:
          game2Logic();
          break;
      }
      break;
    case STARTGAME:
      startGame();
      break;
    case STOPGAME:
      stopGame();
      break;
  }
}

int calculateFrequency(void) {
  return int(1000000 * game.frequency);
}

void Timer1_ISR(void) {
  newtimerInterrupt = true;
}

void initializetimer(void) {
  // see requirements for the function from SpedenSpelit.h
  Timer1.initialize(calculateFrequency());
  Timer1.attachInterrupt(Timer1_ISR);
}

// ISR(timer1_COMPA_vect) {
//   // if (game.mode == MODE2) {
//   //   if (game.waitForUserInput) {
//   //     // in the second game you have 30 seconds to answer if the game is waiting for user input
//   //     if (game.timer >= 30) {
//   //       game.state = -1;
//   //       stopGame();
//   //     }
//   //     game.timer++;
//   //   }
//   // }
// }


void checkGame(int userInput) {
  // check if the last played button was correct
  if (game.score < 100) {
    if (game.values[game.score] == userInput) {
      playSound(buttonNotes[userInput], 4);
      flashLed(userInput);
      game.score++;
      writeHighAndLowNumber(game.score / 10 % 10, game.score % 10);
    } else {
      game.state = STOPGAME;
    }
  } else {
    game.state = STOPGAME;
  }
}

void handleMenu() {
  setAllLeds();
  switch (buttonNumber) {
    case 0:
      game.mode = MODE1;
      playSound(buttonNotes[buttonNumber], 4);
      flashLedMenu(buttonNumber);
      writeHighAndLowNumber(game.highScore1 / 10 % 10, game.highScore1 % 10);
      buttonNumber = -1;
      break;
    case 1:
      game.mode = MODE2;
      playSound(buttonNotes[buttonNumber], 4);
      flashLedMenu(buttonNumber);
      writeHighAndLowNumber(game.highScore2 / 10 % 10, game.highScore2 % 10);
      buttonNumber = -1;
      break;
    case 3:
      buttonNumber = -1;
      if (game.mode != -1) {
        clearHighscore(game.mode);
      }
      break;
    case 4:
      buttonNumber = -1;
      if (game.mode != -1) {
        game.state = STARTGAME;
      }
      break;
  }
}


void initializeGame() {
  int previousNum = -1;
  int currentNum;
  for (int i = 0; i < 100; i++) {
    do {
      currentNum = int(random(0, 4));
    } while (currentNum == previousNum);
    game.values[i] = currentNum;
    Serial.println(currentNum);
    previousNum = currentNum;
  }
  game.state = GAME;
}

void startGame() {
  clearAllLeds();
  initializeGame();
  delay(400);
  initializetimer();
}

void game1Logic() {
  // if (0 <= buttonNumber && buttonNumber < 4) {
  //   Serial.println(buttonNumber);
  //   checkGame(buttonNumber);
  //   buttonNumber = -1;
  // }
  if (newtimerInterrupt) {
    newtimerInterrupt = false;
    playSound(game.values[game.index], 4);
    flashLed(game.values[game.index]);
    game.index++;
    if (game.timer > 9) {
      game.timer = 0;
      game.frequency -= .1;
      Timer1.setPeriod(calculateFrequency());
    } else {
      game.timer++;
    }
    if (game.index > game.score + 5) {
      stopGame();
    }
  }
}

void game2Logic() {
  if (game.waitForUserInput) {
    if (buttonNumber >= 0) {
      if (0 <= buttonNumber < 4) {
        checkGame(buttonNumber);
        buttonNumber = -1;
      }
    }
  }
}

void stopGame() {
  // game ended, handle saving high game.score and ending the game
  if (game.score > game.highScore1 || game.score == 99) {
    game.highScore1 = game.score;
    writeHighscore(game.highScore1, MODE1);
    playTune(HIGHSCORE_TUNE);
  } else {
    playTune(GAMEOVER_TUNE);
  }
  game.score = 0;
  game.index = 0;
  game.mode = -1;
  Timer1.stop();
  game.state = MAINMENU;
}
