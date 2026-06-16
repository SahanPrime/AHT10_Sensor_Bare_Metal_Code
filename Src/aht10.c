/*
 * aht10.c
 *
 *  Created on: Jun 5, 2026
 *      Author: Lenovo
 */

#include "periperals.h"
#include "i2c.h"
#include "uart.h"
#include "aht10.h"

void aht10_init(void) {
    delay_ms(100);

    /* Soft reset */
    i2c_start(AHT10_ADDR, 1, 0);
    i2c_write_byte(AHT10_SOFT_RST);
    i2c_wait_stop();
    delay_ms(30);

    /* Calibrate send init command with parameters */
    i2c_start(AHT10_ADDR, 3, 0);
    i2c_write_byte(AHT10_INIT_CMD);
    i2c_write_byte(0x08);
    i2c_write_byte(0x00);
    i2c_wait_stop();
    delay_ms(20);
}

int aht10_read(float *temperature, float *humidity) {
    uint8_t buf[6];


    /* Trigger measurement */
    i2c_start(AHT10_ADDR, 3, 0);


    if (i2c_write_byte(AHT10_TRIG_CMD) != 0) {
        uart_send_string("trig fail\r\n");
        return -1;
    }


    if (i2c_write_byte(0x33) != 0) {
        uart_send_string("0x33 fail\r\n");
        return -1;
    }

    if (i2c_write_byte(0x00) != 0) {
        uart_send_string("0x00 fail\r\n");
        return -1;
    }

    i2c_wait_stop();

    delay_ms(100);


    /* Read 6 bytes */
    i2c_start(AHT10_ADDR, 6, 1);


    for (int i = 0; i < 6; i++) {
        if (i2c_read_byte(&buf[i]) != 0) {
            uart_send_string("read fail\r\n");
            return -1;
        }
    }

    i2c_wait_stop();


    /* Check busy bit (bit7 of status byte) */
    if (buf[0] & 0x80) {
        uart_send_string("busy\r\n");
        return -2;
    }


    /* Extract raw humidity (20-bit) */
    uint32_t raw_hum  = ((uint32_t)buf[1] << 12)
                      | ((uint32_t)buf[2] <<  4)
                      | ((uint32_t)buf[3] >>  4);

    /* Extract raw temperature (20-bit) */
    uint32_t raw_temp = (((uint32_t)buf[3] & 0x0F) << 16)
                      |  ((uint32_t)buf[4] <<  8)
                      |   (uint32_t)buf[5];


    /* Convert to physical values */
    *humidity    = (raw_hum  / 1048576.0f) * 100.0f;
    *temperature = ((raw_temp / 1048576.0f) * 200.0f) - 50.0f;


    return 0;
}

