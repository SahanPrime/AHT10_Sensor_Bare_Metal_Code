# AHT10 Sensor Bare-Metal Firmware for STM32L476

A bare-metal firmware project for the STM32L476 microcontroller that reads temperature and humidity from an AHT10 sensor using direct register-level I2C communication.

This project intentionally avoids the STM32 HAL and middleware layers. Instead, it configures the GPIO, clock tree, USART, and I2C peripherals by writing to the device registers directly using volatile pointer dereferencing.

## Overview

The firmware:

- initializes the STM32L476 clock system
- configures GPIO pins for UART and I2C
- initializes the I2C1 peripheral in standard mode
- performs AHT10 sensor initialization and soft reset
- triggers a measurement on the AHT10
- reads the 6-byte payload from the sensor
- converts the raw digital data into temperature and humidity values
- prints the results over UART for debugging and monitoring

## Project Demonstration Video

For a detailed walkthrough and demonstration of this project in action, see:
[Project Demonstration Video](https://drive.google.com/drive/folders/1aAJXdSrueDNbWBwonolHRsIhUjoRk1Im?dmr=1&ec=wgc-drive-%5Bmodule%5D-goto)

## Hardware

- MCU: STM32L476RGTx
- Sensor: AHT10 temperature and humidity sensor
- I2C bus: I2C1
- I2C pins:
  - PB8 = SCL
  - PB9 = SDA
- UART debug interface:
  - PA2 = TX
  - PA3 = RX
- Baud rate: configured for UART debug output on USART2

## Features

- direct register-level I2C driver implementation
- no HAL, no CMSIS peripheral driver abstraction for the sensor path
- UART debug output for status and sensor readings
- reusable modular architecture with separate files for I2C, UART, and AHT10 logic
- include file and source file separation for maintainability
- debug-friendly approach for learning low-level embedded systems

## Repository Structure

```text
.
├── Inc/
│   ├── aht10.h
│   ├── i2c.h
│   ├── uart.h
│   └── periperals.h
├── Src/
│   ├── aht10.c
│   ├── i2c.c
│   ├── main.c
│   ├── uart.c
│   └── system_stm32l4xx.c
├── Startup/
│   └── startup_stm32l476xx.s
├── STM32L476RGTX_FLASH.ld
├── STM32L476RGTX_RAM.ld
├── .cproject
├── .project
├── AHT10_Sensor_Reusable_Code Debug.launch
├── README.md
└── Debug/
```

## What the code does

### I2C layer
The `Src/i2c.c` file configures:

- GPIOB alternate function mode for PB8/PB9
- open-drain output mode required by I2C
- high-speed drive mode
- AF4 mapping for I2C1 on PB8/PB9
- I2C1 timing register configuration
- start condition generation
- TX/RX byte handling
- stop condition waiting logic

### AHT10 layer
The `Src/aht10.c` file handles:

- soft reset sequence
- initialization command sequence
- trigger command (`0xAC`, `0x33`, `0x00`)
- wait for measurement completion
- 6-byte read transaction
- busy flag check
- conversion of raw payload to floating-point humidity and temperature values

### Main loop
The `Src/main.c` file:

- enables the FPU
- initializes clocks and peripheral GPIO
- initializes UART for debugging
- initializes I2C1
- initializes the AHT10 sensor
- reads and prints sensor values every 2 seconds

## Example UART Output

```text
UART OK
I2C OK
AHT10 OK
Temperature 24.82 C
Humidity    46.15 %
------------------------------
Temperature 24.90 C
Humidity    46.22 %
------------------------------
```

## Build and Run

This project is intended for use with:

- STM32CubeIDE or another ARM GCC-based toolchain
- STM32L476 target board
- ST-Link debugger/programmer
- serial terminal such as PuTTY or Tera Term for UART output

Typical workflow:

1. Open the project in STM32CubeIDE.
2. Build the firmware.
3. Flash the binary to the STM32L476.
4. Connect a serial terminal to the UART debug pins.
5. Power the board and monitor the sensor readings.

## Important Notes

- The project is designed for learning and experimentation with low-level microcontroller programming.
- Register names and peripheral configuration are handled manually instead of using HAL drivers.
- Timing and clock configuration are critical; this project demonstrates practical debugging of real hardware issues such as misconfigured clocks and pin mapping problems.

## Debugging Lessons Captured in This Project

This project was developed while debugging real hardware-level issues, including:

- clock configuration errors
- UART wiring mistakes
- FPU enablement requirements for floating-point operation
- manual validation of I2C timing and sensor communication

These are common embedded development challenges and make the project useful as a practical reference for bare-metal STM32 work.

## Why Bare-Metal?

Writing firmware at the register level gives a much clearer picture of how the MCU actually works. You learn about:

- peripheral clock gating
- pin multiplexing and alternate functions
- GPIO configuration
- I2C bus timing and state transitions
- UART initialization and framing
- memory-mapped register access
- interrupt and status flag handling

This kind of understanding is especially valuable when debugging low-level hardware behavior.

## License

This repository is provided for educational and learning purposes.

## Author / Project Notes

This project was created as a learning exercise in bare-metal embedded firmware development for the STM32L476 platform using the AHT10 temperature and humidity sensor.
