#ifndef DHT11_H_
#define DHT11_H_

#include <avr/io.h>

void DHT11_Init(void);
uint8_t DHT11_Read(int *temp1, int *temp2, int *hum1, int *hum2);

#endif /* DHT11_H_ */