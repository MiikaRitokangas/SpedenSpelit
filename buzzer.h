#ifndef BUZZER_H
#define BUZZER_H

#define TURQOISE_NOTE = 330
#define YELLOW_NOTE = 277
#define RED_NOTE = 440
#define GREEN_NOTE = 165

void playSound(int note, int duration);

void playTune(int id);

#endif