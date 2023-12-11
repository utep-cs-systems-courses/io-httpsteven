#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

#define LED_RED BIT0               // P1.0
#define LED_GREEN BIT6             // P1.6
#define LEDS (LED_RED | LED_GREEN)

#define SW1 BIT3		/* switch1 is p1.3 */
#define SW2 BIT4		/* switch2 is p1.4 */
#define SW3 BIT5		/* switch3 is p1.5 */
#define SW4 BIT6		/* switch4 is p1.6 */
#define SWITCHES (SW1 | SW2 | SW3 | SW4)	/* 4 switches on this board */

#define BUZZER BIT2  // Buzzer is connected to P1.2

void switch_init() {
  P1REN |= SWITCHES;		/* enables resistors for switches */
  P1IE |= SWITCHES;		/* enable interrupts from switches */
  P1OUT |= SWITCHES;		/* pull-ups for switches */
  P1DIR &= ~SWITCHES;		/* set switches' bits for input */
}

void buzzer_init() {
  P1DIR |= BUZZER;
  P1SEL |= BUZZER;  // Select Timer A output for the buzzer pin
}

void led_init() {
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;		/* leds initially off */
}

void wdt_init() {
  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
}

// Function to play a tone on the buzzer
void play_tone(int frequency) {
  buzzer_set_period(2000000 / frequency);  // Assuming a 2MHz clock frequency
}

void main(void) 
{  
  switch_init();
  buzzer_init();
  led_init();
  wdt_init();
    
  or_sr(0x18);  // CPU off, GIE on
} 

static int buttonDown;
static int state = 0;  // State machine variable

void switch_interrupt_handler()
{
  char p1val = P1IN;

  P1IES |= (p1val & SWITCHES);	/* if switch up, sense down */
  P1IES &= (p1val | ~SWITCHES);	/* if switch down, sense up */

  // Handle each button press based on the state
  switch (state) {
    case 0:  // State 0
      if (p1val & SW1) {
        play_tone(1000);
      } else if (p1val & SW2) {
        play_tone(1500);
      } else if (p1val & SW3) {
        play_tone(2000);
      } else if (p1val & SW4) {
        play_tone(2500);
      }
      break;

    // Add more cases as needed for different states

    default:
      break;
  }
}

void __interrupt_vec(PORT1_VECTOR) Port_1(){
  if (P1IFG & SWITCHES) {
    P1IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}

void __interrupt_vec(WDT_VECTOR) WDT()
{
  static int blink_count = 0;
  switch (blink_count) { 
    case 6: 
      blink_count = 0;
      P1OUT |= LED_RED;
      play_tone(1500);
      break;
    default:
      blink_count ++;
      if (!buttonDown) {
        P1OUT &= ~LED_RED;
        // Stop the buzzer when the button is down
        buzzer_set_period(0);
      }
  }
}
