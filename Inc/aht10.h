/*
 * aht10.h
 *
 *  Created on: Jun 5, 2026
 *      Author: Lenovo
 */

#ifndef AHT10_H_
#define AHT10_H_

#define AHT10_ADDR      (0x38 << 1)
#define AHT10_INIT_CMD  0xE1
#define AHT10_TRIG_CMD  0xAC
#define AHT10_SOFT_RST  0xBA

void aht10_init(void);

/*
 * aht10_read()
 *   0  = success, *temperature and *humidity updated
 *  -1  = I2C timeout / NACK
 *  -2  = sensor still busy
 */
int  aht10_read(float *temperature, float *humidity);


#endif /* AHT10_H_ */
