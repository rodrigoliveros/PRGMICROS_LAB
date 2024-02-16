//******************************************************************************
//Encabezado
//******************************************************************************
//Universidad del Valle de Guatemala
// IE2023 Programación de Microcontroladores
// Autor: Rodrigo Oliveros
// Proyecto: Labororatorio#3
// Descripción: Mostrar en un display un numero
// Hardware: ATMega328P
// Created:
//******************************************************************************
//Facilitadores
//******************************************************************************
.include "M328PDEF.INC"
.cseg 
.org 0x00
	JMP		MAIN

.org 0x0006
	JMP		ISR_PCINT0

.org 0x0020
	JMP		ISR_TIMER0

//******************************************************************************
//Tabla 7 segmentos
//******************************************************************************
TABLA7SEG: .DB	 0x00, 0xC, 0xB6, 0x9E, 0xCC, 0xDA, 0xFA, 0xE, 0xFF, 0xCE, 0x1EE, 0x1F8, 0x72, 0xBC, 0xF2, 0x1E2 
//******************************************************************************
//Configuracion
//******************************************************************************
MAIN:
	LDI		R16, LOW(RAMEND)
	OUT		SPL, R16 
	LDI		R17, HIGH(RAMEND)
	OUT		SPL, R17
//******************************************************************************
//SETUP
//******************************************************************************
SETUP:
	LDI		ZL, LOW(TABLA7SEG << 1)
	LDI		ZH, HIGH(TABLA7SEG << 1)
	
	//Oscilador
	LDI		R16, (1 << CLKPCE)	;Habilitamos el prescaler
	STS		CLKPR, R16 
	LDI		R16, 0				;16Hz
	STS		CLKPR, R16
	
	//Entradas y salidas
	LDI		R16, 0x00	
	STS		UCSR0B, R16			
	LDI		R16, 0xFF	
	OUT		DDRD, R16			;PORTD salida
	LDI		R16, 0xFF	
	OUT		DDRC, R16			;PORTC salida

	//Interrupciones
	LDI		R16, 0
	OUT		TCCR0A, R16			;Contador
	LDI		R16, 5
	OUT		TCCR0B, R16			;PRE 1024
	LDI		R16, 1				
	STS		TIMSK0, R16			;Habilitar TOIE0
	LDI		R16, 99				
	OUT		TCNT0, R16			;Initial value

	LDI		R16, 3
	STS		PCMSK0, R16			;HABILITA PCINT0 y PCINT1
	LDI		R16, 1				;
	STS		PCICR, R16			;HABILITA PCIE0

	LDI		R16, 0
	LDI		R17, 0
	LDI		R18, 0
	LDI		R19, 0
	LDI		R20, 0

	LPM		R18, Z
	OUT		PORTD, R18

	SEI

LOOP:
	CPI		R21, 100				; R21 = 100
	BRNE	LOOP					; Loop si no son iguales
	LDI		R21,0					; Iguales reset
	INC		ZL						; Mover en tabla
	LPM		R18, Z					; Cargar R18 con la posición de Z
	OUT		PORTD, R18				; SACAR A PORTD
	CPI		R18, 0x0f				; Esta en el final?
	BRNE	LOOP					; Regresar a loop si no esta en el final
	LDI		ZL, LOW(TABLA7SEG << 1)	 
	LDI		ZH, HIGH(TABLA7SEG << 1); Regresar al inicio de la tabla
	LPM		R18, Z					; Cargar R18 la posición de z
	OUT		PORTD, R18				; SACAR A PORTD
	RJMP	LOOP					

//******************************************************************************
//SUBRUTINAS
//******************************************************************************

//Interrupción 1
ISR_TIMER0:
	PUSH	R16					;Guardamos para no perder counter ni resultados
	IN		R16, SREG			
	PUSH	R16					
		
	INC		R21					

	LDI		R17, 99				
	OUT		TCNT0, R17			;Initial Value

	POP		R16					;Sacamos de la pila
	OUT		SREG, R16			
	POP		R16					
	RETI

//Interrupción 2
ISR_PCINT0:
	PUSH	R16					;Guardamos para no perder counter ni resultados
	IN		R16, SREG			
	PUSH	R16					

B1:
	IN		R19, PINB			
	SBRC	R19, PB0			;PINB0 = 0 ?
	RJMP	B2				;No es igual, revisar boton 2
	INC		R20					;Igual, incrementamos
	OUT		PORTC, R20			
	RJMP	SALIR				
		
B2:
	IN		R19, PINB			
	SBRC	R19, PB1			;PINB1 = 0 ?
	RJMP	SALIR				;No es igual, salir de la rutina
	DEC		R20					;Igual, drecrementamos
	OUT		PORTC, R20			

SALIR:
	POP		R16					;Salimos de la rutina
	OUT		SREG, R16			
	POP		R16					
	RETI