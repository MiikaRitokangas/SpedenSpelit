#ifndef BUZZER_H
#define BUZZER_H


#define BUZZER_PIN 7 // The Arduino pin connected to the buzzer

#define TURQOISE_NOTE 330
#define YELLOW_NOTE 277
#define RED_NOTE 440
#define GREEN_NOTE 165

extern int gameButtonNotes[4];

enum GameTunes {
  STARTUP_TUNE,
  GAMESTART_TUNE,
  GAMEOVER_TUNE,
  HIGHSCORE_TUNE,
  SPEEDUP_TUNE,
};

void initializeBuzzer(void);

void playSound(int note, int duration);

void playTune(int id);

#endif