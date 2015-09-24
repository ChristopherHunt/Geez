#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "LCDdriver.h"

// Constructs an LCDdriver object with reference to the LCD display.
LCDdriver::LCDdriver(LCD *display) {
   lcd = display; 
   accel = (Acceleration *)calloc(1, sizeof(Acceleration));
   horizontalArrow = NULL;
   verticalArrow = NULL;
}

// Frees all of the memory associated with the driver, including the LCD object
// it will created with.
LCDdriver::~LCDdriver() {
   delete(lcd);
   free(accel);
}

// Prints the splash header words to the top line of the LCD display.
void LCDdriver::printCurrAccelSplash() {
   lcd->returnHome(0);
   lcd->print("Acceleration (G)");
}

// Prints the acceleration data in x and y (and their associated direction
// arrows) to the second line of the LCD display.
void LCDdriver::printCurrAccel() {
   lcd->returnHome(1);

   if (accel->xVal >= 0) {
      horizontalArrow = "<"; 
   } else {
      horizontalArrow = ">";
      accel->xVal = -accel->xVal;
   }

   if (accel->yVal >= 0) {
      verticalArrow = "v"; 
   } else {
      verticalArrow = "^";
      accel->yVal = -accel->yVal;
   }

   snprintf(row, sizeof(row), " %s %1.2f  %1.2f %s ", horizontalArrow,
         (double)accel->xVal/8192, (double)accel->yVal/8192, verticalArrow);

   lcd->print(row);
}

// Reads in acceleration data from the stdin pipe. This data must be packaged as
// an Acceleration struct from the LSM303 driver or this read will fail.
int LCDdriver::readAccel() {
   return read(STDIN_FILENO, accel, sizeof(Acceleration));
}

// Sets the values of the object's Acceleration struct to those specified by x
// and y.
void LCDdriver::setAccel(unsigned short x, unsigned short y) {
   accel->xVal = x;
   accel->yVal = y;
}

// Main driver. Note that this driver is configured to be used with the
// BeagleBoneBlack's pin layout and the specific pins specified below. These
// values will need to be changed for other boards / configurations.
int main(int argc, char **argv) {
   unsigned char lcdDataPins[] = {22, 27, 47, 23};
   LCDpins pins = {66, 69, 45, lcdDataPins}; 

   LCDdriver *driver = new LCDdriver(new LCD(&pins, 4, 1));
   driver->printCurrAccelSplash();

   // Loop until there is no more data to display.
   while (driver->readAccel()) {
      driver->printCurrAccel();
   }
   return 0;
}
