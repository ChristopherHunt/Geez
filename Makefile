# Make file for GMeter driver executable

CC = g++
CFLAGS = -Wall
GMETER_OBJS = GMeter.o LSM303.o LCD.o GPIO.o 
LCD_DRIVER_OBJS = LCD.o LCDdriver.o GPIO.o
ACCEL_DRIVER_OBJS = LSM303.o AccelDriver.o

all: $(GMETER_OBJS) $(LCD_DRIVER_OBJS) $(ACCEL_DRIVER_OBJS)
	make AccelDriver 
	make GMeter 
	make LCDdriver

GMeter: $(GMETER_OBJS)
	$(CC) $(CFLAGS) $(GMETER_OBJS) -o GMeter

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

LCDdriver.o: Driver/LCDdriver.cpp
	$(CC) $(CFLAGS) Driver/LCDdriver.cpp -c

AccelDriver.o: Driver/AccelDriver.cpp
	$(CC) $(CFLAGS) Driver/AccelDriver.cpp -c

%.c: %.h
	touch $@

clean:
	rm *.o AccelDriver GMeter LCDdriver
