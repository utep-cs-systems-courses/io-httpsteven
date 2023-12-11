# Makefile configuration

COMMON_OBJECTS  = main.o switches.o buzzer.o 

CPU             = msp430g2553

CFLAGS          = -mmcu=${CPU} -I../h

LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: project-c.elf project-s.elf

#additional rules for files

project-c.elf: ${COMMON_OBJECTS} led-c.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ ../lib/libTimer.a

project-s.elf: ${COMMON_OBJECTS} led-s.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ ../lib/libTimer.a

load-c: project-c.elf
	msp430loader.sh $^

load-s: project-s.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf *~

main.o: led.h
led-c.o: led.h
wdInterruptHandler.o:  led.h
led-c.o: led.h led-c.c
