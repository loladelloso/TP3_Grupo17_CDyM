#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "SerialPort.h"
#include "DHT11.h"
#include "RTC.h"
#include "SensorReg.h"

//volatile uint8_t Flag_SendData = 0;
char detener[] = "Se detuvo el envio de datos.\r\n";

int main(void)
{
		
	// Inicialización de los módulos
	SerialPort_Init(0x67); // Configurar UART a 9600bps, 8 bits de datos, 1 bit de parada @ F_CPU = 8MHz.
	SerialPort_TX_Enable(); // Habilitar transmisor USART.
	SerialPort_RX_Enable(); // Habilitar receptor USART.
	SerialPort_RX_Interrupt_Enable(); // Habilitar interrupción de receptor USART.
	
	// Inicialización del Timer1
	Timer1_Init();
	
	// inicializacion de DHT11 
	DHT11_Init();
	// incializacion del RTC
	I2C_Init();
	
	SerialPort_Send_String("Presione S para iniciar el envio de datos\r\n");
	sei();
	while (1) {
		
		if (getFlag()) {
			Task_Sensor();
			setFlag(0);
		}
	}
	
	
	return 0;
}

