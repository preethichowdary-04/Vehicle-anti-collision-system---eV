# Vehicle-anti-collision-system---eV
Embedded obstacle detection and adaptive speed control system

## Overview
Vehicle Anti-Collision System (VACS) is an embedded robotics project designed to enhance safety through real-time obstacle detection and adaptive motor speed control.

The system uses an ultrasonic sensor to measure distance and dynamically regulates motor speed to reduce collision risk.

A manual override switch is included to enable or disable system operation.

---

## Key Features
- Real-time obstacle detection using ultrasonic sensor (HC-SR04)
- Automatic speed control based on obstacle distance
- PWM-based motor speed regulation
- L298N motor driver control
- Manual ON/OFF override switch for system enable/disable

---

## Hardware Used
- Ultrasonic Sensor (HC-SR04)
- Arduino Nano / ESP32
- L298N Motor Driver
- DC Motors
- Battery supply
- Manual switch (system enable/disable)

---

## Working Principle
- Sensor continuously measures distance to obstacles
- Distance values are mapped to motor PWM signals
- Vehicle automatically slows down as obstacle distance decreases
- System operation can be enabled or disabled using a manual switch

---

## Control Logic
Motor speed is controlled using a distance-to-PWM mapping function.  
When the system is disabled via switch, manual control or motor stop state is activated.

---

## Applications
- Autonomous mobile robots
- Basic driver assistance prototypes
- Embedded safety systems
- Robotics control research

---

## Author
Preethi Chowdary  
M.Sc Mechatronics & Robotics
