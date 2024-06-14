#ifndef RTC_H_
#define RTC_H_

#include <avr/io.h>

// Definir la direccion del RTC
#define RTC_ADDRESS 0x68

void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Write(uint8_t data);
uint8_t I2C_Read(uint8_t final);

void RTC_GetTime(uint8_t *hour, uint8_t *minute, uint8_t *second);
void RTC_GetDate(uint8_t *day, uint8_t *month, uint8_t *year);
void RTC_GetDateAndTime(uint8_t *day, uint8_t *month, uint8_t *year, uint8_t *hour, uint8_t *minute, uint8_t *second);

#endif /* RTC_H_ */