/*
 * peripherals.c
 *
 *  Created on: Jun 5, 2026
 *      Author: Lenovo
 */

#include "periperals.h"
#include <stdint.h>

void delay_ms(uint32_t ms) {
    for (uint32_t i = 0; i < ms * 4000; i++) {
        __NOP();
    }
}

void clocks_init(void) {
    /* Enable GPIOA (bit0) and GPIOB (bit1) */
    RCC_AHB2ENR  &= ~(0x3UL);
    RCC_AHB2ENR  |=  (0x3UL);

    /* Enable USART2 (bit17) and I2C1 (bit21) */
    RCC_APB1ENR1 &= ~(0x220000UL);
    RCC_APB1ENR1 |=  (0x220000UL);
}
