2026-01-27
- Set up Mosquitto
- ESP32 publishing temp/humidity
- Backend receiving messages
- Added project structure files 
- Issue: reconnect drops messages

2026-03-22
- Resolved MQTT connection error (-2: TCP connection failed) by verifying broker was running and firewall allowed connections
- Fixed topic mismatch: ESP32 publishes to `sensor/#` but listener was subscribing to `sensors/#`
- Fixed JSON parsing error in MQQTListen when receiving numeric payloads (temperature/humidity)
- Updated startup.bat to use project's `mosquitto.conf` instead of system-wide config
- System now successfully receiving sensor data: temperature and humidity readings displayed
- had to add MQTT to path on my laptop. windows key R for search, sysdm.cplGo to Advanced tab Click Environment Variables Under System variables, find Path click Edit and add mosquitto
- plan to add some type of front end or continous publishin sensor data spoofing, SQL data base seems like the next crucial step 
