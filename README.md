The goal of this project is to build a flight controller with GPS navigation based on ESP32-S3. The embedded software is designed to be as portable as possible.

Project status:
- Low-level interfaces (Done)
- Devices interfaces (In progress)
- Controllers (Pending)
- Telemetry (Pending)

Technologies used:
- Arduino Framework + ESP-IDF
- PlatformIO + (Clion IDE or VS Code)
- ESP32-S3
- Arduino libraries rewritten for portability to control devices like IMUs, barometers, receivers, etc...
- Pub/Sub system for communication between task modules

Software architecture :
![Autopilot_Architecture](https://github.com/lenny1411/Autopilot-Flight-Controller/assets/105748537/dc5f17bc-2893-4b4b-9791-34d647099f4b)
