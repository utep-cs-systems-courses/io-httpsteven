#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

void buzzer_init()
{
    /* 
       Direct timer A output "TA0.1" to P1.2.  
        According to table 21 from data sheet:
          P1SEL2.6, P1SEL2.7, anmd P1SEL.7 must be zero
          P1SEL.6 must be 1
        Also: P1.2 direction must be output
    */
    timerAUpmode();		/* used to drive speaker */
    P1SEL2 &= ~(BIT6 | BIT7);
    P1SEL &= ~BIT7; 
    P1SEL |= BIT6;
    P1DIR = BIT6;		/* enable output to speaker (P1.2) */
}

void buzzer_set_period(short cycles) /* buzzer clock = 2MHz.  (period of 1k results in 2kHz tone) */
{
  CCR0 = cycles; 
  CCR1 = cycles >> 1;		/* one half cycle */
}
