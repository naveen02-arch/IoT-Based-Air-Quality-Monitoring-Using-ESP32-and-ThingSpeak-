# 🌍 IoT-Based Air Quality Monitoring System Using ESP32 and ThingSpeak

## 📖 Overview
This project measures temperature, humidity, and gas concentration (CH₄ and CO₂) in real time using ESP32, AHT20, MQ135, and MQ4 sensors.
The collected data is displayed locally on an OLED 128×64 display and transmitted every 10 seconds to the ThingSpeak Cloud for IoT data visualization and analysis.

This system also categorizes air quality levels into Good, Moderate, Unhealthy, and Hazardous to help monitor environmental safety.
---

## ⚙️ Features
- 🌡️ Real-time **Temperature & Humidity** monitoring (AHT20)
- 🧪 **Gas concentration** measurement using MQ sensor (CO₂, CH₄)
- 📊 **AQI (Air Quality Index)** calculation with safety status
- 🖥️ Live display on **OLED (SSD1306 128×64)**
- ☁️ Automatic data upload to **ThingSpeak Cloud**
- 🔋 Works offline (OLED + Serial Monitor) and online (ThingSpeak)
- 🟢 Shows air status levels:
  - `Good`
  - `Moderate`
  - `Poor`
  - `Unhealthy`
  - `Very Unhealthy`
  - `Hazardous`

---

## 🧰 Components Used

| Component | Quantity | Description |
|------------|-----------|-------------|
| **ESP32 Dev Board** | 1 | Main microcontroller with WiFi |
| **AHT20 Sensor** | 1 | Measures Temperature & Humidity |
| **MQ135 / MQ4 Sensor** | 1 each | Measures CO₂ and CH₄ gas levels |
| **SSD1306 OLED Display (128×64)** | 1 | Displays real-time data |
| **Jumper Wires** | — | For connections |
| **Breadboard / PCB** | 1 | For prototyping |


---

## 🔌 Circuit Connections (ESP32 Pin Mapping)

| Module | Pin | ESP32 Pin |
|---------|-----|-----------|
| **AHT20 (I2C)** | SDA | 21 |
|  | SCL | 22 |
| **MQ Sensor** | Analog Out | 34 |
| **OLED Display (I2C)** | SDA | 21 |
|  | SCL | 22 |
| **VCC (All Modules)** | — | 3.3V |
| **GND (All Modules)** | — | GND |

> ⚠️ Ensure all sensors operate at **3.3V** logic level for ESP32.

---

## 🧠 Working Principle
1. The **AHT20** reads temperature and humidity.
2. The **MQ sensor** measures gas concentration (CO₂ or CH₄).
3. The ESP32 calculates an **approximate AQI** using `map()` function.
4. AQI and status are shown on:
   - OLED display
   - Serial Monitor
5. Data is uploaded to **ThingSpeak** every **10 seconds** for visualization.

---

## 🌐 ThingSpeak Cloud Setup

| Field | Parameter | Description |
|--------|------------|-------------|
| Field 1 | Temperature (°C) | AHT20 sensor |
| Field 2 | Humidity (%) | AHT20 sensor |
| Field 3 | Gas Value | MQ sensor |
| Field 4 | AQI | Calculated air quality |


**ThingSpeak Channel:**  
🔗 [View Live Data on ThingSpeak](https://thingspeak.mathworks.com/channels/3142125)

---

## 🧩 Arduino Libraries Required

Install these from **Arduino IDE → Sketch → Include Library → Manage Libraries…**

| Library Name | Author |
|---------------|--------|
| Adafruit AHTX0 | Adafruit |
| Adafruit GFX Library | Adafruit |
| Adafruit SSD1306 | Adafruit |
| Wire | Arduino |
| WiFi | ESP32 |
| HTTPClient | ESP32 |

---

## 💻 Source Code

The complete ESP32 code used in this project:  
📄 [https://github.com/naveen02-arch/IoT-Based-Air-Quality-Monitoring-Using-ESP32-and-ThingSpeak-/blob/main/Air_Quality_moniter.ino)

> This code supports both **offline (OLED + Serial)** and **online (ThingSpeak)** modes.

---

## 🔋 How to Use

1. Open **Arduino IDE**
2. Select **Board:** `ESP32 Dev Module`
3. Select **Port:** (check under Tools → Port)
4. Paste the source code into a new sketch.
5. Update your WiFi credentials in the code:
   ```cpp
   const char* WIFI_NAME = "**";
   const char* WIFI_PASSWORD = "";

---
## 📈 Output Example
- Temp: 27.3 °C
- Humidity: 45.6 %
- Gas Value: 982
- AQI: 75 (Moderate)
- ✅ Data uploaded to ThingSpeak

## 📷 Images & Circuit Diagram

  
             ┌────────────────────────────┐
             │         ESP32              │
             │                            │
             │   3.3V ────────────┐       │
             │                    │       │
             │   GND ─────────────┼───────┘
             │                    │
             │  GPIO21 ───── SDA──┼──> AHT20
             │  GPIO22 ───── SCL──┼──> AHT20
             │                    │
             │  GPIO34 ───── AO───┼──> MQ135
             │                    │
             └────────────────────┘


  ![WhatsApp Image 2025-11-02 at 20 27 32_a291a628](https://github.com/user-attachments/assets/ea4ddd9e-b5ba-4c08-bde7-e6da6afcc73b)




