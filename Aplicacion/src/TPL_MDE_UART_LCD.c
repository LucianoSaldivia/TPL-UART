/*
 * AP_PruebaUART.c
 *
 *  Created on: 25 sep. 2018
 *      Author: lsldv
 */

#include <bibliotecaInfoII.h>
#include "AP_PruebaUART.h"
#include <string.h>

char Trama[100];
static volatile uint8_t Estado;
static volatile uint8_t FLAG_TIMEOUT = 0;

void timer2Handler(void){
        FLAG_TIMEOUT = 1
}

void MDE_UART_LCD ( void )
{
	int16_t dato;
        static uint8_t Index = 0;
        char *Nombre, *Apellido;



        if( FLAG_TIMEOUT == 1 ){
            Index = 0;
            Estado = HEADER;
        }

        dato = UART1_PopRX();

	if ( dato != -1 ){
		switch ( Estado ){
			case HEADER:
				if ( dato == '#' )
					Estado = COMANDO;
				break;

                        case RECIBIENDO:
                                if ( ( dato >= 'a' && dato <= 'z' )  ||
                                     ( dato >= 'A' && dato <= 'Z' )  ||
                                     ( dato == ' ' ) ){
                                    Trama[ Index ] = dato;
                                    Index ++;
                                    TimerStart( 2, 5, timer2Handler, DEC );
                                }
                                else if( dato == '$' ){
                                    Trama[ Index ] = '\0';

                                    Apellido = strtok( Trama, " " );
                                    Nombre = strtok( NULL, " " );
                                    LCD_Display( "               ", DSP0, 0);
                                    LCD_Display( "               ", DSP1, 0);
                                    LCD_Display( Apellido, DSP0, 0 );
                                    LCD_Display( Nombre, DSP1, 0 );

                                    Index = 0;
                                    Estado = HEADER;
                                }
                                else{
                                    Index = 0;
                                    Estado = HEADER;
                                }

                                break;
                        default:
				Estado = HEADER;
				break;
		}
	}
}
