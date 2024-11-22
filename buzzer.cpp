// Author Miika Ritokangas
#include "pitches.h"
#include "buzzer.h"
#include "SpedenSpelit.h"

//start game sound
int startGame[] { NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4 };
int startGame_dur[] { 4, 8, 8, 4, 4, 4, 4, 4 };
int startGame_notes = 8;
//start game alternative sound
int startGameAlt[] { NOTE_E3, NOTE_CS3, NOTE_A3, NOTE_E4, NOTE_CS4, NOTE_A4};
int startGameAlt_dur[] { 8, 8, 4, 8, 8, 4};
int startGameAlt_notes = 6;
//game over sounds
int gameOver[] {NOTE_D2, NOTE_CS2, NOTE_C1};
int gameOver_dur[] {4, 3, 1};
int gameOver_notes = 3;
//high score sounds
int highScore[] {NOTE_A3, NOTE_B3, NOTE_C4, NOTE_A4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_A5, NOTE_G5, NOTE_C6};
int highScore_dur[] {8, 7, 8, 7, 8, 8, 7, 8, 7, 8, 2};
int highScore_notes = 12;

void initializeBuzzer() {
  pinMode(BUZZER_PIN, OUTPUT);
  noTone(BUZZER_PIN);
}

void playSound(int tune, int duration) {
  // to calculate the note duration, take one second divided by the note type.
  // e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
  int noteDuration = 1000 / duration;
  tone(BUZZER_PIN, tune, noteDuration);
  delay(noteDuration);

  noTone(BUZZER_PIN);
}

void handleTune(int notes[], int noteDurs[], int noteAmount) {
  for (int thisNote = 0; thisNote < noteAmount; thisNote++) {
    int noteDuration = 1000 / noteDurs[thisNote];
    tone(BUZZER_PIN, notes[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(BUZZER_PIN);
  }
}

void playTune(int id) {
  switch (id) {
    case STARTUP_TUNE:
      handleTune(startGame, startGame_dur, startGame_notes);
      break;
    case GAMESTART_TUNE:
      handleTune(startGameAlt, startGameAlt_dur, startGameAlt_notes);
      break;
    case GAMEOVER_TUNE:
      handleTune(gameOver, gameOver_dur, gameOver_notes);
      break;
    case HIGHSCORE_TUNE:
      handleTune(highScore, highScore_dur, highScore_notes);
      break;
  }
}