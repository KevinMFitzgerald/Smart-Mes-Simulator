#include "MQTTHandler.h"

MQTTHandler::MQTTHandler(const char* ssid, const char* password, const char* mqtt_server, 
                         int mqtt_port, const char* mqtt_user, const char* mqtt_password,
                         const char* device_id)
    : client(espClient), ssid(ssid), password(password), mqtt_server(mqtt_server),
      mqtt_port(mqtt_port), mqtt_user(mqtt_user), mqtt_password(mqtt_password),
      device_id(device_id) {}

void MQTTHandler::begin() {
    // Connect to WiFi
    Serial.println();
    Serial.print("Connecting to WiFi: ");
    Serial.println(ssid);
    
    WiFi.begin(ssid, password);
    int timeout = 20;
    while (WiFi.status() != WL_CONNECTED && timeout > 0) {
        delay(500);
        Serial.print(".");
        timeout--;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println();
        Serial.print("WiFi connected. IP address: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println();
        Serial.println("WiFi connection failed!");
        delay(5000); // Wait before retrying
    }
    
    // Setup MQTT
    client.setServer(mqtt_server, mqtt_port);
}

// Try to reconnect to MQTT broker
bool MQTTHandler::reconnect() {
    // First check if WiFi is still connected
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi not connected - cannot connect to MQTT");
        return false;
    }
    
    // Create a unique client ID for this device
    String clientId = "ESP32_";
    clientId += device_id;
    
    // Try to connect to MQTT broker
    Serial.print("Attempting MQTT connection to ");
    Serial.print(mqtt_server);
    Serial.print(":");
    Serial.print(mqtt_port);
    Serial.print(" as ");
    Serial.println(clientId.c_str());
    
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password)) {
        Serial.println("MQTT connected successfully!");
        return true;
    } else {
        Serial.print("MQTT connection failed with error code: ");
        Serial.println(client.state());
        return false;
    }
}

// Keep MQTT connection alive and handle any messages
void MQTTHandler::update() {
    // Reconnect if connection is lost (with backoff to avoid spamming)
    if (!client.connected()) {
        unsigned long now = millis();
        if (now - lastReconnectAttempt > RECONNECT_INTERVAL) {
            lastReconnectAttempt = now;
            reconnect();
        }
    }
    // Process any incoming MQTT messages
    client.loop();
}

// Publish current temperature to MQTT broker
void MQTTHandler::publishTemperature(float temp) {
    if (client.connected()) {
        // Build the MQTT topic string: sensor/[device_id]/temperature
        String topic = "sensor/";
        topic += device_id;
        topic += "/temperature";
        
        // Convert temperature to string with 2 decimal places
        String payload = String(temp, 2);
        
        // Publish to MQTT broker
        client.publish(topic.c_str(), payload.c_str());
        Serial.print("Published Temperature: ");
        Serial.print(payload);
        Serial.print(" to ");
        Serial.println(topic);
    }
}

// Publish current humidity to MQTT broker
void MQTTHandler::publishHumidity(float humidity) {
    if (client.connected()) {
        // Build the MQTT topic string: sensor/[device_id]/humidity
        String topic = "sensor/";
        topic += device_id;
        topic += "/humidity";
        
        // Convert humidity to string with 2 decimal places
        String payload = String(humidity, 2);
        
        // Publish to MQTT broker
        client.publish(topic.c_str(), payload.c_str());
        Serial.print("Published Humidity: ");
        Serial.print(payload);
        Serial.print(" to ");
        Serial.println(topic);
    }
}

// Publish both temperature and humidity values
void MQTTHandler::publishSensorData(float temp, float humidity) {
    publishTemperature(temp);
    publishHumidity(humidity);
}

// Block until MQTT broker is connected, or timeout.
bool MQTTHandler::waitUntilConnected(unsigned long timeoutMs) {
    unsigned long start = millis();
    while (!client.connected() && (millis() - start) < timeoutMs) {
        if (reconnect()) {
            return true;
        }
        delay(1000);
    }
    return client.connected();
}

// Check if we are currently connected to MQTT broker
bool MQTTHandler::isConnected() {
    return client.connected();
}