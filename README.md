# 🏠 Adaptive Smart Home IoT Module

> Cloud-Based Smart Home Automation using **ESP32** and **MQTT Protocol** (HiveMQ Cloud)

![Platform](https://img.shields.io/badge/Platform-ESP32-blue)
![Protocol](https://img.shields.io/badge/Protocol-MQTT%20TLS-green)
![Broker](https://img.shields.io/badge/Broker-HiveMQ%20Cloud-orange)
![License](https://img.shields.io/badge/License-MIT-yellow)

---

## 👥 Project Team

| Roll Number | Name | Program | Year |
|-------------|------|---------|------|
| 2300049001 | Meda Siva Sai Raghavendra Prasad | B.Tech ECE | 4th Year |
| 2300049002 | Venkata Ashok Chittibomma | B.Tech ECE | 4th Year |
| 2300049004 | Bojja Soma Sekhar Siddardha | B.Tech ECE | 4th Year |
| 2300049007 | Yenumala Pavan Manikanth | B.Tech ECE | 4th Year |

---

## 📌 Project Objective

To convert conventional home appliances into **smart IoT-enabled devices** by integrating them with a cloud platform for **real-time remote monitoring and control**.

---

## 🧠 Problem Statement

Traditional home appliances are operated manually and lack remote accessibility and monitoring features. This project bridges that gap using ESP32 + MQTT cloud technology.

---

## 🔧 Technologies Used

| Component | Purpose |
|-----------|---------|
| ESP32 | Microcontroller with WiFi |
| MQTT Protocol | Lightweight messaging |
| HiveMQ Cloud | Secure cloud broker |
| WiFiClientSecure | TLS encrypted connection |
| PubSubClient | MQTT client library |
| Relay Module | Appliance switching |

---

## 📐 System Architecture

```
📱 MQTT Client (Mobile/Web)
        │
        ▼
☁️  HiveMQ Cloud Broker (TLS - Port 8883)
        │
        ▼
📡 ESP32 (WiFi Connected)
        │
        ▼
🔌 Relay Module
        │
        ▼
💡 Home Appliance (Fan / Light / AC)
```

---

## 🛰️ MQTT Topic Structure

| Topic | Controlled Device | Payload |
|-------|------------------|---------|
| `home/gpio1` | Device 1 (e.g., Light) | `ON` / `OFF` |
| `home/gpio2` | Device 2 (e.g., Fan) | `ON` / `OFF` |
| `home/gpio3` | Device 3 (e.g., AC) | `ON` / `OFF` |

---

## 🔌 Hardware Connections

| ESP32 GPIO | Connected To |
|-----------|-------------|
| GPIO 25 | Relay 1 (Device 1) |
| GPIO 4 | Relay 2 (Device 2) |
| GPIO 5 | Relay 3 (Device 3) |

---

## 🔐 Security

- TLS Encryption on Port **8883**
- Username & Password Authentication via HiveMQ Cloud
- Credentials stored separately (never hardcoded in public repo)

---

## 🚀 Getting Started

### 1. Install Required Libraries (Arduino IDE)
- `PubSubClient` by Nick O'Leary
- `WiFiClientSecure` (built-in with ESP32 board package)

### 2. Configure Credentials
Open `src/adaptive_smart_home.ino` and replace:

```cpp
const char* ssid     = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

const char* mqtt_server = "YOUR_HIVEMQ_CLOUD_URL";
const char* mqtt_user   = "YOUR_MQTT_USERNAME";
const char* mqtt_pass   = "YOUR_MQTT_PASSWORD";
```

### 3. Flash to ESP32
- Select board: `ESP32 Dev Module`
- Upload speed: `115200`
- Flash the code

### 4. Test via MQTT Client
Use **MQTT Explorer** or **HiveMQ Web Client**:
- Connect to your broker
- Publish `ON` to `home/gpio1` → Device 1 turns ON
- Publish `OFF` to `home/gpio1` → Device 1 turns OFF

---

## 📂 Project Structure

```
Adaptive-Smart-Home-Module/
│
├── src/
│   └── adaptive_smart_home.ino   ← Main ESP32 code
│
├── docs/
│   └── architecture.md           ← System architecture details
│
├── README.md
├── LICENSE
└── .gitignore
```

---

## 🔮 Future Enhancements

- [ ] Temperature & Humidity Sensor (DHT22)
- [ ] Motion Detection (PIR Sensor)
- [ ] Energy Monitoring (PZEM-004T)
- [ ] Mobile App Dashboard (Flutter/Blynk)
- [ ] OTA Firmware Updates
- [ ] AI-based Adaptive Automation
- [ ] Voice Control Integration (Alexa/Google)

---

## 📜 License

This project is licensed under the **MIT License** – see the [LICENSE](LICENSE) file for details.

---

## 🙏 Acknowledgements

- [HiveMQ Cloud](https://www.hivemq.com/mqtt-cloud-broker/) – Free MQTT Broker
- [PubSubClient Library](https://pubsubclient.knolleary.net/)
- [Espressif ESP32 Arduino Core](https://github.com/espressif/arduino-esp32)
