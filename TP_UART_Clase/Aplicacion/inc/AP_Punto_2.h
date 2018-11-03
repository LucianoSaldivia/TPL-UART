/*
 * mensaje.h
 *
 *  Created on: 5 jun. 2018
 *      Author: gabriel
 */

#ifndef AP_PRUEBA1_H_
#define AP_PRUEBA1_H_

//Relays
#define RELAY0 0
#define RELAY1 1
#define RELAY2 2
#define RELAY3 3

//Estados
#define	ESPERANDO	1
#define	NUEVA_TECLA	2

#define HEADER				0
#define RECIBIENDO_TRAMA	1

//Prototipos de funciones
void MDE_Switches_UART(void);
void MDE_UART_LCD ( void );
void MDE_Punto2(void);

void Inicializar_TP_Punto2( void );

#endif /* AP_PRUEBA1_H_ */
