# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec2.0.0.html).

## [Unreleased]

### Added
- DHTSensor class for object-oriented sensor management
- Separate header file (DHTSensor.h) and implementation file (DHTSensor.cpp)
- Proper encapsulation of DHT11 sensor functionality

### Changed
- Refactored Testdht11.cpp to use OOP approach
- Fixed printf formatting for correct temperature/humidity display
- Improved code organization with separate files

### Fixed
- Sensor readings now display properly formatted values instead of memory addresses