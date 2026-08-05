#include <Arduino.h>
#include <SPI.h>
#include <mcp2515.h>

MCP2515 CAN_BUS(PA4);

struct can_frame RX_MSG;

#define LED PA5

void setup() {
  Serial.begin(9600);
  SPI.begin();
  pinMode(LED, OUTPUT);

  CAN_BUS.reset();
  CAN_BUS.setBitrate(CAN_500KBPS, MCP_8MHZ);
  CAN_BUS.setNormalMode();

  Serial.println("CAN Receiver Ready");
}

void loop() {
  if (CAN_BUS.readMessage(&RX_MSG) == MCP2515::ERROR_OK) {
    if (RX_MSG.can_id == 0x123) {
      if (RX_MSG.data[0] == 0x01) {
        digitalWrite(LED, HIGH);
        Serial.println("[RECEIVED] LED ON");
      } else {
        digitalWrite(LED, LOW);
        Serial.println("[RECEIVED] LED OFF");
      }
    }
  }
}
