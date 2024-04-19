/*
 * lab622848.c
 *
 * Created: 19/04/2024 14:05:09
 * Author : rodri
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void initUART9600(void);
void writeUART(char Caracter);
void writeTEXTUART(char * Texto);

volatile uint8_t buffertx;

int main(void)
{
	initUART9600();
	sei();
	writeUART('M');
	writeUART('e');
	writeUART('n');
	writeUART('s');
	writeUART('a');
	writeUART('j');
	writeUART('e');
	writeUART('\n');
	
    /* Replace with your application code */
    while (1) 
    {
		PORTB = buffertx;
    }
}
void initUART9600(void){
	DDRB = 0xFF;
	PORTB = 0x00;
	DDRD &= ~(1<<DDD0);
	DDRD |= (1<<DDD1);
	UCSR0A = 0;
	//Configurar el UCSR0B, tx y rx
	UCSR0B = 0;
	UCSR0B |= (1<<RXCIE0) | (1<<RXEN0) |(1<<TXEN0);
	//Configurar UCSR0C, ASINCRONO, PARIEDAD NONE, 1 BIT STOP, DATA 8 BITS
	UCSR0C = 0;
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	//Configurar velocidad de Baudrate: 9600
	UBRR0 = 103;
}
void writeUART(char Caracter) {
	while(!(UCSR0A & (1<<UDRE0))); //UCSR0A sea 1 
	UDR0 = Caracter; 
}

ISR(USART_RX_vect) {
	buffertx = UDR0;
	//lo que yo le mande me responde lo mismo
	while(!(UCSR0A & (1<<UDRE0))); //UCSR0A sea 1
	UDR0 = buffertx;
}