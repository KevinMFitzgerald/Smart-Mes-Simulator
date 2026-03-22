#ifndef CONFIG_H
#define CONFIG_H

// ===== WiFi Configuration =====
#define WIFI_SSID "ItHertzWhenIP"        // Replace with your WiFi network name
#define WIFI_PASSWORD "FreeLo@ders12"  // Replace with your WiFi password

// ===== MQTT Configuration =====
#define MQTT_SERVER "192.168.1.19"  // Replace with your MQTT broker IP
#define MQTT_PORT 1883                // MQTT broker port (default: 1883)
#define MQTT_USER ""         // MQTT username (leave empty if not needed: "")
#define MQTT_PASSWORD ""     // MQTT password (leave empty if not needed: "")
#define DEVICE_ID "dht11_sensor"      // Unique device ID for topic naming

// ===== DHT Sensor Configuration =====
#define DHT_PIN 15                    // GPIO pin for DHT sensor
#define DHT_TYPE DHT11                // DHT sensor type
#define READ_INTERVAL 2000            // Interval between sensor readings (ms)

#endif