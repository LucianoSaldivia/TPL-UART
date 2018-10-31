/*
 * mensaje.c
 *
 *  Created on: 29 may. 2018
 *      Author: gabriel
 */


#include <bibliotecaInfoII.h>
#include "AP_Prueba1.h"

void MDE_Switches_UART(void){
	static uint8_t Switch = 0;
	static uint8_t estado = 0;
        static char Nombre[30] = "";

	switch(estado){
		case ESPERANDO:
                        /*******/Switch = GetKey();
			if( Switch != NO_KEY ){
				estado = NUEVA_TECLA;
			}
			break;

		case NUEVA_TECLA:
			switch( Switch ){
				case SW10:
                                        strcpy( Nombre, "#" );
                                        strcpy( Nombre, "Chiama Esteban" );
                                        strcpy( Nombre, "$" );
                                        /*******/Transmitir( UART1 , Nombre , strlen(Nombre));
					break;
				case SW7:
                                        strcpy( Nombre, "#" );
                                        strcpy( Nombre, "Margulies Luciano" );
                                        strcpy( Nombre, "$" );
                                        /*******/Transmitir( UART1 , Nombre , strlen(Nombre));
                                        break;
				case SW4:
                                        strcpy( Nombre, "#" );
                                        strcpy( Nombre, "Saldivia Luciano" );
                                        strcpy( Nombre, "$" );
                                        Transmitir( UART1 , Nombre , strlen(Nombre));
                                        break;
				case SW1:
                                        strcpy( Nombre, "#" );
                                        strcpy( Nombre, "Ziccardi Ignacio" );
                                        strcpy( Nombre, "$" );
                                        /*******/Transmitir( UART1 , Nombre , strlen(Nombre));
                                        break;
				default:
					break;
			}
			estado = ESPERANDO;
			break;

		default:
			estado = ESPERANDO;
	}
}
