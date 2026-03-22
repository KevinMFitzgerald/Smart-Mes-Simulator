#ifndef MQTTHANDLER_H
#define MQTTHANDLER_H

#include <WiFi.h>
#include <PubSubClient.h>


// For publishing sensor data from ESP32 to MQTT broker
class MQTTHandler {
private:
    WiFiClient espClient;              // WiFi connection object
    PubSubClient client;               // MQTT client object
    
    // WiFi credentials
    const char* ssid;
    const char* password;
    
    // MQTT broker details
    const char* mqtt_server;
    int mqtt_port;
    const char* mqtt_user;
    const char* mqtt_password;
    
    // Device identifier for topic naming
    const char* device_id;
    
    // Reconnection backoff timing
    unsigned long lastReconnectAttempt = 0;
    const unsigned long RECONNECT_INTERVAL = 5000;  // Wait 5 seconds between attempts
    
    bool reconnect();
    
public:
    // Constructor - pass WiFi and MQTT credentials
    MQTTHandler(const char* ssid, const char* password, const char* mqtt_server, 
                int mqtt_port, const char* mqtt_user, const char* mqtt_password, 
                const char* device_id);
    
    void begin();
    
    // keep alive connection to the MQTT broker and process incoming messages
    void update();

    // Block until MQTT connection is established (or timeout)
    bool waitUntilConnected(unsigned long timeoutMs = 30000);
    
    // Publish temperature value to MQTT
    void publishTemperature(float temp);
    
    // Publish humidity value to MQTT
    void publishHumidity(float humidity);
    
    // Publish both temperature and humidity to MQTT
    void publishSensorData(float temp, float humidity);
    
    // Check if currently connected to MQTT broker
    bool isConnected();
};

#endif