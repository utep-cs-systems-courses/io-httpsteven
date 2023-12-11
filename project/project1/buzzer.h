#ifndef BUZZER_INCLUDED
#define BUZZER_INCLUDED

void buzzer_init();
void buzzer_set_period(short cycles);
void play_note(int note, float duration);

#endif // BUZZER_INCLUDED

