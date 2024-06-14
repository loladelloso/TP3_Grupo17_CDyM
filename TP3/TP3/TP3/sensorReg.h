#ifndef SensorReg_H_
#define SensorReg_H_

#include <avr/io.h>
extern volatile uint8_t Flag_SendData;

void Task_Sensor(void);

#endif /* SensorReg_H_ */
