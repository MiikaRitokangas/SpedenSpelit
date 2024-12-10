#include "eeprom.h"

int readHighscore(int mode) {
  int highscore;
  switch (mode) {
    case MODE1:
      highscore = (EEPROM.read(0) << 8) + EEPROM.read(1);
      break;
    case MODE2:
      highscore = (EEPROM.read(2) << 8) + EEPROM.read(3);
      break;
  }
  if (highscore == 0xffff) {
    return 0;
  }
  return highscore;
}

void writeHighscore(int value, int mode) {
  switch (mode) {
    case MODE1:
      EEPROM.write(0, value >> 8);
      EEPROM.write(1, value & 0xff);
      break;
    case MODE2:
      EEPROM.write(2, value >> 8);
      EEPROM.write(3, value & 0xff);
      break;
  }
}

void clearHighscore(int mode) {
  writeHighscore(0, mode);
}
