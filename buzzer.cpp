// Author Miika Ritokangas

#include "buzzer.h"
#include "pins.h"
#include "pitches.h"

void playSound(int tune, int duration) {
  // to calculate the note duration, take one second divided by the note type.
  // e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
  int noteDuration = 1000 / duration;
  tone(BUZZER_PIN, tune, noteDuration);
  delay(noteDuration);

 // noTone(BUZZER_PIN);
}

// void playTune() {
//     // iterate over the notes of the melody:
//     for (int thisNote = 0; thisNote < 8; thisNote++) {

//       // to calculate the note duration, take one second divided by the note type.
//       //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
//       int noteDuration = 1000 / noteDurations[thisNote];
//       tone(BUZZER_PIN, melody[thisNote], noteDuration);

//       // to distinguish the notes, set a minimum time between them.
//       // the note's duration + 30% seems to work well:
//       int pauseBetweenNotes = noteDuration * 1.30;
//       delay(pauseBetweenNotes);
//       // stop the tone playing:
//       noTone(BUZZER_PIN);
//     }
// }