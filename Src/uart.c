/*
 * uart.c
 *
 *  Created on: Jun 5, 2026
 *      Author: Lenovo
 */

#include <stdio.h>
#include "periperals.h"
#include "uart.h"

void gpioa_init(void) {
    /* PA2, PA3 into Alternate Function */
    GPIOA_MODER   &= ~(0xF0UL);
    GPIOA_MODER   |=  (0xA0UL);

    /* Push-pull output type */
    GPIOA_OTYPER  &= ~(0xCUL);

    /* High speed */
    GPIOA_OSPEEDR &= ~(0xF0UL);
    GPIOA_OSPEEDR |=  (0xF0UL);

    /* AF7 (USART2) on PA2 and PA3 */
    GPIOA_AFR0    &= ~(0xFF00UL);
    GPIOA_AFR0    |=  (0x7700UL);
}

void usart2_init(void) {
    /* BRR here 4 MHz / 115200 ≈ 35. if you want different baud rate change 115200 value into different value. */
    USART2_BRR  =  35;

    /* Enable UE (bit0), RE (bit2), TE (bit3) */
    USART2_CR1  &= ~(0xDUL);
    USART2_CR1  |=  (0xDUL);
}

void uart_send_char(char c) {
    /* Wait until TXE (bit7) is set */
    while (!(USART2_ISR & (1UL << 7)));
    USART2_TDR = (uint32_t)c;
}

void uart_send_string(const char *str) {
    while (*str) uart_send_char(*str++);
}

void print_float(const char *label, float val, const char *unit) {
    char buf[64];
    int whole = (int)val;
    int frac  = (int)((val - (float)whole) * 10);
    if (frac < 0) frac = -frac;
    snprintf(buf, sizeof(buf), "%s: %d.%d %s\r\n", label, whole, frac, unit);
    uart_send_string(buf);
}

