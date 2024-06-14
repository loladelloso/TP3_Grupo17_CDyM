#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>

#define DHT11_PIN PORTC0
#define DHT11_DDR DDRC
#define DHT11_PORT PORTC
#define DHT11_PIN_INPUT PINC

void DHT11_Init(void) {
	DHT11_DDR |= (1 << DHT11_PIN); // Configura el pin como salida
	DHT11_PORT |= (1 << DHT11_PIN); // Establece el pin en alto
}

uint8_t DHT11_Read(int *temp1, int *temp2, int *hum1, int *hum2) {
	uint8_t bits[5] = {0}; // Asegurarse de inicializar los bits a 0
	uint8_t i, j = 0;


	DHT11_DDR |= (1 << DHT11_PIN); // Configura el pin como salida
	DHT11_PORT |= (1 << DHT11_PIN); // Establece el pin en alto
	_delay_ms(5);

	// Envia señal de inicio: Señal baja por 18 ms
	DHT11_PORT &= ~(1 << DHT11_PIN);
	_delay_ms(20);
	// MCU envía señal alta por 20-40 us para esperar que se prepare el DHT11
	DHT11_PORT |= (1 << DHT11_PIN);
	//_delay_us(24);

	// Configura el pin como ENTRADA para LEER la respuesta del DHT11
	DHT11_DDR &= ~(1 << DHT11_PIN);
	
	// Espera a que el pin se ponga bajo (máximo 80 us)
	while (DHT11_PIN_INPUT & (1 << DHT11_PIN));
	//_delay_us(80);

	// Espera a que el pin se ponga alto (máximo 80 us)
	while (!(DHT11_PIN_INPUT & (1 << DHT11_PIN)));
	//_delay_us(80);

	// Espera a que el pin se ponga bajo nuevamente
	while (DHT11_PIN_INPUT & (1 << DHT11_PIN));
	//_delay_us(50);
	// Lee los datos del DHT11
	for (j = 0; j < 5; j++) {
		uint8_t result = 0;
		for (i = 0; i < 8; i++) {
			// Espera a que el pin se ponga alto
			while (!(DHT11_PIN_INPUT & (1 << DHT11_PIN)));

			_delay_us(30); // Espera 40 us

			// Si despues de 40 us esta:
			// -En alto: bit = 1
			// -En bajo: bit = 0
			// Como result se inicializa con todo en 0, no hace falta
			// especificar que se le esta asignando un 0 a la posicion i
			// Solo se asigna 1 cuando es necesario
			if (DHT11_PIN_INPUT & (1 << DHT11_PIN)) {
				result |= (1 << (7 - i)); // Establece el bit 'i' en 1
			}

			// Espera a que el pin se ponga bajo
			while (DHT11_PIN_INPUT & (1 << DHT11_PIN));
		}
		bits[j] = result;
	}

	// Espera a que el pin se ponga alto
	while (!(DHT11_PIN_INPUT & (1 << DHT11_PIN)));

	// Configura el pin como salida y lo establece en alto
	DHT11_DDR |= (1 << DHT11_PIN);
	DHT11_PORT |= (1 << DHT11_PIN);

	// Verificación de la suma de comprobación
	if ((uint8_t)(bits[0] + bits[1] + bits[2] + bits[3]) != bits[4]) {
		return 1;
	}
	
	*hum1 = bits[0];
	*hum2 = bits[1];
	*temp1 = bits[2];
	*temp2 = bits[3];

	return 0;
}