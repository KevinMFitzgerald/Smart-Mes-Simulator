#include "DHTSensor.h"
#include "MQTTHandler.h"
#include "config.h"

// Create instances of our sensor and MQTT handler
DHTSensor sensor(DHT_PIN, DHT_TYPE);
MQTTHandler mqtt(WIFI_SSID, WIFI_PASSWORD, MQTT_SERVER, MQTT_PORT, MQTT_USER, MQTT_PASSWORD, DEVICE_ID);

// Track when we last read the sensor
unsigned long lastReadTime = 0;

// Setup function - runs once when ESP32 boots up
void setup() {
  Serial.begin(115200);
  delay(1000); // Give serial monitor time to connect
  
  Serial.println("\n\n========================================");
  Serial.println("  DHT11 Sensor with MQTT Publishing");
  Serial.println("========================================\n");
  
  Serial.println("Initializing DHT11 sensor...");
  sensor.begin();
  
  Serial.println("Connecting to WiFi and MQTT...");
  mqtt.begin();

  if (mqtt.waitUntilConnected(30000)) {
    Serial.println("MQTT connected. Starting sensor loop.");
  } else {
    Serial.println("MQTT connection timed out. Will retry in loop.");
  }
  
  Serial.println("\nSetup complete! Reading sensor data...\n");
}


void loop() {
  mqtt.update();
  
  if (!mqtt.isConnected()) {
    Serial.println("MQTT disconnected. Waiting to reconnect...");
    delay(2000);
    return;
  }
  
  // Read sensor data at the specified interval
  if (millis() - lastReadTime >= READ_INTERVAL) {
    // Read temperature and humidity from sensor
    float temp = sensor.readTemperature();
    float humidity = sensor.readHumidity();
    
    // Print readings to serial monitor
    Serial.printf("Temp: %.2f °C | Humidity: %.2f %%\n", temp, humidity);
    
    // Try to publish to MQTT if connected
    if (mqtt.isConnected()) {
      mqtt.publishSensorData(temp, humidity);
    } else {
      Serial.println("MQTT not connected - skipping publish");
    }
    
    // Update the time of last reading
    lastReadTime = millis();
  }
}