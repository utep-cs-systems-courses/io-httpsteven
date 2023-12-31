#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

//temp variable (testing purposes)
int temp = 0;

//Holds the switches states 1 or 0
int* states;

//Holds if megalovania or shooting stars
char play_m = ' ';

//Notes for Megalovania and note length
// Notes for Ocarina of Time melody
int oMelody[] = {
  659, 0,   // E5
  659, 0,   // E5
  698, 0,   // F5
  784, 0,   // G5
  659, 0,   // E5
  698, 0,   // F5
  784, 0,   // G5
  880      // A5
};
float oDuration[] = {
  0.5, 0.5, // E5
  0.5, 0.5, // E5
  0.5, 0.5, // F5
  0.5, 0.5, // G5
  0.5, 0.5, // E5
  0.5, 0.5, // F5
  0.5, 0.5, // G5
  0.5      // A5
};


// Notes for Lavender Town melody
int lMelody[] = {
  523, 0,   // C5
  587, 0,   // D5
  659, 0,   // E5
  698, 0,   // F5
  784, 0,   // G5
  880, 0,   // A5
  988, 0,   // B5
  1047      // C6
};
float lDuration[] = {
  0.5, 0.5, // C5
  0.5, 0.5, // D5
  0.5, 0.5, // E5
  0.5, 0.5, // F5
  0.5, 0.5, // G5
  0.5, 0.5, // A5
  0.5, 0.5, // B5
  0.5      // C6
};


void play_lavender(int melody[], float duration[], char play_m) {
  if (play_m == 'l') {
    play_note(melody[temp], duration[temp]);
    temp++;
    if (temp >= sizeof(lMelody) / sizeof(lMelody[0])) {
      temp = 0;
      play_lavender(melody, duration, ' ');
      return;
    } else {
      play_lavender(melody, duration, 'l');
    }
  }
}

void play_ocarina(int melody[], float duration[], char play_m) {
  if (play_m == 'o') {
    play_note(melody[temp], duration[temp]);
    temp++;
    if (temp >= sizeof(oMelody) / sizeof(oMelody[0])) {
      temp = 0;
      play_ocarina(melody, duration, ' ');
      return;
    } else {
      play_ocarina(melody, duration, 'o');
    }
  }
}


int main() {

  configureClocks();
  led_init();
  // toggle_red();
  //  toggle_green();  //testing led that they are on respectively
  switch_init();
  buzzer_init();
  // buzzer_set_period(1000); //test purpose just checking that the buzzer code works correctly
  
  enableWDTInterrupts();
  
  or_sr(0x18); // CPU off, GIE on

}

// global state var to count time
int reset_switches = 0;
int secondCount = 0;
int case_int = 0;



void __interrupt_vec(WDT_VECTOR) WDT(){    /* 250 interrupts/sec */

  states = get_switches_states();

  //Blinks both lights 10 times every half second with the switch in the red board

  if(states[0]){
    secondCount++;
    if(secondCount >= 60){
      reset_switches++;
      toggle_red();
      toggle_green();
      secondCount = 0;
      if(reset_switches >= 20){
	play_note(1000,3);
	reset_switches = 0;
	set_switches_states();
      }
    }
  }
  else if(states[1]){
      if(secondCount >= 125){
	case_int++;
	secondCount = 0;
      }
      switch(case_int){
      case 0:
	if(!secondCount){
	  toggle_red();
	}
      break;
      case 1:
	if(!secondCount){
	  toggle_green();
	}
      break;
      case 2:
	if(!secondCount){
	  toggle_red();
	  toggle_green();
	}
      break;
      case 3:
	if(!secondCount){
	  toggle_red();
	  toggle_green();
	}
      break;
      case 4:
	if(!secondCount){
	  toggle_red();
	  toggle_green();
	}
      break;
      case 5:
	if(!secondCount){
	  set_switches_states();
	  case_int = 0;
	}
	break;
      }
      secondCount++;
    }
  

  else if(states[2]){
    secondCount++;
    if(secondCount >= 125){
      reset_switches++;
      toggle_green();
      secondCount = 0;
      if(reset_switches >= 20){
  	reset_switches = 0;
  	set_switches_states();
      }
    }
  }
  

  
  else if (states[3]) {
  toggle_green();
  play_ocarina(oMelody, oDuration, 'o');
  toggle_green();
  set_switches_states();
}

  else if (states[4]) {
  toggle_green();
  play_lavender(lMelody, lDuration, 'l');
  toggle_green();
  set_switches_states();
}
}
