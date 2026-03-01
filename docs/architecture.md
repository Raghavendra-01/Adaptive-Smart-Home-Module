# 📐 System Architecture – Adaptive Smart Home IoT Module

## Overview

The system converts traditional home appliances into cloud-controlled smart devices using ESP32 and MQTT protocol.

---

## Architecture Layers

```
┌──────────────────────────────────────────────┐
│           USER LAYER                         │
│   MQTT Client (Mobile App / Web Browser)     │
│   Publishes: ON / OFF to topic               │
└────────────────────┬─────────────────────────┘
                     │ MQTT over TLS (Port 8883)
                     ▼
┌──────────────────────────────────────────────┐
│           CLOUD LAYER                        │
│   HiveMQ Cloud MQTT Broker                   │
│   - Handles message routing                  │
│   - TLS encryption                           │
│   - Username/Password auth                   │
└────────────────────┬─────────────────────────┘
                     │ MQTT Subscribe (TLS)
                     ▼
┌──────────────────────────────────────────────┐
│           DEVICE LAYER                       │
│   ESP32 Microcontroller                      │
│   - WiFi Connection                          │
│   - MQTT Subscribe (3 topics)                │
│   - GPIO Control Logic                       │
└────────────────────┬─────────────────────────┘
                     │ GPIO HIGH / LOW
                     ▼
┌──────────────────────────────────────────────┐
│           HARDWARE LAYER                     │
│   Relay Module (3 Channel)                   │
│   → Appliance 1 (GPIO 25)                    │
│   → Appliance 2 (GPIO 4)                     │
│   → Appliance 3 (GPIO 5)                     │
└──────────────────────────────────────────────┘
```

---

## MQTT Communication Flow

1. User opens MQTT client (phone/laptop)
2. User connects to HiveMQ Cloud broker
3. User publishes `ON` to `home/gpio1`
4. HiveMQ routes message to all subscribers
5. ESP32 receives the message (subscribed to `home/gpio1`)
6. ESP32 sets GPIO 25 → HIGH
7. Relay activates → Appliance turns ON

---

## GPIO to Device Mapping

| GPIO | Pin | Device |
|------|-----|--------|
| GPIO1 | 25 | Relay Channel 1 → Appliance 1 |
| GPIO2 | 4  | Relay Channel 2 → Appliance 2 |
| GPIO3 | 5  | Relay Channel 3 → Appliance 3 |

---

## Security Details

- Protocol: MQTT over TLS (MQTTS)
- Port: 8883
- Authentication: Username + Password
- Certificate: `setInsecure()` used for development (no CA cert validation)
- Production recommendation: Use proper Root CA certificate

---

## Reconnection Logic

If MQTT disconnects (network drop), the ESP32 automatically reconnects:
- Attempts every 2 seconds
- Re-subscribes to all 3 topics after reconnection
- No manual reset required
