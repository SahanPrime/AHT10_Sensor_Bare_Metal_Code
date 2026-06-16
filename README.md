# AHT10_Sensor_Bare_Metal_Code
Bare metal coding Learning Task 

# AHT10 Bare-Metal I2C Driver — STM32L476

A bare-metal firmware project implementing an I2C driver for the AHT10 temperature and humidity sensor on the STM32L476 microcontroller. No HAL, no middleware, direct register-level access using volatile pointer dereferencing.

## Hardware

- **MCU:** STM32L476
- **Sensor:** AHT10 (Temperature & Humidity)
- **I2C Pins:** PB8 (SCL), PB9 (SDA)
- **UART Debug:** PA2 (TX), PA3 (RX) — USART2

## What's Implemented

- I2C peripheral initialization via direct register configuration
- AHT10 initialization, measurement trigger, and data read sequence
- UART debug output for sensor readings
- Modular multi-file architecture with handle-based abstractions (`UART_Handle`, `I2C_Handle` structs)

## Key Debugging Challenges

- **Clock misconfiguration:** STM32L476 defaults to MSI 4 MHz — BRR register value had to be corrected from an incorrect value to 417 to match the actual clock
- **UART wiring fault:** TX/RX wires were accidentally connected to the nTRST debug pin, causing no output
- **FPU HardFault:** Traced to missing `SCB_CPACR` coprocessor access enable  floating point unit was being used without being enabled

## Project Structure

```
├── Core/
│   ├── Src/
│   │   ├── main.c
│   │   ├── i2c.c
│   │   ├── uart.c
│   │   └── aht10.c
│   ├── Inc/
│   │   ├── i2c.h
│   │   ├── uart.h
│   │   └── aht10.h
```

## Why Bare-Metal?

Using the HAL abstracts away what the hardware is actually doing. Writing directly to registers forces a real understanding of the peripheral  clock enabling, pin modes, timing, flags  which is essential for debugging and optimization in resource-constrained embedded systems.

## Tools Used

- STM32CubeIDE / GCC ARM toolchain
- ST-Link debugger
- PuTTY (UART monitoring)

