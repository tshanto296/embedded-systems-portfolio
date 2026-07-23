# Temperature Monitor

## What it does
Reads temperature and humidity from a DHT22 sensor every 2 seconds 
and prints readings over UART to serial monitor. Triggers an LED 
alert when temperature exceeds 30°C.

## Concepts demonstrated
- Sensor interfacing (DHT22)
- UART serial communication for debug output
- Float data types for decimal sensor readings
- Threshold based alert system
- Error handling for sensor failures

## Hardware
- Arduino Uno
- DHT22 temperature and humidity sensor
- 1x LED
- 1x 220Ω resistor

## How to run
1. Wire circuit as shown
2. Upload code to Arduino
3. Open serial monitor at 9600 baud
4. Adjust DHT22 temperature above 30°C to trigger alert
