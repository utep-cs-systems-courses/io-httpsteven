#ifndef BUZZER_H
#define BUZZER_H

void buzzer_init();
void buzzer_set_period(short cycles);
void play_tone(int frequency, float duration);

#endif // BUZZER_H
