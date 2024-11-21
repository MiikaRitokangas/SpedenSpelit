// Author Miika Ritokangas
#include "pitches.h"
#include "buzzer.h"
#include "SpedenSpelit.h"

int startgame[] { NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4 };
int startgame_dur[] { 4, 8, 8, 4, 4, 4, 4, 4 };

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

void handleTune(int notes[], int noteDurs[]) {
  for (int thisNote = 0; thisNote < sizeof(notes)/sizeof(notes[0]); thisNote++) {
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
      handleTune(startgame, startgame_dur);
  }
}