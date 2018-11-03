/*
 * aplicacion.c
 *
 *  Created on: Oct 26, 2018
 *      Author: cha
 */

#include "AP_Punto_1.h"

#include "dr_uart1.h"
#include "Tipos.h"
#include "PR_SysTick.h"

/********************************/
/* VARIABLES GLOBALES AL MÓDULO */
/********************************/

volatile int flag_Enviar = 0;


/*************************/
/* FUNCIONES DEL PUNTO 1 */
/*************************/

void Inicializar_TP_Punto1( char item ){

	UART1_Init( item );
	setTickCallback( (void *) SysTick_Punto1_Handler );

}

void SysTick_Punto1_Handler(void){

	volatile static uint8_t cont = 0;

	cont ++;

	if ( cont == 4 ) {
		flag_Enviar = 1;
	}

	cont %= 4;
}


void MDE_Punto1( void ){

	static uint8_t dato = 0x55;

	if ( flag_Enviar == 1 ){
		PushTx(dato);
		PushTx(dato);
		flag_Enviar = 0 ;
	}

}
