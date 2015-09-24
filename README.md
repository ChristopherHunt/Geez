#GMeter

##BeagleBone Black (BBB) GMeter Project

The purpose of this project is to create a cape for the BBB that measure
real-time Gforces and displays them via an onboard LCD module. This project 
uses a LSM303 accelerometer to measure Gforces and a small off the shelf 2x16 
LCD module to display the current X and Y values.

This project includes custom library files created to interact with both the 
LSM303 and the LCD module. The LSM303 board requires 4 wires (3.3V / 5V PWR, 
GRD, I2C DATA, I2C CLK) to properly operate. The BBB comes with 3 sets of i2c 
connections, so ensure that one of these sets is used to communicate with the 
LSM303.

Communication between the LCD module and the BBB is much simplier and just
requires a handful of GPIO pins. However, since the BBB's pins don't always
default to GPIO a Device Tree Overlay is included to remux several pins to act
as GPIO pins.

Finally, a driver program is included that ties all of the other library files
together and allows operation of the BBB Gmeter Cape.

## Pinout
Note that these pinouts are for the BeagleBoneBlack Rev3. Also, prior to running
 any source code it is imperative that the build.sh file is run from the  
CapeDeviceTree (this remuxes certain pins on the BeagleBoneBlack's pin headers   
to allow for more GPIO ports).                                                   
                                                                                 
* Pinout for the LCD screen.                                                       
    P8_07 -> RS                                                                      
    P8_09 -> RW                                                                      
    P8_11 -> E                                                                       
    P8_13 -> D4                                                                      
    P8_15 -> D5                                                                      
    P8_17 -> D6                                                                      
    P8_19 -> D7                                                                      
                                                                                 
* Pinout for the accelerometer.                                                    
    P9_19 -> SCL                                                                     
    P9_20 -> SDA                                                                     
                                                                                 
* Pin for the kill process button (note that this button should be configured to   
be pulled-low and should set the value ot P9_23 to high when it is switched).    
    P9_23 -> Button         

## Compiling the program
A makefile is included in order to compile the files for the GMeter cape. To
compile the entire project, run:

> make

This will populate the current directory with all of the associated executables
for running the project.

## Running the program
Once everything has been wired together, run:

> ./GMeter

This will fork off processes for both the LCD screen and the LSM303
accelerometer, and will establish pipes between the two of them for data
transfer. The output of the accelerometer should be sent to the LCD for
displaying as well.

## Killing the program
To kill the program, either hit ctrl-C or use the button associated with P9_23
(if setup on your circuit).

## Cleaning up
To cleanup all of the files created by make, run:

> make clean

## Fortune
     _____________________________________ 
    ( HELP!!!! I'm being held prisoner in )
    ( /usr/games/lib!                     )
     ------------------------------------- 
         o
          o
              oO)-.                       .-(Oo
             /__  _\                     /_  __\
             \  \(  |     ()~()         |  )/  /
              \__|\ |    (-___-)        | /|__/
              '  '--'    ==`-'==        '--'  '
