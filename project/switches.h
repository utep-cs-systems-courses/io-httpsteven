#ifndef SWITCHES_H
#define SWITCHES_H

#define NUM_SWITCHES 5

#define SW1 BIT0
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3
#define TOP_SWITCH BIT4

void switch_init();
void switch_interrupt_handler();
int* get_switches_states();
void set_switches_states();

#endif // SWITCHES_H
