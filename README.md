The goal of this project is to build a flight controller with GPS navigation based on ESP32-S3. The embedded software is designed to be as portable as possible.

## Project status:
- Low-level interfaces (Done)
- Devices interfaces (Done, note: Barometer interface is not implemented)
- Modules (In progress)
- Telemetry (In progress)

## Technologies used:
- Arduino Framework + ESP-IDF
- PlatformIO + (Clion IDE or VS Code)
- ESP32-S3
- Arduino libraries rewritten for portability to control devices like IMUs, barometers, receivers, etc...
- Pub/Sub system for communication between task modules

## Hardware:
![20240211_153857](https://github.com/lenny1411/Autopilot-Flight-Controller/assets/105748537/35af56b6-37de-48b7-aed2-a2a18e67e7e1)

Components:
- ESP32-S3
- IMU 6-Dof BMI088 Gyro+Accel
- Transmitter Flysky FS-I6X + Receiver Flysky FS-IA6B (Ibus mode)
- Holybro M8N (GNSS module + magnetometer)
- 4 or 6 ESC 30A 3s/2s + BEC 5V
- 3.3V Regulator
- 3s 8000 mAh Lipo battery XT60
## Schematic:
Coming soon.

## Monitoring and telemetry:
[Android App](https://github.com/Embedded-MUTEX-1/DroneMonitoringApp)

## First flight:
https://github.com/Embedded-MUTEX-1/Autopilot-Flight-Controller/assets/105748537/e9cec997-3c3b-4aa0-ba62-bae3b584f156

## Software architecture :
![Architecture](https://github.com/lenny1411/Autopilot-Flight-Controller/assets/105748537/7f271d01-1ac2-45c5-8e4c-3a17ef811279)

