🚗 ESP32 Wi-Fi Controlled Car with L298N Motor Driver
This project showcases a simple yet powerful Wi-Fi controlled robotic car built using the ESP32 microcontroller and the L298N dual H-bridge motor driver. Designed for hobbyists and learners, it demonstrates how to control a car remotely over Wi-Fi using a web interface hosted directly on the ESP32.

🔧 Features
Wi-Fi Control: Drive the car using any device with a browser—no app required!

Web Interface: Responsive control panel served from ESP32 with buttons for forward, backward, left, right, and stop.

Dual Motor Control: L298N handles two DC motors for differential steering.

Compact & Affordable: Uses minimal components and is perfect for DIY robotics.

🧰 Hardware Required
ESP32 Dev Board

L298N Motor Driver Module

2x DC Motors

Power Supply (Li-ion battery or similar)

Jumper Wires & Chassis

💻 Software Highlights
Written in Arduino/C++ using the ESPAsyncWebServer library

Real-time motor control via HTTP requests

Modular code structure for easy customization

📦 Repository Contents
/src: Arduino sketch and HTML interface

/docs: Wiring diagrams and setup instructions

/assets: Images and demo videos

🚀 Getting Started
Clone the repo and open the sketch in Arduino IDE.

Connect your ESP32 and upload the code.

Power the car and connect to its Wi-Fi hotspot or local network.

