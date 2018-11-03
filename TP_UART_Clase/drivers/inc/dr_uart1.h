/*
 * dr_uart.h
 *
 *  Created on: Oct 26, 2018
 *      Author: cha
 */

#ifndef DR_UART1_H_
#define DR_UART1_H_


/************/
/* INCLUDES */
/************/

#include "DR_pinsel.h"		// Pinsel
#include "DR_gpio.h"		// PinMODE

#include "Regs_LPC176x.h"	// Registros

#include "PR_uart1.h"		// Primitivas UART



/**************/
/* CONSTANTES */
/**************/


#define P0_15	0,15
#define P0_16	0,16


/***********************************************/
/* VARIABLES GLOBALES PARA INCLUIR EN OTROS .C */
/***********************************************/

extern volatile uint8_t UART1_txEnCurso;


/***************************/
/* PROTOTIPOS DE FUNCIONES */
/***************************/

void UART1_Init( char selector );
void UART1_StartTx(void);

#endif /* DR_UART1_H_ */
