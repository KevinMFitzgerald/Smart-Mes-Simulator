# MQTT Setup Guide

This project uses MQTT to publish DHT11 sensor readings from the ESP32 to a laptop running an MQTT broker.

## Prerequisites

1. **MQTT Broker** - Install Mosquitto or another MQTT broker on your laptop
2. **MQTT Client** - Install a tool to listen/subscribe to topics

## Step 1: Configure ESP32

Edit `include/config.h` and update:

```cpp
#define WIFI_SSID "YOUR_NETWORK_NAME"
#define WIFI_PASSWORD "YOUR_PASSWORD"
#define MQTT_SERVER "192.168.1.100"    // Your laptop's IP address
```

Find your PC's IP address:
- **Windows**: Open PowerShell and run `ipconfig` (look for "IPv4 Address")
- **Mac/Linux**: Open Terminal and run `ifconfig` or `hostname -I`

## Step 2: Install & Run MQTT Broker on Laptop

### Option A: Using Mosquitto (Recommended)

**Windows:**
1. Download from: https://mosquitto.org/download/
2. Install with default settings
3. Open PowerShell as Administrator and run:
   ```powershell
   cd "C:\Program Files\mosquitto"
   .\mosquitto.exe -v
   ```

**Mac:**
```bash
brew install mosquitto
mosquitto -v
```

**Linux (Ubuntu/Debian):**
```bash
sudo apt-get install mosquitto
sudo systemctl start mosquitto
```

### Option B: Using Docker

```bash
docker run -it -p 1883:1883 eclipse-mosquitto:latest
```

## Step 3: Listen to Sensor Data

You can use any of these tools:

### Option A: Mosquitto CLI (Easiest)

Open a terminal and subscribe to sensor topics:

```bash
# Listen to temperature only
mosquitto_sub -h 192.168.1.100 -p 1883 -t "sensor/dht11_sensor/temperature"

# Listen to humidity only
mosquitto_sub -h 192.168.1.100 -p 1883 -t "sensor/dht11_sensor/humidity"

# Listen to all sensor topics
mosquitto_sub -h 192.168.1.100 -p 1883 -t "sensor/dht11_sensor/#"
```

Replace `192.168.1.100` with your broker's IP address.

### Option B: MQTT Explorer (GUI)

1. Download: https://mqtt-explorer.com/
2. Configuration:
   - **Host**: Your laptop's IP (e.g., `192.168.1.100`)
   - **Port**: `1883`
   - **Username**: `mqtt_user` (or leave blank if no auth)
   - **Password**: `mqtt_pass` (or leave blank if no auth)
3. Click Connect
4. Browse the `sensor/` topic tree on the left

### Option C: Python Script

Save as `mqtt_listener.py`:

```python
import paho.mqtt.client as mqtt

def on_connect(client, userdata, flags, rc):
    print(f"Connected with result code {rc}")
    client.subscribe("sensor/dht11_sensor/#")

def on_message(client, userdata, msg):
    print(f"{msg.topic}: {msg.payload.decode()}")

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("192.168.1.100", 1883, 60)  # Update IP address
client.loop_forever()
```

Run: `python mqtt_listener.py`

## Topic Structure

The ESP32 publishes to:

```
sensor/dht11_sensor/temperature   -> Current temperature value
sensor/dht11_sensor/humidity      -> Current humidity value
```

Change the `DEVICE_ID` in `config.h` to customize topic names.

## Troubleshooting

| Problem | Solution |
|---------|----------|
| "Connection refused" | Check broker is running and IP address is correct |
| "Connection timeout" | Verify ESP32 is on same WiFi network as laptop |
| No data arriving | Check MQTT credentials and firewall settings |
| WiFi won't connect | Verify SSID and password in `config.h` |

## Security Notes

For production use, consider:
- Using TLS/SSL encryption
- Setting up MQTT authentication credentials
- Using a MQTT broker with access control
- Never hardcode passwords (use environment variables)