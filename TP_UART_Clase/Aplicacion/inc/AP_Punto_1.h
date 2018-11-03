/*
 * aplicacion.h
 *
 *  Created on: Oct 26, 2018
 *      Author: cha
 */

#ifndef AP_PUNTO_1_H_
#define AP_PUNTO_1_H_

extern volatile int flag_Enviar;

void Inicializar_TP_Punto1( char item );
void SysTick_Punto1_Handler(void);

void MDE_Punto1( void );


#endif /* AP_PUNTO_1_H_ */
