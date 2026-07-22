const int LED = 13;
const int BUTTON = 2;
volatile bool STATE = false;
void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON), ISRf, FALLING);
}

void loop() {
  digitalWrite(LED, STATE);
}

void ISRf(){
  STATE=!STATE;
}
