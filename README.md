
# IoT-Based Heart Rate Monitoring System

## 📌 Project Overview
This project demonstrates a simple **IoT-based Heart Rate Monitoring System** using **Arduino Uno**, a **Pulse Sensor**, and an **I2C LCD** for real-time BPM display.
The system measures the heartbeat in **Beats Per Minute (BPM)** and displays it on both the **LCD screen** and the **Serial Monitor/Serial Plotter** for real-time visualization.

---

## 📷 Features
- Real-time heart rate measurement using a Pulse Sensor
- BPM display on **16x2 LCD with I2C interface**
- Live monitoring via **Serial Monitor & Serial Plotter**
- Low wiring complexity with **I2C communication**
- Easy to build, cost-effective, and beginner-friendly

---

## 🔧 Components Used
| Component         | Purpose                                                    |
|-------------------|------------------------------------------------------------|
| Arduino Uno        | Main microcontroller for data processing                   |
| Pulse Sensor       | Detects heartbeat signals                                  |
| I2C LCD (16x2)     | Displays BPM values with minimal wiring                     |
| USB Cable          | Provides power supply from the laptop to Arduino board      |
| Jumper Wires       | Used for electrical connections between components         |

---

## 🔌 Circuit Connections
| Component       | Arduino Pins        | Purpose                                           |
|-----------------|---------------------|--------------------------------------------------|
| Pulse Sensor     | A0, 5V, GND         | A0 → Signal Input, 5V → Power, GND → Ground        |
| I2C LCD (16x2)   | A4 (SDA), A5 (SCL)  | SDA → Data Line, SCL → Clock Line, 5V → Power, GND → Ground |

---

## 🖥️ Working Principle
1. The **Pulse Sensor** detects heartbeat signals and sends analog data to Arduino.
2. Arduino processes the data to calculate **Beats Per Minute (BPM)**.
3. The calculated BPM is displayed on both **LCD** and **Serial Monitor/Serial Plotter**.
4. Real-time monitoring helps visualize heartbeat patterns effectively.

---


---

## 🚀 How to Run the Project
1. Install **Arduino IDE**
2. Add required libraries:
   - `LiquidCrystal_I2C` (by Frank de Brabander)
   - `Wire.h` (built-in)
3. Connect components as per the **circuit diagram**.
4. Upload the code to Arduino Uno.
5. Open **Serial Monitor** or **Serial Plotter** to see BPM readings.

---

## 📊 Results
- Real-time BPM displayed on **16x2 LCD**.
- Live visualization using **Serial Monitor** and **Serial Plotter**.

---

## 🏗️ Future Scope
- **Bluetooth/Wi-Fi Integration** for remote monitoring
- **Mobile App & Cloud Storage** for long-term analysis
- **Additional sensors** like SpO2, ECG for complete health monitoring
- **AI/ML Integration** for health risk prediction

---

## 👥 Team Members
- **Nensi Chavda** – Coding & Implementation
- **Darshita Bhatt** – Circuit Connections & Hardware Setup
