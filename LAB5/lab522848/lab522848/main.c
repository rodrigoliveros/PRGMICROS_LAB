/******************************************************************************
//Encabezado
//Universidad del Valle de Guatemala
// IE2023 Programaci?n de Microcontroladores
// Autor: Rodrigo Oliveros
// Proyecto: LAB4
// Descripci?n: Contador de 8 bits con C
// Hardware: ATMega328P
// Created:04/04/2024
//Facilitadores
*******************************************************************************/
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h> //Frencuencia de reloj
#include <stdint.h>

volatile uint8_t potValue = 0;

void setup(void);
void initADC(void);

int main(void)
{
	cli();
	setup();
	initADC();
	sei();
	ADCSRA |= (1<<ADSC);
	//loop principal
	while (1)
	{
		// Convertir el valor del potenciómetro a un rango de 1000 a 2000 (aproximadamente)
		// utilizando una regla de tres simple.
		uint16_t pulseWidth = (uint16_t)potValue * 11 + 1000;

		// Generar señal PWM para el servo
		OCR1A = pulseWidth;

		//_delay_ms(15); // Pequeña pausa para estabilizar el movimiento
	}
}
void setup(void) {
	//salidas
	UCSR0B = 0;
	DDRD = 0xFF;
	PORTD = 0x00;
	DDRB |= (1<<DDB0)|(1<<DDB1);
	
	// Configurar Timer 1 para generar PWM en modo Fast PWM
	TCCR1A |= (1 << COM1A1) | (1 << WGM11); // Configurar OC1A en modo Fast PWM
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Modo Fast PWM, prescaler 8
}
void initADC(void) {
	ADMUX = 0;
	ADMUX |= (1<<REFS0);//REF 5V
	ADMUX |= (1<<ADLAR); //LEFT
	ADMUX |= (1<<MUX2)|(1<<MUX1)|(1<<MUX0);
	ADCSRA = 0;

	ADCSRA |= (1<<ADIE); //ADC INTERRUPT ON
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1); //FREC 125KHZ
	ADCSRA |= (1<<ADEN); //ADC ON
	ADCSRB = 0;
	DIDR0 |= (1<<ADC0D);
	ADMUX &= ~(1 << MUX0); // Selección inicial de canal ADC
	ADCSRA |= (1 << ADSC);	
}
//Interrupciones
ISR(ADC_vect){
	
	potValue = ADCH;
	ADCSRA |= (1<<ADIF);
	ADCSRA |= (1<<ADSC);
}