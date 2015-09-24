#include <iostream>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "Libraries/GPIO/GPIO.h"
#include "Libraries/LCD/LCD.h"
#include "Libraries/LSM303/LSM303.h"

using namespace std;

int main(int argc, char **argv) {
   int fds[2] = {0};
   int pids[2] = {0};
   pipe(fds);

   // Create LCD process
   if (!(pids[0] = fork())) {
      dup2(fds[0], STDIN_FILENO);
      close(fds[0]);
      close(fds[1]);
      execlp("./LCDdriver", "LCDdriver");
   }

   // Close dangling read file descriptor
   close(fds[0]);

   // Create Accelerometer process
   if (!(pids[1] = fork())) {
      dup2(fds[1], STDOUT_FILENO);
      close(fds[1]);
      execlp("./AccelDriver", "AccelDriver");
   }

   // Close dangling write file descriptor
   close(fds[1]);

   // Loop and check for off button press
   GPIO *offButton = new GPIO(49);
   offButton->setDirection("in");
   while (offButton->getValue() == 0) {
   }
   delete(offButton);

   // When off button is pressed, kill child processes and exit
   printf("Killing process.\n");
   kill(pids[0], SIGTERM);
   kill(pids[1], SIGTERM);

   return 0;
}
