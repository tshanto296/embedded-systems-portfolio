# Button Controlled LED with Interrupts

## What it does
An LED that toggles on/off each time a button is pressed, 
implemented using hardware interrupts instead of polling.

## Concepts demonstrated
- GPIO configuration (input/output)
- Hardware interrupts (falling edge trigger)
- Volatile variables for ISR/main loop communication
- INPUT_PULLUP to avoid floating pins

## Hardware
- Arduino Uno
- 1x LED
- 1x Push button
- 1x 220Ω resistor

## How to run
1. Wire circuit as shown
2. Upload code to Arduino
3. Press button to toggle LED
