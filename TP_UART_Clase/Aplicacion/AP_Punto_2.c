#include "AP_Punto_2.h"

#include <string.h>
#include "PR_uart1.h"
#include "PR_Teclado.h"
#include "PR_lcd.h"
#include "PR_Timers.h"



/********************************/
/* VARIABLES GLOBALES AL MÓDULO */
/********************************/

char Trama[100];
static volatile uint8_t Estado_RX;
static volatile uint8_t FLAG_TIMEOUT = 0;


void Inicializar_TP_Punto2( void ){
	UART1_Init( '2' );
	LCD_Display("RESET, PUNTO2",LCD_RENGLON0,0);
}


void MDE_Punto2(void){
	MDE_Switches_UART();
	MDE_UART_LCD();
}

void MDE_Switches_UART(void){
	static uint8_t Switch = 0;
	static uint8_t estado = 0;
	static char Nombre[30] = "";

	switch(estado){
		case ESPERANDO:
            Switch = GetKey();
			if( Switch != NO_KEY ){
				estado = NUEVA_TECLA;
			}
			break;

		case NUEVA_TECLA:
			switch( Switch ){
				case SW_1:
                                        strcpy( Nombre, "#" );
                                        strcat( Nombre, "Chiama Esteban" );
                                        strcat( Nombre, "$" );
                                        EnviarString( Nombre );
					break;
				case SW_2:
                                        strcpy( Nombre, "#" );
                                        strcat( Nombre, "Margulies Luciano" );
                                        strcat( Nombre, "$" );
                                        EnviarString( Nombre );
                                        break;
				case SW_3:
                                        strcpy( Nombre, "#" );
                                        strcat( Nombre, "Saldivia Luciano" );
                                        strcat( Nombre, "$" );
                                        EnviarString( Nombre );
                                        break;
				case SW_4:
                                        strcpy( Nombre, "#" );
                                        strcat( Nombre, "Ziccardi Ignacio" );
                                        strcat( Nombre, "$" );
                                        EnviarString( Nombre );
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



void timer2Handler(void){
        FLAG_TIMEOUT = 1;
}

void MDE_UART_LCD ( void ){

	uint8_t dato;
	static uint8_t Index = 0;
	char *Nombre, *Apellido;

        if( FLAG_TIMEOUT == 1 ){
                Index = 0;
                Estado_RX = HEADER;
                FLAG_TIMEOUT = 0;
        }

	if ( !PopRx(&dato) ){

		switch ( Estado_RX ){

			case HEADER:
				if ( dato == '#' )
					Estado_RX = RECIBIENDO_TRAMA;
				break;

			case RECIBIENDO_TRAMA:

				Trama[ Index ] = dato;
				Index ++;
					if ( ( dato >= 'a' && dato <= 'z' ) || ( dato >= 'A' && dato <= 'Z' ) || ( dato == ' ' ) ){
						Trama[ Index ] = dato;
						Index ++;
						TimerStart( 2, 5, timer2Handler, DEC );
					}
                                        else if( dato == '$' ){
						Trama[ Index ] = '\0';

						Apellido = strtok( Trama, " " );
						Nombre = strtok( NULL, " " );
						LCD_Display( "               ", LCD_RENGLON0, 0);
						LCD_Display( "               ", LCD_RENGLON1, 0);
						LCD_Display( Apellido, LCD_RENGLON0, 0 );
						LCD_Display( Nombre, LCD_RENGLON1, 0 );

						Index = 0;
						Estado_RX = HEADER;
					}
					else{
						Index = 0;
                                                Estado_RX = HEADER;
					}
					break;

			default:
				Estado_RX = HEADER;
				break;
		}
	}
}
