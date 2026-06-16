/*
 * i2c.c
 *
 *  Created on: Jun 5, 2026
 *      Author: Lenovo
 */

#include "periperals.h"
#include "i2c.h"

void gpiob_init(void) {
    /* PB8, PB9 into Alternate Function */
    GPIOB_MODER   &= ~(0xF0000UL);
    GPIOB_MODER   |=  (0xA0000UL);

    /* Open-drain for I2C */
    GPIOB_OTYPER  &= ~(0x300UL);
    GPIOB_OTYPER  |=  (0x300UL);

    /* High speed */
    GPIOB_OSPEEDR &= ~(0xF0000UL);
    GPIOB_OSPEEDR |=  (0xF0000UL);

    /* AF4 (I2C1) on PB8 and PB9, in AFR1 bits */
    GPIOB_AFR1    &= ~(0xFFUL);
    GPIOB_AFR1    |=  (0x44UL);
}

void i2c1_init(void) {
    /* Disable I2C before configuring */
    I2C1_CR1 &= ~(0x1UL);

    /* TIMINGR for MSI 4 MHz is 100 kHz standard mode(used internet for this value) */
    I2C1_TIMINGR = 0x00100F13UL;

    /*enable I2C */
    I2C1_CR1 |= (0x1UL);
}

void i2c_start(uint8_t addr, uint8_t nbytes, uint8_t read) {
    I2C1_CR2 = (addr & 0xFEUL)
             | ((uint32_t)nbytes << 16)
             | (read ? (1UL << 10) : 0)
             | (1UL << 25)   /* AUTOEND */
             | (1UL << 13);  /* START   */
}

int i2c_write_byte(uint8_t data) {
    uint32_t timeout = 100000;
    while (!(I2C1_ISR & (1UL << 1))) {   /* wait TXIS */
        if (I2C1_ISR & (1UL << 4)) {      /* NACKF */
            I2C1_ICR |= (1UL << 4);
            return -1;
        }
        if (--timeout == 0) return -1;
    }
    I2C1_TXDR = data;
    return 0;
}

int i2c_read_byte(uint8_t *data) {
    uint32_t timeout = 100000;
    while (!(I2C1_ISR & (1UL << 2))) {   /* wait RXNE */
        if (--timeout == 0) return -1;
    }
    *data = (uint8_t)I2C1_RXDR;
    return 0;
}

void i2c_wait_stop(void) {
    uint32_t timeout = 100000;
    /* Wait until BUSY (bit15) clears */
    while ((I2C1_ISR & (1UL << 15)) && --timeout);
}

