#include "display.h"


void initializeDisplay(void) {
  // Sets pinModes, clears shift register and enables output

  // Set pinModes
  pinMode(DISP_RESETn, OUTPUT);   // n_reset
  pinMode(DISP_SHIFT, OUTPUT);    // shiftclock
  pinMode(DISP_LATCH, OUTPUT);    // latchClock
  pinMode(DISP_ENABLEn, OUTPUT);  // n_outEnable
  pinMode(DISP_DATAIN, OUTPUT);   // serialInput

  delay(1); // minimal delay for pinModes to propagate

  // Set pins to default states
  digitalWrite(DISP_RESETn,   1); // reset inactive
  digitalWrite(DISP_SHIFT,    0);
  digitalWrite(DISP_LATCH,    0);
  digitalWrite(DISP_ENABLEn,  0); // output enabled
  digitalWrite(DISP_DATAIN,   0);

  // Toggle reset, so shift register resets
  digitalWrite(DISP_RESETn, 0);
  digitalWrite(DISP_RESETn, 1);
  // Load resetted shift register values to latches
  digitalWrite(DISP_LATCH,  1);
  digitalWrite(DISP_LATCH,  0);
}


void writeByte(uint8_t bits, bool last) {
  /*
    WriteByte subroutine writes number 0-9 to 7-segment display.
    Last parameter controls when number is actually shown.
  */

  uint8_t dispBits = 0;
  // Case structure sets correct bits into 8-bit variable
  switch(bits) {
    case 0:
      dispBits = 0b00111111;
      break;
    case 1:
      dispBits = 0b00000110;
      break;
    case 2:
      dispBits = 0b01011011;
      break;
    case 3:
      dispBits = 0b01001111;
      break;
    case 4:
      dispBits = 0b01100110;
      break;
    case 5:
      dispBits = 0b01101101;
      break;
    case 6:
      dispBits = 0b01111101;
      break;
    case 7:
      dispBits = 0b00000111;
      break;
    case 8:
      dispBits = 0b01111111;
      break;
    case 9:
      dispBits = 0b01101111;
      break;
    default:  // show line as an error, if case is not matched
      dispBits = 0b01000000;
      break;
  }

  // Shifting bits to register in for-loop
  for(int i=0; i<8; i++) {
    digitalWrite(DISP_DATAIN, ((dispBits >> 7-i) & 0b00000001));
    digitalWrite(DISP_SHIFT, 1);
    digitalWrite(DISP_SHIFT, 0);
  }

  // If last is true, copy shift register to latches
  if(last == true) {
    digitalWrite(DISP_LATCH, 1);
    digitalWrite(DISP_LATCH, 0);
  }
}


void writeHighAndLowNumber(uint8_t tens, uint8_t ones) {
  /*
    writeHighAndLowNumber writes number from range 0-99 to
    two cascaded 7-segment displays.
  */
  writeByte(tens, false);
  writeByte(ones, true);
}

void showResult(byte number) {
  /*
    showResuts(byte result) This function separates digits from result number
    and calls writeByte subroutine to write the digit to 7-segment display.
    New implementation of this function makes writeHighAndLowNumber subroutine
    redundant, but it is required in project documents.
  */

  // Add support for any number of digits
  for(uint8_t i=NUMBER_OF_DISPLAYS; i>0; i--) {
    uint8_t digit = number;
    for(uint8_t j=0; j<i; j++) {
      digit = digit / 10;
    }

    digit = digit % 10;
    
    if(i==1) {
      writeByte(digit, true);
    } else {
      writeByte(digit, false);
    }
  }

  // old implementation, works only for 2 digits
  //writeHighAndLowNumber(number / 10, number % 10);
}
