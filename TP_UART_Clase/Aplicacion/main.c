/*
===============================================================================
 Name        : TP_UART_Clase.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif


// Includes Generales
#include <cr_section_macros.h>
#include "PR_Inicializacion.h"
#include "PR_Timers.h"

// Inlcudes del Punto 1
//#include "AP_Punto_1.h"
//#include "PR_SysTick.h"

// Includes del Punto 2
#include "AP_Punto_2.h"

// Includes del Punto 3
//#include "AP_Punto_3.h"

// Prototipo de función
void Inicializar_Consigna( char Punto );


int main(void) {

	Inicializacion();
	Inicializar_Consigna('2');

    while(1) {

    	// Punto 1
//    	MDE_Punto1();

    	// Punto 2
    	TimerEvent();
    	MDE_Punto2();

//    	// Punto 3
//    	TimerEvent();
//    	MDE_Punto3();
//    	RX_Mensajes();

    }

    return 0 ;
}

void Inicializar_Consigna( char Punto ){

	switch ( Punto ){

		case 'a':
			Inicializar_TP_Punto1('a');
			break;

		case 'b':
			Inicializar_TP_Punto1('b');
			break;

		case 'c':
			Inicializar_TP_Punto1('c');

			break;

		case '2':
			Inicializar_TP_Punto2();
			break;

		case '3':
			Inicializar_TP_Punto3();
			break;
	}

}
