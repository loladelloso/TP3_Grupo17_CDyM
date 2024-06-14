#include <avr/io.h>
#include <util/twi.h>
#include "RTC.h"

void I2C_Init(void) {
	TWSR = 0x00;
	TWBR = 0x47;//((16000000/100000)-16)/2; //0x47;
	TWCR = (1 << TWEN);
}

void I2C_Start(void) {
	TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));
}

void I2C_Stop(void) {
	TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);
}

void I2C_Write(uint8_t data) {
	TWDR = data;
	TWCR = (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));
}

uint8_t I2C_Read(unsigned char final){
	if (final == 0) // send ACK
		TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA); 
	else
		TWCR = (1 << TWEN) | (1 << TWINT); // send NACK
	while ((TWCR & (1 << TWINT)) == 0);
	return TWDR;
}


uint8_t bcd_to_dec(uint8_t bcd) {
	//bcd contiene dos dígitos decimales en formato BCD y lo convierte a un valor decimal.
	return ((bcd / 16 * 10) + (bcd % 16));
}

void RTC_GetTime(uint8_t *hour, uint8_t *minute, uint8_t *second) {
	I2C_Start();
	I2C_Write((RTC_ADDRESS << 1) | TW_WRITE);
	I2C_Write(0x00);
	I2C_Start();
	I2C_Write((RTC_ADDRESS << 1) | TW_READ);
	*second = bcd_to_dec(I2C_Read(0));
	*minute = bcd_to_dec(I2C_Read(0));
	*hour = bcd_to_dec(I2C_Read(1));
	I2C_Stop();
}

void RTC_GetDate(uint8_t *day, uint8_t *month, uint8_t *year) {
	I2C_Start();
	I2C_Write((RTC_ADDRESS << 1) | TW_WRITE);
	I2C_Write(0x04);
	I2C_Start();
	I2C_Write((RTC_ADDRESS << 1) | TW_READ);
	*day = bcd_to_dec(I2C_Read(0));
	*month = bcd_to_dec(I2C_Read(0));
	*year = bcd_to_dec(I2C_Read(1));
	I2C_Stop();
}
