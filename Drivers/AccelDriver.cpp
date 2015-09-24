#include <stdio.h>
#include <unistd.h>
#include "../Libraries/LSM303/LSM303.h"

// This program assums that it has a pipe to a LCDdisplay process via stdout.
// To call this process, the client must first establish this pipe, otherwise
// this process will do nothing.
int main(int argc, char **argv) {
   LSM303 accel(1);
   accel.init(INIT_MASK);
   Acceleration data = {0};

   // Loop until a kill signal is sent by parent process.
   while (true) {
      // Read the current accelerometer values.
      accel.readAcceleration(&data);

      // Sleep a set amount of time to not overly saturate the pipe.
      usleep(500000);

      // Write the accelerometer values to the outbound pipe.
      write(STDOUT_FILENO, &data, sizeof(Acceleration));
   }
   return 0;
}
