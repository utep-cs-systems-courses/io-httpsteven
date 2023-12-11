#ifndef SWITCH_INCLUDED
#define SWITCH_INCLUDED

#define SW1 BIT3
#define SW2 BIT0
#define SW3 BIT1
#define SW4 BIT2
#define SW5 BIT3
#define TOP_SWITCH (SW2 | SW3 | SW4 | SW5)

void switch_init();
void set_switches_states();
void switch_interrupt_handler();
int* get_switches_states();

#endif // SWITCH_INCLUDED
