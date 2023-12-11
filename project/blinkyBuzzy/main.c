#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

int main() {
  configureClocks();
  led_init();
  switch_init();
  buzzer_init();
  enableWDTInterrupts();
  or_sr(0x18); // CPU off, GIE on
}

int temp = 0;
int led_state = 0;

void play_state_machine(int tones[], float durations[], int num_tones) {
  for (int i = 0; i < num_tones; i++) {
    play_tone(tones[i], durations[i]);
    temp++;
    if (temp >= num_tones) {
      temp = 0;
    }
  }
}

void led_state_machine() {
  switch (led_state) {
    case 0:
      toggle_red();
      play_tone(1000, 0.2);
      break;
    case 1:
      toggle_red();
      play_tone(1500, 0.2);
      break;
    case 2:
      toggle_red();
      toggle_green();
      play_tone(2000, 0.2);
      break;
  }

  led_state++;
  if (led_state >= 3) {
    led_state = 0;
  }
}

void __interrupt_vec(WDT_VECTOR) WDT() {
  static int idle_tone_counter = 0;
  
  int* states = get_switches_states();

  if (idle_tone_counter < 1000) {
    play_tone(500, 0.2);
    idle_tone_counter++;
  } else {
    idle_tone_counter = 0;
  }

  led_state_machine();

  // Additional logic based on button states if needed

  set_switches_states();
}
