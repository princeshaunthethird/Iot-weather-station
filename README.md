# 🌦️ XIAO ESP32-C6 Weather Station

<div align="center">

![Project Status](https://img.shields.io/badge/Status-Complete-success)
![Arduino](https://img.shields.io/badge/Arduino-Compatible-00979D?logo=arduino)
![ESP32](https://img.shields.io/badge/ESP32-C6-red?logo=espressif)

**A compact, IoT-enabled environmental monitoring station with real-time cloud connectivity**

[Features](#features) • [Hardware](#hardware-requirements) • [Setup](#installation--setup) • [Usage](#usage) • [Documentation](#documentation)

</div>

---

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Circuit Diagram](#circuit-diagram)
- [Installation & Setup](#installation--setup)
- [Configuration](#configuration)
- [Usage](#usage)
- [Blynk Dashboard](#blynk-dashboard-setup)

---

## 🎯 Overview

This project is a **portable, battery-powered weather monitoring station** built using the Seeed Studio XIAO ESP32-C6 microcontroller. It measures temperature, humidity, and battery voltage in real-time, displaying data locally on an OLED screen while simultaneously uploading to the Blynk IoT cloud platform for remote monitoring and historical analysis.

### Why This Project?

- ✅ **Ultra-compact design** (21mm × 17.5mm board)
- ✅ **Wi-Fi 6 support** for reliable connectivity
- ✅ **Low power consumption** with battery operation
- ✅ **Real-time cloud monitoring** via Blynk mobile app
- ✅ **Beginner-friendly** with detailed documentation

---

## ✨ Features

### Hardware Features
- **Temperature & Humidity Sensing** - DHT11 sensor with ±2°C and ±5% RH accuracy
- **Local OLED Display** - 128×64 pixel display for immediate visual feedback
- **Battery Monitoring** - Real-time voltage measurement and charge estimation
- **Compact Enclosure** - Portable box design (10cm × 8cm × 5cm)

### Software Features
- **Cloud Integration** - Real-time data sync with Blynk IoT platform
- **Mobile Dashboard** - iOS/Android app with gauges and historical charts
- **Power Efficiency** - Optimized code for extended battery life (~25-66 hours)
- **Error Resilience** - Fallback values and connection recovery mechanisms

---

## 🛠️ Hardware Requirements

| Component | Specification | Quantity | Approx. Cost |
|-----------|--------------|----------|--------------|
| **Seeed XIAO ESP32-C6** | RISC-V, Wi-Fi 6, 21×17.5mm | 1 | 4000Rs |
| **DHT11 Sensor** | Temperature & Humidity | 1 | 100Rs |
| **SSD1306 OLED Display** | 128×64, I²C interface | 1 | 300Rs |
| **Li-ion Battery** | 3.7V, 1000-2000mAh | 1 | 120Rs |
| **Breadboard/PCB** | For prototyping/final assembly | 1 | 50-80Rs |
| **Jumper Wires** | Male-to-female | 10+ | 150Rs |
| **Enclosure** | 10×8×5cm plastic box | 1 | 30-50Rs |

**Total Estimated Cost:** 
---

## 📐 Circuit Diagram

### Pin Connections

| Component | Pin | XIAO ESP32-C6 Pin | Function |
|-----------|-----|-------------------|----------|
| **DHT11** | VCC | 3.3V | Power supply |
| | DATA | D2 (GPIO2) | Data signal |
| | GND | GND | Ground |
| **OLED** | VCC | 3.3V | Power supply |
| | GND | GND | Ground |
| | SDA | D4 (GPIO22) | I²C Data |
| | SCL | D5 (GPIO23) | I²C Clock |
| **Battery** | + | BAT | Positive terminal |
| | - | GND | Negative terminal |

### Schematic

```
                    XIAO ESP32-C6
                   ┌──────────────┐
    DHT11          │              │
    ┌────┐         │              │         OLED Display
    │VCC ├─────────┤ 3.3V         │         ┌──────────┐
    │    │         │              │    ┌────┤ VCC      │
    │DATA├─────────┤ D2 (GPIO2)   │    │    │          │
    │    │         │              │    │ ┌──┤ GND      │
    │GND ├─────────┤ GND          │    │ │  │          │
    └────┘         │              │    │ │ ┌┤ SDA      │
                   │              │    │ │ ││          │
    Battery        │              │    │ │ │└┤ SCL     │
    ┌────┐         │              │    │ │ │ └──────────┘
    │ +  ├─────────┤ BAT          │    │ │ │
    │    │         │              │────┘ │ │
    │ -  ├─────────┤ GND          │──────┘ │
    └────┘         │              │────────┘
                   │ D4 (GPIO22)  │
                   │ D5 (GPIO23)  │
                   │              │
                   ┤ A0 (GPIO0)   │
                   │              │
                   └──────────────┘
    
```

### Voltage Divider Circuit

The battery voltage (3.0V - 4.2V) exceeds the ADC safe range, so we use a voltage divider:

```
V_out = V_battery × (R2 / (R1 + R2))
V_out = 4.2V × (100kΩ / 200kΩ) = 2.1V ✓ (Safe for 3.3V ADC)
```

---

## 💻 Installation & Setup

### 1. Install Arduino IDE

Download and install [Arduino IDE 2.0+](https://www.arduino.cc/en/software)

### 2. Add ESP32 Board Support

1. Open Arduino IDE
2. Go to **File → Preferences**
3. Add to "Additional Board Manager URLs":
   ```
   https://espressif.github.io/arduino-esp32/package_esp32_index.json
   ```
4. Go to **Tools → Board → Boards Manager**
5. Search for "esp32" and install **"esp32 by Espressif Systems"**
6. Select board: **Tools → Board → ESP32 Arduino → XIAO_ESP32C6**

### 3. Install Required Libraries

Open **Sketch → Include Library → Manage Libraries** and install:

- **Adafruit SSD1306** (v2.5.0+)
- **Adafruit GFX Library** (v1.11.0+)
- **DHT sensor library** by Adafruit (v1.4.0+)
- **Blynk** (v1.3.0+)

### 4. Clone This Repository

```bash
git clone https://github.com/yourusername/xiao-esp32c6-weather-station.git
cd xiao-esp32c6-weather-station
```

### 5. Open the Code

Open `src/XIAO_Weather_Station.ino` in Arduino IDE

---

## ⚙️ Configuration

### Update Wi-Fi Credentials

In the Arduino sketch, modify these lines:

```cpp
char ssid[] = "Your_WiFi_SSID";     // Replace with your Wi-Fi name
char pass[] = "Your_WiFi_Password"; // Replace with your Wi-Fi password
```

### Update Blynk Authentication

1. Create a Blynk account at [blynk.cloud](https://blynk.cloud)
2. Create a new template (see [Blynk Dashboard Setup](#blynk-dashboard-setup))
3. Copy your Auth Token and update:

```cpp
#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "XIAO Weather Station"
#define BLYNK_AUTH_TOKEN "YourAuthToken"
```

---

## 🚀 Usage

### Upload Code

1. Connect XIAO ESP32-C6 to your computer via USB-C
2. Select the correct port: **Tools → Port**
3. Click **Upload** button (→)
4. Wait for "Done uploading" message

### Monitor Serial Output

Open **Tools → Serial Monitor** (set to 115200 baud) to see:

```
Temp: 24.5 C | Hum: 58.0 % | Batt: 3.87 V
Temp: 24.6 C | Hum: 57.0 % | Batt: 3.86 V
```

### View on OLED Display

The OLED will show:
```
XIAO Weather Station
Temp: 24.5 C
Hum : 58.0 %
Batt: 3.87 V
```

### Access Blynk Dashboard

1. Download Blynk app ([iOS](https://apps.apple.com/us/app/blynk-iot/id1559317868) | [Android](https://play.google.com/store/apps/details?id=cloud.blynk))
2. Login with your account
3. Open your Weather Station device
4. View real-time data and historical charts

---

## 📱 Blynk Dashboard Setup

### Create Template

1. Login to [Blynk Console](https://blynk.cloud)
2. Click **"+ New Template"**
3. Configure:
   - **Name**: Weather Station
   - **Hardware**: ESP32
   - **Connection**: WiFi

### Configure Datastreams

Create three virtual pins:

| Virtual Pin | Name | Data Type | Units | Min/Max | Decimals |
|-------------|------|-----------|-------|---------|----------|
| V0 | Temperature | Double | °C | 0/50 | 1 |
| V1 | Humidity | Integer | % | 0/100 | 0 |
| V2 | Battery Voltage | Double | V | 3.0/4.2 | 2 |

### Add Widgets

**Web/Mobile Dashboard: It is sometimes different for web and phone so use a super chart and if u see there is no data comming change the graph timeline to live in the preview section**
1. **Gauge Widget** → Datastream V0 (Temperature) → Orange-red gradient
2. **Gauge Widget** → Datastream V1 (Humidity) → Blue gradient
3. **Value Display** → Datastream V2 (Battery Voltage)
4. **Chart Widget** → Datastream V0 → 24-hour history
5. **Chart Widget** → Datastream V1 → 24-hour history

---


## 🔋 Power Consumption

### Current Draw

| Mode | Current (mA) | Notes |
|------|--------------|-------|
| Active (Wi-Fi TX) | 100-115 | Data transmission |
| Idle (Wi-Fi connected) | 25-40 | Between updates |
| Deep Sleep | 10-15 | Not implemented |

### Battery Life Estimates

**With 1000mAh Battery:**
- 2-second updates: ~25 hours
- 10-second updates: ~30 hours
- 30-second updates: ~40 hours

**With 2000mAh Battery:**
- 2-second updates: ~50 hours
- 10-second updates: ~66 hours
- 30-second updates: ~85 hours

### Optimization Tips

1. Increase `updateInterval` to 10000ms (10 seconds)
2. Reduce OLED brightness: `display.dim(true)`
3. Implement deep sleep between readings
4. Use larger battery (3000mAh+)

---

## 🤝 Contributing

Contributions are welcome! Please follow these steps:

### Ideas for Contributions

- [ ] Add BME280 sensor support (pressure + better accuracy)
- [ ] Implement deep sleep mode
- [ ] Create 3D-printable enclosure designs
- [ ] Add data logging to SD card
- [ ] Implement OTA (Over-The-Air) updates
- [ ] Add weather forecast API integration
- [ ] Create PCB design for permanent installation

---

📊 Project Stats




---

## 🙏 Acknowledgments

- **Seeed Studio** for the excellent XIAO ESP32-C6 board
- **Adafruit** for comprehensive sensor libraries
- **Blynk** for user-friendly IoT platform
- **ESP32 Community** for extensive documentation

---

## 📚 Documentation

- [Technical Report](Technical_Report.docx) - Detailed project documentation
- [Arduino Code](src/XIAO_Weather_Station.ino) - Complete source code

---

<div align="center">

**Made with ❤️ by [Shaun dias]**

⭐ Star this repo if you find it helpful!

</div>
