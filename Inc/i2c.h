/*
 * i2c.h
 *
 *  Created on: Jun 5, 2026
 *      Author: Lenovo
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

void gpiob_init(void);
void i2c1_init(void);
void i2c_start(uint8_t addr, uint8_t nbytes, uint8_t read);
int  i2c_write_byte(uint8_t data);
int  i2c_read_byte(uint8_t *data);
void i2c_wait_stop(void);


#endif /* I2C_H_ */
