#if !defined(LCDDRIVER_H)
#define LCDDRIVER_H

#include "../Libraries/LCD/LCD.h"
#include "../Libraries/LSM303/LSM303.h"

#define ROW_LENGTH 16

// This class requires that it is passed acceleration data in the form of an
// Acceleration struct via stdin. The Acceleration struct is declared within the
// LSM303.h file. The current driver implementation is heavily tied to the
// layout of a 2x16 LCD display, and will output data in the following form:
//
//  ==================
//  |Acceleration (G)|
//  | < #.## #.## ^  |
//  ==================
// 
//  where the first number is the x-acceleration (with a left or right pointing
//  arrow to specify the direction), and the second number is the y-acceleration
//  (with an up or down arrow specifying the direction).
class LCDdriver {
   public:

      // Constructs an LCDdriver object with reference to the LCD display. Note
      // that the Acceleration struct used internally by this object is
      // dynamically allocated and so it is the callers responsibility to free
      // this memory once they are done using the object.  
      LCDdriver(LCD *display);

      // Must be called once the caller is done with the object, otherwise there
      // will be a memory leak. This function also deletes the LCD object it is
      // tied to as well.
      ~LCDdriver();

      // Prints the acceleration splash screen to the LCD module (aka the top
      // line of the display):
      //
      //  ==================
      //  |Acceleration (G)|
      //  |                |
      //  ==================
      void printCurrAccelSplash();

      // Prints the current acceleration value to the LCD splash screen (aka
      // overwrites the second line of the display) with the current data
      // values and their associated arrow directions.
      void printCurrAccel();

      // Reads the current acceleration values from the stdin pipe. Returns the
      // number of bytes read (this should equal the size of an Acceleration
      // struct).
      int readAccel();

      // Sets the values of the Acceleration struct to those specified by x & y.
      void setAccel(unsigned short x, unsigned short y);

   private:
      Acceleration *accel;
      LCD *lcd;
      char row[ROW_LENGTH];
      const char *horizontalArrow;
      const char *verticalArrow;
};

#endif
