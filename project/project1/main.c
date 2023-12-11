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
int mMelody[] = {

  586,
  0,   
  586, 
  0,   
  1174, 
  0,   
  830, 
  0,   
  880, 
  0,   
  920, 
  0,   
  950,
  0,
  586,
  0,
  950,
  0,
  950,
  0,
  920,
  0,
 
};
float mDuration[] = {

  .14,
  .14,
  .122,
  .122,
  .248,
  .248,
  .368,
  .368,
  .256,
  .256,
  .242,
  .242,
  .251,
  .251,
  .121,
  .121,
  .128,
  .128,
  .121,
  .1,
  .242,
  .242
  
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

void play_megalovania(int melody[], float duration[],char play_m){
  
  if (play_m == 'm') {
    play_note(melody[temp] * 4,duration[temp]);
    temp++;
    if(temp > 18) {
      temp = 0;
      play_megalovania(melody,duration,' ');
      return;
    }else{
      play_megalovania(melody,duration,'m');
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
    play_megalovania(mMelody,mDuration,'m');
    play_megalovania(mMelody,mDuration,'m');
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
