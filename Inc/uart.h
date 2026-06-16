/*
 * uart.h
 *
 *  Created on: Jun 5, 2026
 *      Author: Lenovo
 */

#ifndef UART_H_
#define UART_H_


#include <stdint.h>

void gpioa_init(void);
void usart2_init(void);
void uart_send_char(char c);
void uart_send_string(const char *str);
void print_float(const char *label, float val, const char *unit);




#endif /* UART_H_ */
