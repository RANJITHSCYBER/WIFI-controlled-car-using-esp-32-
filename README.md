# 🚗 ESP32 Wi-Fi Controlled Car

Welcome to the official documentation for the **ESP32 Wi-Fi Controlled Car** project using the **L298N motor driver**. This page guides you through the hardware setup, software implementation, and usage instructions to build your own remote-controlled robotic car.

---

## 📦 Project Overview

This project demonstrates how to control a two-wheel drive car using an ESP32 microcontroller over Wi-Fi. The car hosts a web interface that allows users to send movement commands directly from a browser.

---

## 🔧 Hardware Components

- ESP32 Dev Board  
- L298N Motor Driver Module  
- 2x DC Motors  
- Power Supply (Li-ion battery or similar)  
- Jumper Wires  
- Robot Chassis  

---

## 🛠️ Wiring Instructions

| ESP32 Pin | L298N Pin | Description         |
|-----------|-----------|---------------------|
| D2        | IN1       | Motor A control     |
| D4        | IN2       | Motor A control     |
| D16       | IN3       | Motor B control     |
| D17       | IN4       | Motor B control     |
| VIN       | VCC       | Power supply        |
| GND       | GND       | Common ground       |

---

## 💻 Software Setup

1. Install the **ESPAsyncWebServer** and **AsyncTCP** libraries in Arduino IDE.
2. Upload the provided sketch to your ESP32.
3. Connect to the ESP32's Wi-Fi network or assign it to your local router.
4. Access the car's control panel via the IP address shown in Serial Monitor.

---

## 🌐 Web Interface

The ESP32 hosts a simple HTML page with buttons for:
- Forward
- Backward
- Left
- Right
- Stop

Each button sends an HTTP GET request to control the motors in real time.

---

## 🚀 Getting Started

```bash
git clone https://github.com/yourusername/esp32-wifi-car.git
cd esp32-wifi-car
