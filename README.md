
# ESP32 Energy Monitoring with PZEM-004T and ThingsBoard

This project uses an **ESP32 microcontroller** and a **PZEM-004T v3.0 energy meter** to monitor electrical parameters such as voltage, current, power, energy, frequency, and power factor. The data is sent to **ThingsBoard** via MQTT over Wi-Fi for remote monitoring.

---

## 🛠 Hardware Requirements

- ESP32 development board  
- PZEM-004T v3.0 energy meter  
- Wi-Fi access point  
- TTL to RS485 converter (if using PZEM RS485 version)  
- Jumper wires and power supply

---

## 🧰 Libraries Used

Install the following libraries via Arduino Library Manager:

- [`PZEM004Tv30`](https://github.com/mandulaj/PZEM-004T-v30)  
- [`PubSubClient`](https://github.com/knolleary/pubsubclient)  
- `WiFi` (comes with ESP32 board package)

---

## 📡 Pin Configuration

| Component | ESP32 Pin |
|----------|------------|
| PZEM TX  | GPIO 5     |
| PZEM RX  | GPIO 18    |
| UART Port Used | Serial2     |

---

## 🔌 WiFi & MQTT Configuration

Update the following credentials in the code:

```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* mqtt_server = "demo.thingsboard.io";  // or your own server
const char* accessToken = "YOUR_THINGSBOARD_ACCESS_TOKEN";
```

---

## 📥 Installation Guide

### 1. Set Up Arduino IDE
- Download and install [Arduino IDE](https://www.arduino.cc/en/software).
- Install the **ESP32 board package**:
  - Go to `File > Preferences` and add the following URL to "Additional Board Manager URLs":
    - `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
  - Go to `Tools > Board > Boards Manager`, search for "ESP32", and install it.

### 2. Install Required Libraries
- Go to `Sketch > Include Library > Manage Libraries`.
- Search and install the following libraries:
  - `PZEM004Tv30`
  - `PubSubClient`

### 3. Connect Your Hardware
- Wire the PZEM-004T to ESP32:
  - PZEM TX → ESP32 GPIO 5
  - PZEM RX → ESP32 GPIO 18
  - Ensure power and ground are properly connected.

### 4. Upload the Code
- Select the correct board: `ESP32 Dev Module`.
- Select the correct COM port.
- Click the **Upload** button.

### 5. Monitor the Output
- Open the Serial Monitor (`Ctrl + Shift + M`) and set the baud rate to `115200`.
- Check connection and telemetry logs.

---

## 📊 Data Sent to ThingsBoard

The following telemetry data is published every 2 seconds:

- `voltage` (Volts)
- `current` (Amps)
- `power` (Watts)
- `energy` (kWh)
- `frequency` (Hz)
- `pf` (Power Factor)

---

## ✅ Output Example (Serial Monitor)

```
PZEM Sensor Data:
Voltage: 230.5
Current: 0.65
Power: 149.3
Energy: 1.02
Frequency: 50.0
PF: 0.95
```

---

## 📌 Notes

- Ensure the PZEM device address (default is `0x03`) matches your sensor.  
- Use a suitable power supply and secure wiring for safe operation.
- ThingsBoard must have a device created with the correct `Access Token`.

---

## 📎 License

This project is open-source and free to use under the MIT License.
