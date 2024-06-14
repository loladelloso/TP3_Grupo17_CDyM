#include "SensorReg.h"
#include "DHT11.h"
#include "RTC.h"
#include "SerialPort.h"
#include <stdio.h>


volatile uint8_t Flag_SendData = 0;
extern char detener[];

void Task_Sensor(void) 
{
	int temp1 = 0, temp2 = 0,hum1 = 0, hum2 = 0;
	char buffer[100];
	uint8_t hour, minute, second, day, month, year;

		if (!(DHT11_Read(&temp1, &temp2, &hum1, &hum2))) 
		{
			RTC_GetTime(&hour, &minute, &second);
			RTC_GetDate(&day, &month, &year);
			snprintf(buffer, sizeof(buffer),
			"TEMP: %d.%d %cC HUM: %d.%d%% FECHA: %02d/%02d/%02d HORA: %02d:%02d:%02d\r\n",
			temp1, temp2,248, hum1, hum2, day, month, year, hour, minute, second);
		}
		if (Flag_SendData) {
			SerialPort_Send_String(buffer);
		}
}

ISR(USART_RX_vect) {
	static volatile uint8_t RX_Buffer = 0;
	RX_Buffer = UDR0; // lee datos ingresados
	
	// Si se ingreso 'S' alterna
	if (RX_Buffer == 's' || RX_Buffer == 'S') {
		Flag_SendData = !Flag_SendData; 
			
		if (!Flag_SendData) {
			SerialPort_Send_String(detener);
		}
	}
}
