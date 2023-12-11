#include <msp430.h>
#include "led.h"

void led_init() {
  P1DIR |= LED_RED;
  P1OUT &= ~LED_RED;
}

void toggle_red() {
  P1OUT ^= LED_RED;
}
