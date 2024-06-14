#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>

void Timer1_Init(void);
uint8_t getFlag();
void setFlag(uint8_t);

//extern volatile uint8_t Flag_Sensor;

#endif /* TIMER_H_ */
