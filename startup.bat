@echo off
setlocal enabledelayedexpansion

REM ===================================
REM Smart-Mes-Simulator Startup Script
REM ===================================

echo.
echo ========================================
echo Smart-Mes-Simulator - Project Startup
echo ========================================
echo.

cd /d "%~dp0"

REM 1) Ensure Mosquitto MQTT Broker is running
echo [1/4] Checking MQTT Broker (Mosquitto)...
set MOSQ_PATH="C:\Program Files\mosquitto\mosquitto.exe"
set MOSQ_CONF="%~dp0mosquitto.conf"

tasklist /FI "IMAGENAME eq mosquitto.exe" | find /I "mosquitto.exe" >nul
if %ERRORLEVEL% NEQ 0 (
    echo Starting Mosquitto broker...
    start "Mosquitto MQTT Broker" /MIN %MOSQ_PATH% -c %MOSQ_CONF%
    timeout /t 3 /nobreak >nul
    echo Mosquitto started successfully
) else (
    echo Mosquitto already running
)
echo.

REM 2) Build and Upload ESP32 Firmware
echo [2/4] Building and uploading ESP32 firmware...
cd /d "%~dp0Esp32"
pio run -t upload --environment freenove_esp32_s3_wroom
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ERROR: ESP32 upload failed. Check USB connection and retry.
    exit /b %ERRORLEVEL%
)
echo ESP32 firmware uploaded successfully
echo.

REM 3) Start Python Backend
echo [3/4] Starting Python Backend...
cd /d "%~dp0"
call .venv\Scripts\activate.bat
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Could not activate Python virtual environment
    exit /b %ERRORLEVEL%
)
echo Starting Backend application...
start "Smart-Mes Backend" python Backend\MQQTListen
timeout /t 2 /nobreak >nul
echo Backend started in new window
echo.

REM 4) Open Serial Monitor for ESP32
echo [4/4] Opening ESP32 Serial Monitor...
cd /d "%~dp0Esp32"
start "ESP32 Serial Monitor" pio device monitor --environment freenove_esp32_s3_wroom

echo.
echo ========================================
echo Startup Complete!
echo ========================================
echo.
echo Services running:
echo  * Mosquitto MQTT Broker (port 1883)
echo  * Python Backend (listening to MQTT)
echo  * ESP32 Serial Monitor (monitoring DHT11 data)
echo.
echo Note: Frontend (Web UI) not yet implemented
echo.
pause

endlocal
