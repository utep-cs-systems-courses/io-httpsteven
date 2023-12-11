#include <msp430.h>
#include "buzzer.h"
#include "libTimer.h"
#include <stdio.h>

int delay_int = 0;

void buzzer_init() {

  timerAUpmode(); // Used to drive speaker
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6; // Enable output to speaker (P2.6)

}

void buzzer_set_period(short cycles) {
  
  CCR0 = cycles;
  CCR1 = cycles >> 1; // One half cycle

}

void delay_ms(unsigned int ms) {
  unsigned int i;

  for (i = 0; i <= ms; i++) {
    __delay_cycles(2000); // Approximately 1 millisecond at 2MHz
  }
}

void play_note(int note, float duration) {
  
  buzzer_set_period(note);
  delay_int = (int)(duration * 4000);
  delay_ms(delay_int); // Convert duration from seconds to milliseconds
  buzzer_set_period(0); // Stop playing note
  
}
