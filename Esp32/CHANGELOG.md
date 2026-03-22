# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec2.0.0.html).

## [Unreleased]

### Added
- DHTSensor class for object-oriented sensor management
- Separate header file (DHTSensor.h) and implementation file (DHTSensor.cpp)
- **MQTT Support:**
  - MQTTHandler class for WiFi and MQTT connectivity
  - PubSubClient library integration
  - WiFi connection management
  - Sensor data publishing to MQTT topics
  - Config file for easy WiFi and MQTT configuration
- Comprehensive MQTT setup guide with multiple listener options
- Support for publishing temperature and humidity to separate MQTT topics

### Changed
- Refactored Testdht11.cpp to use OOP approach with MQTT integration
- Fixed printf formatting for correct temperature/humidity display
- Improved code organization with separate files
- Transitioned from serial-only output to MQTT publishing
- Changed from fixed delay to interval-based sensor readings

### Fixed
- Sensor readings now display properly formatted values instead of memory addresses
- Added non-blocking MQTT connection updates in main loop