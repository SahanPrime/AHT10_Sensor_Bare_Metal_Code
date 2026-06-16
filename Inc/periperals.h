/*
 * periperals.h
 *
 *  Created on: Jun 5, 2026
 *      Author: Lenovo
 */

#ifndef PERIPERALS_H_
#define PERIPERALS_H_

#include <stdint.h>
/*  BASE ADDRESSES  */
#define GPIOA_BASE      0x48000000UL
#define GPIOB_BASE      0x48000400UL
#define RCC_BASE        0x40021000UL
#define I2C1_BASE       0x40005400UL
#define USART2_BASE     0x40004400UL
#define FPU_CPACR_BASE  0xE000ED88UL //This is used for float calculations.//

/* GPIOA REGISTERS  */
#define GPIOA_MODER     (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_OTYPER    (*(volatile uint32_t *)(GPIOA_BASE + 0x04))
#define GPIOA_OSPEEDR   (*(volatile uint32_t *)(GPIOA_BASE + 0x08))
#define GPIOA_PUPDR     (*(volatile uint32_t *)(GPIOA_BASE + 0x0C))
#define GPIOA_AFR0      (*(volatile uint32_t *)(GPIOA_BASE + 0x20))
#define GPIOA_AFR1      (*(volatile uint32_t *)(GPIOA_BASE + 0x24))

/* GPIOB REGISTERS  */
#define GPIOB_MODER     (*(volatile uint32_t *)(GPIOB_BASE + 0x00))
#define GPIOB_OTYPER    (*(volatile uint32_t *)(GPIOB_BASE + 0x04))
#define GPIOB_OSPEEDR   (*(volatile uint32_t *)(GPIOB_BASE + 0x08))
#define GPIOB_PUPDR     (*(volatile uint32_t *)(GPIOB_BASE + 0x0C))
#define GPIOB_AFR0      (*(volatile uint32_t *)(GPIOB_BASE + 0x20))
#define GPIOB_AFR1      (*(volatile uint32_t *)(GPIOB_BASE + 0x24))

/*RCC REGISTERS */
#define RCC_AHB2ENR     (*(volatile uint32_t *)(RCC_BASE + 0x4C))
#define RCC_APB1ENR1    (*(volatile uint32_t *)(RCC_BASE + 0x58))

/* USART2 */
#define USART2_CR1      (*(volatile uint32_t *)(USART2_BASE + 0x00))
#define USART2_CR2      (*(volatile uint32_t *)(USART2_BASE + 0x04))
#define USART2_BRR      (*(volatile uint32_t *)(USART2_BASE + 0x0C))
#define USART2_ISR      (*(volatile uint32_t *)(USART2_BASE + 0x1C))
#define USART2_TDR      (*(volatile uint32_t *)(USART2_BASE + 0x28))

/* I2C1 REGISTERS  */
#define I2C1_CR1        (*(volatile uint32_t *)(I2C1_BASE + 0x00))
#define I2C1_CR2        (*(volatile uint32_t *)(I2C1_BASE + 0x04))
#define I2C1_TIMINGR    (*(volatile uint32_t *)(I2C1_BASE + 0x10))
#define I2C1_ISR        (*(volatile uint32_t *)(I2C1_BASE + 0x18))
#define I2C1_ICR        (*(volatile uint32_t *)(I2C1_BASE + 0x1C))
#define I2C1_RXDR       (*(volatile uint32_t *)(I2C1_BASE + 0x24))
#define I2C1_TXDR       (*(volatile uint32_t *)(I2C1_BASE + 0x28))

/* FPU  */
#define FPU_CPACR       (*(volatile uint32_t *)(FPU_CPACR_BASE))

/* delays */
#define __NOP()  __asm volatile("nop")//this is extracted from internet to waste a cpu cycle.//
void delay_ms(uint32_t ms);

void clocks_init(void);

#endif /* PERIPERALS_H_ */
