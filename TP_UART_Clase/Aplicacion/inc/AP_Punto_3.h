/*
 * AP_Punto_3.h
 *
 *  Created on: Nov 1, 2018
 *      Author: cha
 */

#ifndef AP_PUNTO_3_H_
#define AP_PUNTO_3_H_

/**************/
/* CONSTANTES */
/**************/

#define ID_SLAVE	'1'

#define TIMER_1		1
#define TIMER_2		2


// Constantes para estado
#define RESET		0
#define	INACTIVO	1


// Constante para MDE UART Rx
#define ESPERANDO_TRAMA		0
#define RECIBIENDO_TRAMA	1
#define MAX_TRAMA_RX		8

#define FIN_DE_LINEA		'0x0A'
#define	RETORNO_DE_CARRO	'0x0D'


// Constantes para command
#define NO_COMMAND			0
#define GREEN_LED			1
#define	RED_LED				2




void Inicializar_TP_Punto3( void );

void MDE_Punto3( void );
void Apagar_Leds( void );
void OKs_To_Buffer( void );
void FAILs_To_Buffer( void );

void RX_Mensajes(void);
void interpretar( const char trama[] );



#endif /* AP_PUNTO_3_H_ */
