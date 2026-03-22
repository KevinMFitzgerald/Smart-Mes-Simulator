#include "DHTSensor.h"

DHTSensor sensor(15, DHT11);

void setup() {
  Serial.begin(115200);
  sensor.begin();
}

void loop() {
  sensor.printReadings();
  delay(2000);
}