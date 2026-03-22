#include "DHTSensor.h"

DHTSensor::DHTSensor(uint8_t pin, uint8_t type) : pin(pin), type(type), dht(pin, type) {}

void DHTSensor::begin() {
    dht.begin();
}

float DHTSensor::readTemperature() {
    return dht.readTemperature();
}

float DHTSensor::readHumidity() {
    return dht.readHumidity();
}

void DHTSensor::printReadings() {
    float temp = readTemperature();
    float humidity = readHumidity();
    Serial.printf("Temp: %.2f °C| Humidity: %.2f \n\r", temp, humidity);
}