# DoorStatusDetector
## ESP32 + HC-SR04 which detectes whether the door is open or closed

### Pre-req
- ESP32 or Arduino
- At least 2 PWM pins
- 5vdc Power Supply
- HC-SR04 Ultrasonic Sensor
- Door
- Coffee

### Connection
=================
|ESP32   | HC-SR04|
=================
|GPIO0 | Trig|
--------------
|GPIO2 | Echo|
--------------
|Gnd   | Gnd|
-------------
|5VDC  | VCC|
--------------

### Features
- Noise reduction using last 3 distance readings
- Scalable to accomodate last 10 distance readings within few changes
