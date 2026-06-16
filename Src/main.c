
#include "periperals.h"
#include "uart.h"
#include "i2c.h"
#include "aht10.h"

int main(void) {
    /* Enable FPU .used internet for this part */
    FPU_CPACR |= (0xFUL << 20);
    __asm volatile("dsb");
    __asm volatile("isb");

    clocks_init();
    gpioa_init();
    usart2_init();
    uart_send_string("UART OK\r\n");

    gpiob_init();
    i2c1_init();
    uart_send_string("I2C OK\r\n");

    aht10_init();
    uart_send_string("AHT10 OK\r\n");

    float temp, hum;

    while (1) {
        int ret = aht10_read(&temp, &hum);

        if (ret == 0) {
            print_float("Temperature", temp, "C");
            print_float("Humidity   ", hum,  "%");
            uart_send_string("------------------------------\r\n");
        } else if (ret == -1) {
            uart_send_string("[ERR] I2C timeout\r\n");
        } else if (ret == -2) {
            uart_send_string("[ERR] AHT10 read failed\r\n");
        }

        delay_ms(2000);// you can change this value according to your purpose//
    }
}

