#include "Timer.h"
#include <avr/interrupt.h>

volatile uint8_t Flag_Sensor = 0;
volatile uint8_t cant = 0;

void Timer1_Init(void) {
	
	TCCR1B |= (1 << WGM12);	 // Timer1 en modo CTC
	OCR1A = 62499;			 // 62499 cuentas para 2 segundos con prescaler 256
	TIMSK1 |= (1 << OCIE1A); // Habilita la interrupción por comparación de salida A
	TCCR1B |= (1 << CS12);	 // Configura el prescaler a 256 y arrancar el temporizador
}

uint8_t getFlag(){
	return Flag_Sensor;	
}

void setFlag(uint8_t x){
	Flag_Sensor = x;
}
 
ISR(TIMER1_COMPA_vect) {
	if(cant % 2)
	{
		Flag_Sensor = 1;
	}	
	cant++;
}
