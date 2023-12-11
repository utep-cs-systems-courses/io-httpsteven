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
int oMelody[] = {
  784, 0, 784, 0, 784, 0, 659, 0, 784, 0, 659, 0, 659,
};
float oDuration[] = {

0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25


  
};


//Notes for shooting stars

int sMelody[] = {

  311,
  0,
  311,
  0,
  329,
  0,
  493,
  415
  
};
float sDuration[] = {

  .75,
  .5,  // 0
  .5,
  .5, //0
  .5,
  .5, //0
  .5,
  .25
};


void play_stars(int melody[], float duration[],char play_m){

  if (play_m == 's') {
    play_note(melody[temp] * 3,duration[temp]);
    temp++;
    if(temp > 7) {
      temp = 0;
      play_stars(melody,duration,' ');
      return;
    }else{
      play_stars(melody,duration,'s');
    }
  }
    
}

void play_ocarina(int melody[], float duration[], char play_m) {
  if (play_m == 'o') {
    play_note(melody[temp] * 4, duration[temp]);
    temp++;
    if (temp > 63) {
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
  

  
  else if(states[3]){
    toggle_green();
    play_ocarina(oMelody,oDuration,'m');
    play_ocarina(oMelody,oDuration,'m');
    toggle_green();
    set_switches_states();
    //secondCount++;
   }

  else if(states[4]){
    toggle_green();
    play_stars(sMelody,sDuration,'s');
    play_stars(sMelody,sDuration,'s');
    toggle_green();
    set_switches_states();
  }
}
