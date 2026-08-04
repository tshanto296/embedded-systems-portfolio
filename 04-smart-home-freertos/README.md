# Smart Home Automation with FreeRTOS

## What it does
A FreeRTOS-based smart home system running 4 concurrent tasks on STM32:
temperature monitoring, light control, UART logging, and critical alerts
with buzzer and LED.

## FreeRTOS concepts demonstrated
- Task creation and scheduling with priorities
- Queue-based inter-task communication
- Non-blocking delays with vTaskDelay
- Multiple concurrent tasks running independently

## How it works
- Temperature task (priority 3) reads DHT22 every 2s and sends to queue
- Light control task (priority 2) turns LED on above 30°C
- Alert task (priority 2) triggers buzzer and LED above 35°C
- UART task (priority 1) logs all readings and status to serial monitor

## Hardware
- STM32F103C8 Blue Pill
- DHT22 temperature sensor
- 2x LEDs (light control + alert)
- Buzzer
- 2x 220Ω resistors

## Wiring
| Component | Pin | STM32 Pin |
|-----------|-----|-----------|
| DHT22 | VCC | 5V |
| DHT22 | GND | GND |
| DHT22 | DATA | PA1 |
| LED (light) | Anode | PA5 (via 220Ω) |
| LED (alert) | Anode | PA6 (via 220Ω) |
| Buzzer | Positive | PA7 |

## How to run
1. Wire circuit as shown
2. Add STM32duino FreeRTOS library
3. Upload code
4. Open serial monitor at 9600 baud
5. Adjust DHT22 above 30°C for light control, above 35°C for alert
