// libTimer.h

#ifndef LIBTIMER_H
#define LIBTIMER_H

// Define LEDs
#define LED_RED BIT0       // P1.0
#define LED_GREEN BIT6     // P1.6
#define LEDS (BIT0 | BIT6)

void configureClocks();
void enableWDTInterrupts();
void timerAUpmode();

#endif /* LIBTIMER_H */
