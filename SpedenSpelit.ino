#include "SpedenSpelit.h"

// used for communicating between loop() and interrupts
volatile int buttonNumber = -1;           // for buttons interrupt handler
volatile bool newtimerInterrupt = false;  // for game.timer interrupt handler

extern gameStruct game = { MAINMENU, -1, 0, {}, 0, readHighscore(MODE1), readHighscore(MODE2), 0, false, 1.0, false };  // TODO implement high score fetching (EEPROM.read(0) << 8) + EEPROM.read(1)

int buttonNotes[4] = { TURQOISE_NOTE, YELLOW_NOTE, RED_NOTE, GREEN_NOTE };

void setup() {
  // Initializing all modules here
  Serial.begin(9600);
  initButtonsAndButtonInterrupts();
  initializeDisplay();
  initializeLeds();
  initializeBuzzer();
  initializetimer();
  interrupts();
}

void loop() {
  // check what state the game is in and call the correct function to handle the state.
  if (game.state == GAME && buttonNumber != -1 && buttonNumber != 4) {
    checkGame(buttonNumber);
    buttonNumber = -1;
  }
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

long calculateFrequency(void) {
  return 1000000 * game.frequency;
}

void Timer1_ISR(void) {
  newtimerInterrupt = true;
}

void initializetimer(void) {
  // see requirements for the function from SpedenSpelit.h
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(Timer1_ISR);
}

void checkGame(int userInput) {
  // check if the last played button was correct
  if (game.score < 100) {
    switch (game.mode) {
      case MODE1:
        if (game.values[game.score] == userInput) {
          setLed(userInput);
          playSound(buttonNotes[userInput], 4);
          delay(250);
          clearAllLeds();
          game.score++;
          writeHighAndLowNumber(game.score / 10 % 10, game.score % 10);
        } else {
          game.state = STOPGAME;
        }
        break;
      case MODE2:
        if (game.waitForUserInput) {
          if (game.index <= game.score) {
            if (game.values[game.index] == userInput) {
              setLed(userInput);
              playSound(buttonNotes[userInput], 4);
              delay(250);
              clearAllLeds();
              game.index++;
            } else {
              game.state = STOPGAME;
            }
            if (game.score < game.index) {
              game.index = 0;
              game.score++;
              writeHighAndLowNumber(game.score / 10 % 10, game.score % 10);
              delay(1000);
              game.waitForUserInput = false;
            }
          }
        }
        break;
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
    case 2:
      playSound(buttonNotes[buttonNumber], 4);
      flashLedMenu(buttonNumber);
      game.cheat = !game.cheat;
      buttonNumber = -1;
      break;
    case 3:
      if (game.mode != -1) {
        clearHighscore(game.mode);
        playSound(buttonNotes[buttonNumber], 4);
        flashLedMenu(buttonNumber);
        switch (game.mode) {
          case MODE1:
            game.highScore1 = readHighscore(game.mode);
            break;
          case MODE2:
            game.highScore2 = readHighscore(game.mode);
            break;
        }
      }
      buttonNumber = -1;
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
  game.score = 0;
  game.index = 0;
  game.frequency = 1.0;
  game.timer = 0;
  randomSeed(analogRead(A0));
  for (int i = 0; i < 100; i++) {
    do {
      currentNum = int(random(0, 4));
    } while (currentNum == previousNum);
    game.values[i] = currentNum;
    Serial.println(currentNum);
    previousNum = currentNum;
  }
  playTune(game.mode);
  game.state = GAME;
}

void startGame() {
  clearAllLeds();
  initializeGame();
  delay(1000);
  Timer1.start();
}

void game1Logic() {
  if (newtimerInterrupt) {
    if (game.index < 100) {
      if ((!game.cheat) || !(game.index % 20 >= 10 && game.index % 20 < 20)) {
        setLed(game.values[game.index]);
      }
      playSound(buttonNotes[game.values[game.index]], 4);
      delay(250);
      clearAllLeds();
      game.index++;
      if (game.timer > 9) {
        game.timer = 0;
        game.frequency -= 0.1;
        Timer1.setPeriod(calculateFrequency());
      } else {
        game.timer++;
      }
      // if (game.index > game.score + 5) {
      //   stopGame();
      // }
      newtimerInterrupt = false;
    }
  }
}

void game2Logic() {
  if (!game.waitForUserInput) {
    for (int i = 0; i <= game.score; i++) {
      delay(250 * game.frequency);
      playSound(buttonNotes[game.values[i]], 4);
      flashLed(game.values[i]);
    }
    game.waitForUserInput = true;
    if (game.score % 10 == 0 && game.score != 0) {
      game.frequency -= 0.1;
    }
  }
}

void stopGame() {
  // game ended, handle saving high game.score and ending the game
  if (game.mode == MODE1 && game.score > game.highScore1 || game.mode == MODE2 && game.score > game.highScore2 || game.score == 99) {
    switch (game.mode) {
      case MODE1:
        game.highScore1 = game.score;
        writeHighscore(game.highScore1, MODE1);
        break;
      case MODE2:
        game.highScore2 = game.score;
        writeHighscore(game.highScore2, MODE2);
        break;
    }
    playTune(HIGHSCORE_TUNE);
  } else {
    playTune(GAMEOVER_TUNE);
  }
  game.mode = -1;
  Timer1.stop();
  game.state = MAINMENU;
}
