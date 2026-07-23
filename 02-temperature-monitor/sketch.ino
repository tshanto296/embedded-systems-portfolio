#include <DHT.h>

const int DHTPIN = 4;
const int LEDPIN = 8;
const float THRESHOLD = 30.0;

DHT DHT_SENSOR(DHTPIN, DHT22);

void setup() {
  Serial.begin(9600);
  pinMode(LEDPIN, OUTPUT);
  DHT_SENSOR.begin();
  Serial.println("Temperature Monitor Started");
}

void loop() {
  float TEMPERATURE = DHT_SENSOR.readTemperature();
  float HUMIDITY = DHT_SENSOR.readHumidity();

  if (isnan(TEMPERATURE) || isnan(HUMIDITY)) {
    Serial.println("Sensor error!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(TEMPERATURE);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(HUMIDITY);
  Serial.println(" %");

  if (TEMPERATURE > THRESHOLD) {
    digitalWrite(LEDPIN, HIGH);
    Serial.println("ALERT: Temperature too high!");
  } else {
    digitalWrite(LEDPIN, LOW);
  }

  delay(2000);
}
