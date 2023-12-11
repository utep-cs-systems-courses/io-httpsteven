# Makefile configuration
COMMON_OBJECTS  = main.o libTimer.o buzzer.o
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS         = -L/opt/ti/msp430_gcc/include

# Switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

# Target executable
TARGET          = main.elf

all: ${TARGET}

# Additional rules for files
${TARGET}: ${COMMON_OBJECTS} ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: ${TARGET}
	msp430loader.sh $^

clean:
	rm -f *.o *.elf
