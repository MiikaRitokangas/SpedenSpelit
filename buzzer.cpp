// Author Miika Ritokangas

#include "buzzer.h"
#include "pins.h"
#include "pitches.h"

int startgame[] { NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4 };
int startgame_dur[] { 4, 8, 8, 4, 4, 4, 4, 4 };


void initializeBuzzer() {
  pinMode(BUZZER_PIN, OUTPUT);
  playTune();
}

void playSound(int tune, int duration) {
  // to calculate the note duration, take one second divided by the note type.
  // e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
  int noteDuration = 1000 / duration;
  tone(BUZZER_PIN, tune, noteDuration);
  delay(noteDuration);

  noTone(BUZZER_PIN);
}

void playTune(int id) {
  switch (id) {
    case STARTUP_TUNE:
      handleTune(startgame, startgame_dur);
  }
    // // iterate over the notes of the melody:
    // for (int thisNote = 0; thisNote < 8; thisNote++) {

    //   // to calculate the note duration, take one second divided by the note type.
    //   //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    //   int noteDuration = 1000 / noteDurations[thisNote];
    //   tone(BUZZER_PIN, melody[thisNote], noteDuration);

    //   // to distinguish the notes, set a minimum time between them.
    //   // the note's duration + 30% seems to work well:
    //   int pauseBetweenNotes = noteDuration * 1.30;
    //   delay(pauseBetweenNotes);
    //   // stop the tone playing:
    //   noTone(BUZZER_PIN);
    // }
}

void handleTune(int notes[], int noteDurs[]) {
  for (int thisNote = 0; thisNote < sizeOf(notes)/sizeOf(int); thisNote++) {
    int noteDuration = 1000 / noteDurs[thisNote];
    tone(BUZZER_PIN, notes[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(BUZZER_PIN);
  }
}