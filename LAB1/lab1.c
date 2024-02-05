//******************************************************************************
//Universidad del Valle de Guatemala
// IE2023 Programación de Microcontroladores
// Autor:
// Proyecto:
// Descripción:
// Hardware: ATMega328P
// Created:
//******************************************************************************
//Encabezado
//******************************************************************************
.include "M328PDEF.inc"
.cseg // segmento del codigo
.org 0x00 // parte del codigo en el que vamos a iniciar
//******************************************************************************
//Configuración de la pila
//******************************************************************************
LDI R16, LOW(RAMEND)
OUT SPL, R16 // stack counter parte baja
LDI R17, HIGH(RAMEND)
OUT SPH, R17
//******************************************************************************

//******************************************************************************
//Configuración MCU
//******************************************************************************
SETUP:
	SBI DDRB, PB5 //estamos agarrando el registro ddrb y estamos modificando explicitamente el bit 5. SBI=SET,arriba estamos definiendo PB5 como salida.
	
	CBI PORTB, PB5 //colocar 0 en el PB5.

	
//******************************************************************************
//Loop Infinito
//******************************************************************************
LOOP:
	SBI PORTB, PB5
	CBI PORTB, PB5
	CALL DELAY

	RJMP LOOP
//******************************************************************************
// Subrutinas
//******************************************************************************
Delay:
	LDI R18, 0
INCR18 //LAS ETIQUETAS SON PLACE HOLDER DE ALGO QUE VAS A LLAMAR DESPUES
	INC R18
	CPI R18, 100 // COMPARA
	BRNE INCR18 //SALTA SI NO ES IGUAL
	RET
//******************************************************************************