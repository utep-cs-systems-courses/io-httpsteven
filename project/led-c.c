#include <msp430.h>
#include "led.h"

void led_init() {
  P1DIR |= LEDS;
  P1OUT &= LED_GREEN;
  P1OUT &= LED_RED;
}

void toggle_green(){
  
  // if(P1OUT & LED_GREEN)
  //  P1OUT &= ~LED_GREEN;
  //else
  //  P1OUT |= LED_GREEN;

  P1OUT ^= LED_GREEN;
}



void toggle_red(){
  // if(P1OUT & LED_RED)
  //  P1OUT &= ~LED_RED;
  //else
  //  P1OUT |= LED_RED;

  P1OUT ^= LED_RED;
}