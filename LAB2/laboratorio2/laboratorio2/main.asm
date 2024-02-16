//******************************************************************************
//Universidad del Valle de Guatemala
// IE2023 Programación de Microcontroladores
// Autor: Rodrigo Oliveros
// Proyecto: Labororatorio#2
// Descripción: Mostrar en un display un numero
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
TABLA7SEG: .DB 0x00, 0xC, 0xB6, 0x9E, 0xCC, 0xDA, 0xFA, 0xE, 0xFF, 0xDE
//******************************************************************************
//Configuración MCU
//******************************************************************************
SETUP:
//SALIDAS
	LDI R19, 0xDE
	LDI R20, 0x00

	OUT DDRD, R19 //CONFIGURAR PUERTO D COMO SALIDAS
	OUT DDRC, R20 // CONFIGURAR PUERTO A COMO ENTRADAS
	STS UCSR0B, R20
	

//******************************************************************************
//Loop Infinito
//******************************************************************************
	LDI R18, 0xFF
	OUT PORTD, R18
//******************************************************************************
// Subrutinas
//******************************************************************************
CONTCUATRO: //LAS ETIQUETAS SON PLACE HOLDER DE ALGO QUE VAS A LLAMAR DESPUES
	LDI R18, 0
INCR18:
	INC R18
	CPI R18, 16 // COMPARA
	BRNE INCR18 //SALTA SI NO ES IGUAL
	RET
//******************************************************************************