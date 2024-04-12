/******************************************************************************
//Encabezado
//Universidad del Valle de Guatemala
// IE2023 Programación de Microcontroladores
// Autor: Rodrigo Oliveros
// Proyecto: LAB4
// Descripción: Contador de 8 bits con C
// Hardware: ATMega328P
// Created:04/04/2024 
//Facilitadores
*******************************************************************************/
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h> //Frencuencia de reloj
#include <stdint.h>



void setup(void);
void initADC(void);
//Variables
uint8_t contador = 0;
uint8_t actual = 0;
uint8_t anterior = 0xFF;
uint8_t tabla [16] = {
	0b0111111,
	0b0000110,
	0b1011011,
	0b1001111,
	0b1100110,
	0b1101101,
	0b1111101,
	0b0000111,
	0b1111111,
	0b1110111,
	0b1111100,
	0b0111001,
	0b1011110,
	0b1111001,
	0b1110001
	};
uint8_t baja = 0; //parte baja del ADCH
uint8_t alta = 0; //parte alta del ADCH
uint8_t alarma = 0; 

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
				
		PORTD = tabla[baja];
		PORTC = alarma;
		PORTC |= 0b00000010;
		_delay_ms(70);
		PORTD = tabla[alta];
		PORTC = alarma;
		PORTC |= 0b00000100;
		_delay_ms(70);
		PORTD = contador;
		PORTC = alarma;
		PORTC |= 0b00000001;
		_delay_ms(70);
		//FUNCION DE ALARMA
		if(contador < ADCH) {
			alarma = 0x10; //encender led
		}
		else {
			alarma = 0x00; //apagar led
		}
		//CONTADOR DE 8 BITS
		actual = PINB; //Leer los botones en el puerto B.
		if(actual!=anterior){
			
		_delay_ms(15); //Delay para aclarar valor
		actual = PINB;//Lectura clara
		
		if(actual!=anterior){//Si se cumple, en realidad se presiono un boton
			if(!(PINB & 0x01)) {
				contador--;
			}
			if(!(PINB & 0x02)) {
				contador++;
			}
			anterior=actual;
			}
		}
	}
}


void setup(void) {
	//salidas
	UCSR0B = 0;
	DDRD = 0xFF;
	PORTD = 0x00;
	DDRC = 0b00001111;
	//entradas
	DDRB &= ~(1<<DDB0)|~(1<<DDB1);
	PORTB &= ~(1<<DDB0)|~(1<<DDB1);
}
void initADC(void) {
	ADMUX = 0;
	ADMUX |= (1<<REFS0);//REF 5V
	ADMUX |= (1<<ADLAR); //LEFT
	ADMUX |= (1<<MUX2)|(1<<MUX1)|(1<<MUX0);
	ADCSRA = 0;

	ADCSRA |= (1<<ADIE); //ADC INTERRUPT ON
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //FREC 125KHZ
	ADCSRA |= (1<<ADEN); //ADC ON
}
//Interrupciones
ISR(ADC_vect){
	baja = (ADCH & 0x0F); //almacenamos parte baja
	alta = (ADCH & 0xF0); //almacenamos parte alta
	alta = alta >> 4;  //corrido 4 espacios
	ADCSRA |= (1<<ADIF);
	ADCSRA |= (1<<ADSC);
}