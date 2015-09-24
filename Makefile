# Make file for Geez driver executable

CC = g++
CFLAGS = -Wall
GEEZ_OBJS = Geez.o LSM303.o LCD.o GPIO.o 
LCD_DRIVER_OBJS = LCD.o LCDdriver.o GPIO.o
ACCEL_DRIVER_OBJS = LSM303.o AccelDriver.o

all: $(GEEZ_OBJS) $(LCD_DRIVER_OBJS) $(ACCEL_DRIVER_OBJS)
	make AccelDriver 
	make Geez 
	make LCDdriver

Geez: $(GEEZ_OBJS)
	$(CC) $(CFLAGS) $(GEEZ_OBJS) -o Geez

LCDdriver: $(LCD_DRIVER_OBJS)
	$(CC) $(CFLAGS) $(LCD_DRIVER_OBJS) -o LCDdriver

AccelDriver: $(ACCEL_DRIVER_OBJS)
	$(CC) $(CFLAGS) $(ACCEL_DRIVER_OBJS) -o AccelDriver

LSM303.o: Libraries/LSM303/LSM303.cpp
	$(CC) $(CFLAGS) Libraries/LSM303/LSM303.cpp -c

LCD.o: Libraries/LCD/LCD.cpp
	$(CC) $(CFLAGS) Libraries/LCD/LCD.cpp -c

GPIO.o: Libraries/GPIO/GPIO.cpp
	$(CC) $(CFLAGS) Libraries/GPIO/GPIO.cpp -c

LCDdriver.o: Drivers/LCDdriver.cpp
	$(CC) $(CFLAGS) Drivers/LCDdriver.cpp -c

AccelDriver.o: Drivers/AccelDriver.cpp
	$(CC) $(CFLAGS) Drivers/AccelDriver.cpp -c

%.c: %.h
	touch $@

clean:
	rm *.o AccelDriver Geez LCDdriver
