/*
 * AP_Punto_3.c
 *
 *  Created on: Nov 1, 2018
 *      Author: cha
 */


#include "AP_Punto_3.h"

#include "dr_uart1.h"

// Includes de la librería de augusto
#include "Tipos.h"
#include "PR_RGB.h"
#include "PR_Timers.h"
#include "PR_lcd.h"


/********************************/
/* VARIABLES GLOBALES AL MÓDULO */
/********************************/

static uint32_t estado = RESET;
static uint8_t command = NO_COMMAND;

volatile uint8_t OKs=0;
volatile uint8_t FAILs=0;

volatile uint8_t msg_Contadores[16];


/*************************/
/* FUNCIONES DEL PUNTO 3 */
/*************************/

void Inicializar_TP_Punto3( void ){

	UART1_Init( '3' );

	msg_Contadores[0] = 'o';
	msg_Contadores[1] = 'k';
	msg_Contadores[2] = ':';
	msg_Contadores[3] = ' ';
	msg_Contadores[4] = '0';
	msg_Contadores[5] = '0';
	msg_Contadores[6] = ' ';
	msg_Contadores[7] = 'F';
	msg_Contadores[8] = 'a';
	msg_Contadores[9] = 'i';
	msg_Contadores[10] = 'l';
	msg_Contadores[11] = ':';
	msg_Contadores[12] = ' ';
	msg_Contadores[13] = '0';
	msg_Contadores[14] = '0';
	msg_Contadores[15] = ' ';

}


void MDE_Punto3( void ){

		// MdE: medición del ADC y transmisión de datos
		switch ( estado ) {

			case RESET:
				LCD_Display("ID: 01" , LCD_RENGLON0, 0 );
				LCD_Display("RESET" , LCD_RENGLON1, 0 );
				estado = INACTIVO;
				break;

			case INACTIVO:

				// caso:
				if ( command == GREEN_LED ) {
					command = NO_COMMAND;
					OKs++;
					LedsRGB( VERDE, ON );
					TimerStart( TIMER_1, 1, Apagar_Leds, SEG );
					OKs_To_Buffer();
					LCD_Display( msg_Contadores, LCD_RENGLON1, 0);
				}

				// caso:
				if( command == RED_LED ){
					command = NO_COMMAND;
					FAILs++;
					LedsRGB( ROJO, ON );
					TimerStart( TIMER_2, 1, Apagar_Leds, SEG);
					FAILs_To_Buffer();
					LCD_Display( msg_Contadores, LCD_RENGLON1, 0);
				}
				break;

			default:
				estado = INACTIVO;
				break;
		}
}


void Apagar_Leds( void ){

	LedsRGB( VERDE , OFF );
	LedsRGB( ROJO , OFF );

}


void OKs_To_Buffer( void ) {

	uint8_t decena_OKs, unidad_OKs;

	if( OKs > 99 ){
		OKs = 0;
	}

	unidad_OKs = OKs % 10;
	decena_OKs = OKs / 10;

	msg_Contadores[4] = 48 + decena_OKs;
	msg_Contadores[5] = 48 + unidad_OKs;

}


void FAILs_To_Buffer( void ) {

	uint8_t decena_FAILs, unidad_FAILs;

	if( FAILs > 99 ){
		FAILs = 0;
	}

	unidad_FAILs = FAILs % 10;
	decena_FAILs = FAILs / 10;

	msg_Contadores[13] = 48 + decena_FAILs;
	msg_Contadores[14] = 48 + unidad_FAILs;

}


void RX_Mensajes(void) {
	uint8_t dato;
	static uint8_t index_msg_rx = 0;
	static char msg_rx[MAX_TRAMA_RX] = {0};
	static uint32_t estado_rx = ESPERANDO_TRAMA;

	// Chequeo si llegó un msje...
	if (!PopRx(&dato)) {
		// MdE: Análisis de la trama recibida
		switch (estado_rx) {

			case ESPERANDO_TRAMA:
				// Espero el caracter de inicio de la trama ('$')
				if ((char)dato == ':') {
					index_msg_rx = 0;
					estado_rx = RECIBIENDO_TRAMA;
				}
				break;

			case RECIBIENDO_TRAMA:
				// caso: no se llegó al fin de trama ('#'), recibo y almaceno.
				if ( (char)dato != FIN_DE_LINEA ) {
					msg_rx[index_msg_rx] = (char)dato;
					index_msg_rx++;
					if (index_msg_rx > MAX_TRAMA_RX-1){
						estado_rx = ESPERANDO_TRAMA;
					}
					break;
				}
				// caso: se terminó de recibir la trama (FIN DE LINEA)
				if ( (char)dato == FIN_DE_LINEA ){
					interpretar(msg_rx);
					estado_rx = ESPERANDO_TRAMA;
				}
				break;

				default:
				estado_rx = ESPERANDO_TRAMA;
				break;
		}
	}
}


void interpretar( const char trama[] ){

	// Caso: Se comunican con esta placa
	if ( ( (trama[0]) == '0' ) && ( (trama[1]) == ID_SLAVE ) && ( (trama[1]) == RETORNO_DE_CARRO ) ) {
		command = GREEN_LED;
	}

	// Caso: Se comunican con otra placa o la trama no tiene sentido
	else {
		command = RED_LED;
	}

}
