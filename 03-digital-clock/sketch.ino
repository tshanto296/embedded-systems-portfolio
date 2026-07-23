#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

LiquidCrystal_I2C LCD(0x27, 16, 2);
RTC_DS1307 CLOCK;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  LCD.init();
  LCD.backlight();
  
  if (!CLOCK.begin()) {
    Serial.println("RTC not found!");
    while (1);
  }

  CLOCK.adjust(DateTime(2026, 7, 22, 12, 0, 0));
  
  Serial.println("Digital Clock Started");
}

void loop() {
  DateTime NOW = CLOCK.now();

  Serial.print(NOW.hour());
  Serial.print(":");
  Serial.print(NOW.minute());
  Serial.print(":");
  Serial.println(NOW.second());

  LCD.setCursor(0, 0);
  LCD.print("Time: ");
  LCD.print(NOW.hour());
  LCD.print(":");
  LCD.print(NOW.minute());
  LCD.print(":");
  LCD.print(NOW.second());

  LCD.setCursor(0, 1);
  LCD.print("Date: ");
  LCD.print(NOW.day());
  LCD.print("/");
  LCD.print(NOW.month());
  LCD.print("/");
  LCD.print(NOW.year());

  delay(1000);
}
