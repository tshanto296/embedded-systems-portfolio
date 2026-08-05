# CAN Bus Communication

## What it does
Demonstrates CAN bus communication between two STM32 nodes using
MCP2515 CAN controllers. Node 1 sends LED control commands every 2
seconds. Node 2 receives and executes them, toggling an LED on/off.

## CAN Bus concepts demonstrated
- CAN bus multi-node communication over shared 2-wire bus
- Message ID based filtering
- Sending and receiving structured CAN frames
- MCP2515 CAN controller configuration (bitrate, mode)
- SPI communication between STM32 and MCP2515

## How it works
- Sender (Node 1) broadcasts a CAN frame with ID 0x123 every 2s
- Frame contains a command byte (0x01 = ON, 0x00 = OFF)
- Receiver (Node 2) listens on the bus, filters for ID 0x123
- Executes LED command and logs to serial monitor

## Hardware
- 2x STM32F103C8 Blue Pill
- 2x MCP2515 CAN controller modules
- 1x LED
- 1x 220Ω resistor

## Wiring
| Component | Pin | STM32 Pin |
|-----------|-----|-----------|
| MCP2515 | VCC | 5V |
| MCP2515 | GND | GND |
| MCP2515 | SCK | PA5 |
| MCP2515 | SI (MOSI) | PA7 |
| MCP2515 | SO (MISO) | PA6 |
| MCP2515 | CS | PA4 |
| MCP2515 CAN_H | CAN_H | MCP2515 Node 2 CAN_H |
| MCP2515 CAN_L | CAN_L | MCP2515 Node 2 CAN_L |
| LED | Anode | PA5 (via 220Ω) |
| LED | Cathode | GND |

## How to run
1. Wire both STM32 boards with MCP2515 modules as shown
2. Connect CAN_H to CAN_H and CAN_L to CAN_L between both modules
3. Add MCP2515 library in Wokwi
4. Flash sender code to Node 1, receiver code to Node 2
5. Open serial monitors on both
6. Node 1 sends LED commands, Node 2 toggles LED accordingly
