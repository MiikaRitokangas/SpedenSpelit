#ifndef EEPROM_H
#define EEPROM_H
#include "SpedenSpelit.h"
#include <EEPROM.h>

int readHighscore(int); // reads highscore, input is which gamemode
void writeHighscore(int, int); // writes highscore for current gamemode
void clearHighscore(int); // clear selected gamemodes highscore

#endif