#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <DHT.h>

// Pin definitions
#define DHTPIN PA1
#define LED_LIGHT PA5
#define LED_ALERT PA6
#define BUZZER PA7
#define DHTTYPE DHT22

// Temperature thresholds
#define TEMP_HIGH 30.0
#define TEMP_CRITICAL 35.0

// DHT sensor
DHT SENSOR(DHTPIN, DHTTYPE);

// Queue to pass temperature between tasks
QueueHandle_t TEMP_QUEUE;

// Task 1: Read temperature and put in queue
void TemperatureTask(void *pvParameters) {
  while(1) {
    float temp = SENSOR.readTemperature();
    
    if (!isnan(temp)) {
      xQueueSend(TEMP_QUEUE, &temp, portMAX_DELAY);
    }
    
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

// Task 2: Control light LED based on temperature
void LightControlTask(void *pvParameters) {
  float temp;
  
  while(1) {
    if (xQueuePeek(TEMP_QUEUE, &temp, portMAX_DELAY)) {
      if (temp > TEMP_HIGH) {
        digitalWrite(LED_LIGHT, HIGH);
      } else {
        digitalWrite(LED_LIGHT, LOW);
      }
    }
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

// Task 3: UART logging
void UARTTask(void *pvParameters) {
  float temp;
  
  while(1) {
    if (xQueuePeek(TEMP_QUEUE, &temp, 0)) {
      Serial.print("[SMART HOME] Temp: ");
      Serial.print(temp);
      Serial.println(" C");
      
      if (temp > TEMP_CRITICAL) {
        Serial.println("[ALERT] CRITICAL TEMPERATURE!");
      } else if (temp > TEMP_HIGH) {
        Serial.println("[WARNING] High temperature detected.");
      } else {
        Serial.println("[OK] Temperature normal.");
      }
    }
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

// Task 4: Alert task - buzzer and alert LED
void AlertTask(void *pvParameters) {
  float temp;
  
  while(1) {
    if (xQueuePeek(TEMP_QUEUE, &temp, portMAX_DELAY)) {
      if (temp > TEMP_CRITICAL) {
        digitalWrite(LED_ALERT, HIGH);
        digitalWrite(BUZZER, HIGH);
        vTaskDelay(pdMS_TO_TICKS(500));
        digitalWrite(BUZZER, LOW);
        vTaskDelay(pdMS_TO_TICKS(500));
      } else {
        digitalWrite(LED_ALERT, LOW);
        digitalWrite(BUZZER, LOW);
      }
    }
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void setup() {
  Serial.begin(9600);
  
  pinMode(LED_LIGHT, OUTPUT);
  pinMode(LED_ALERT, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
  SENSOR.begin();
  
  // Create queue - holds 5 float values
  TEMP_QUEUE = xQueueCreate(5, sizeof(float));
  
  // Create tasks with priorities
  xTaskCreate(TemperatureTask,  "TempTask",   256, NULL, 3, NULL);
  xTaskCreate(LightControlTask, "LightTask",  256, NULL, 2, NULL);
  xTaskCreate(UARTTask,         "UARTTask",   256, NULL, 1, NULL);
  xTaskCreate(AlertTask,        "AlertTask",  256, NULL, 2, NULL);
  
  // Start scheduler
  vTaskStartScheduler();
}

void loop() {
  // Empty - FreeRTOS scheduler takes over
}
