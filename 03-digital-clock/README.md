# Digital Clock with RTC

## What it does
Displays real time clock data (time and date) on an I2C LCD screen,
with serial monitor output over UART. Uses DS1307 RTC module to keep
accurate time.

## Concepts demonstrated
- I2C communication protocol
- RTC (Real Time Clock) interfacing
- LCD display output
- UART serial debug output
- STM32 microcontroller

## Hardware
- STM32F103C8 Blue Pill
- DS1307 RTC module
- LCD1602 I2C display

## How to run
1. Wire circuit as shown
2. Upload code
3. Open serial monitor at 9600 baud
4. Time and date display on LCD and serial monitor
