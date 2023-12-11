#ifndef LED_INCLUDED
#define LED_INCLUDED
#define LED_GREEN BIT6
#define LED_RED BIT0
#define LEDS (BIT0 | BIT6)

void led_init();
void toggle_green();
void toggle_red();

#endif // LED_INCLUDED

