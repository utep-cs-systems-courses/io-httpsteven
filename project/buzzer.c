#include <msp430.h>
#include "buzzer.h"
#include "libTimer.h"

void buzzer_init() {
  timerAUpmode(); // Used to drive the speaker
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6; // Enable output to the speaker (P2.6)
}

void buzzer_set_period(short cycles) {
  CCR0 = cycles;
  CCR1 = cycles >> 1; // One half cycle
}

void play_tone(int frequency, float duration) {
  buzzer_set_period(frequency);
  __delay_cycles(1000000); // Add a delay for better sound separation
  buzzer_set_period(0); // Stop playing tone
}
