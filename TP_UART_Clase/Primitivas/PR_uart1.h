/*
 * PR_uart1.h
 *
 *  Created on: Oct 26, 2018
 *      Author: cha
 */

#ifndef PR_UART1_H_
#define PR_UART1_H_

#include "dr_uart1.h"

#define TXBUFFER_SIZE	32
#define RXBUFFER_SIZE	32

uint8_t PushTx(uint8_t dato);
uint8_t PopTx(uint8_t *dato);
uint8_t PushRx(uint8_t dato);
uint8_t PopRx(uint8_t *dato);
void EnviarString(const char *str);

#endif /* PR_UART1_H_ */
