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

//******************************************************************************
//Configuración MCU
//******************************************************************************
SETUP:
//SALIDAS
	SBI DDRD, PD2//G
	SBI DDRD, PD3//F
	SBI DDRD, PD4//A
	SBI DDRD, PD5//B
	SBI DDRD, PD6//E
	SBI DDRD, PD7//D
	
	SBI DDRB, PB0//C
	SBI DDRB, PB1//PT

//ENRTRADAS
	
	CBI DDRC, PC0
	CBI DDRC, PC1
	CBI DDRC, PC2
	CBI DDRC, PC3
	CBI DDRC, PC4
	CBI DDRC, PC5
//******************************************************************************
//Loop Infinito
//******************************************************************************
	
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