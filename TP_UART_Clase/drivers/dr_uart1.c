/*
 * dr_uart.c
 *
 *  Created on: Oct 26, 2018
 *      Author: cha
 */

#include "dr_uart1.h"

volatile uint8_t UART1_txEnCurso;

void UART1_Init(char selector){

	//1. alimentación
	PCONP |= (0x1) << 4;

	//2. frecuencia del clock del periferico: 25Mhz
	PCLKSEL0 &=  ~ ( (0x3) << 8 );

	//3. configuración de trama.

	U1LCR |= (0x3) << 0 ;		// Largo de Trama: 8 bits

	if ( ( selector == 'a' ) || ( selector == '2' ) || ( selector == '3' ) ){
		U1LCR &= ~ ( (0x1) << 3 );	// parity disabled
		U1LCR &= ~ ( (0x1) << 2 );	// UN bit de stop
	}

	if ( selector == 'b' ){
		U1LCR |= ( (0x1) << 3 );	// parity enabled
		// Las siguientes 2 líneas ponen paridad par
		U1LCR |= ( (0x1) << 4 );
		U1LCR &= ~( (0x1) << 5 );
	}

	if ( selector == 'c' ){
		U1LCR &= ~ ( (0x1) << 3 );	// parity disabled
		U1LCR |= ( (0x1) << 2 );	// DOS bit de stop
	}

	U1LCR &= ~( (0x1)<<6 );		// Bit 6. Break Control. 0 es disabled

	//4. Config. BAUDRATE = 9600

	// pongo DLAB en 1
	U1LCR |= (0x1) << 7;

	// DLM. planchamos 0s primero
	U1DLM &= ~ (0xFF) ;

	// DLL
	U1DLL &= ~(0xFF);
	U1DLL |= (0xA3) << 0;

	// deshabilitamos FIFO (por las dudas)
	U1FCR &= ~ ( (0x1) << 0 ) ;

	// 5. Config de Pines

	SetPINSEL( P0_15, 0x1); // tx
	SetPINSEL( P0_16, 0x1);	// rx
	SetMODE(P0_16, 0x2);	// rx pin mode : ninguno

	// 6. Interrupciones del periferico

	// pongo DLAB en 0
	U1LCR &= ~ ( (0x1) << 7 );
	U1IER |= (0x1) << 0 ; //int. por rx
	U1IER |= (0x1) << 1 ; //int. por tx

	// 7. Interrupciones del micro

	ISER0 |= (0x1) << 6;
}

void UART1_IRQHandler (void){

	uint8_t iir, dato;

	do {
		//Para limpiar los flags de IIR hay que leerlo, una vez que lo leí se resetea.
		iir = U1IIR;
		//THRE (Interrupción por TX)
		if (iir & 0x02) {
			if(!PopTx(&dato))
				U1THR = dato;	// hay un dato en el bufferTx para enviar
			else
				UART1_txEnCurso = 0; // si no hay más datos a enviar, limpio el flag
		}
		//Data Ready (Interrupción por RX)
		if ( iir & 0x04 ) {
			PushRx((uint8_t)U1RBR);	// guardo el dato recibido en el bufferRx
		}
	} while(!(iir & 0x01));	/* me fijo si cuando entré a la ISR había otra
						    int. pendiente de atención: b0=1 (ocurre únicamente
						    si dentro del mismo espacio temporal llegan dos
						    interrupciones a la vez) */
}

void UART1_StartTx(void){
	uint8_t dato;

	if(!PopTx(&dato))
		U1THR = dato;	//fuerzo la transmisión del primer dato
}
