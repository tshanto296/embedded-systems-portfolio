#include <Arduino.h>
#include <SPI.h>
#include <mcp2515.h>

MCP2515 CAN_BUS(PA4);

struct can_frame TX_MSG;

void setup() {
  Serial.begin(9600);
  SPI.begin();

  CAN_BUS.reset();
  CAN_BUS.setBitrate(CAN_500KBPS, MCP_8MHZ);
  CAN_BUS.setNormalMode();

  Serial.println("CAN Sender Ready");
}

void loop() {
  TX_MSG.can_id  = 0x123;
  TX_MSG.can_dlc = 2;
  TX_MSG.data[0] = 0x01;  // command: turn LED on
  TX_MSG.data[1] = 0xFF;  // value: full brightness

  if (CAN_BUS.sendMessage(&TX_MSG) == MCP2515::ERROR_OK) {
    Serial.println("[SENT] LED ON command");
  }
  delay(2000);

  TX_MSG.data[0] = 0x00;  // command: turn LED off
  TX_MSG.data[1] = 0x00;

  if (CAN_BUS.sendMessage(&TX_MSG) == MCP2515::ERROR_OK) {
    Serial.println("[SENT] LED OFF command");
  }
  delay(2000);
}
