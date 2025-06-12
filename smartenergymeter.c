#include <PZEM004Tv30.h>
#include <WiFi.h>
#include <PubSubClient.h>

// PZEM sensor configuration
#define PZEM_RX_PIN 5
#define PZEM_TX_PIN 18
#define PZEM_SERIAL Serial2

PZEM004Tv30 pzem(PZEM_SERIAL, PZEM_RX_PIN, PZEM_TX_PIN, 0x03);  // Initialize PZEM with address 0x03

// WiFi credentials
const char* ssid = "Rahul";
const char* password = "asdfghjkl";

// ThingsBoard MQTT credentials
const char* mqtt_server = "demo.thingsboard.io";
const char* accessToken = "FNp0aZFsxISmMpy22FjK";
WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setup() {
    Serial.begin(115200);

    // Connect to WiFi
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println(" connected");

    // Setup MQTT client
    client.setServer(mqtt_server, 1883);
    connectToThingsBoard();
}

void loop() {
    if (!client.connected()) {
        connectToThingsBoard();
    }
    client.loop();  // Ensure MQTT client is processing incoming messages

    // Read data from PZEM sensor
    float voltage = pzem.voltage();
    float current = pzem.current();
    float power = pzem.power();
    float energy = pzem.energy();
    float frequency = pzem.frequency();
    float pf = pzem.pf();

    // Check if the data is valid and send to ThingsBoard
    if (!isnan(voltage) && !isnan(current) && !isnan(power) && !isnan(energy) && !isnan(frequency) && !isnan(pf)) {
        Serial.println("PZEM Sensor Data:");
        Serial.print("Voltage: "); Serial.println(voltage);
        Serial.print("Current: "); Serial.println(current);
        Serial.print("Power: "); Serial.println(power);
        Serial.print("Energy: "); Serial.println(energy);
        Serial.print("Frequency: "); Serial.println(frequency);
        Serial.print("PF: "); Serial.println(pf);
        
        // Publish data to ThingsBoard
        publishToThingsBoard(voltage, current, power, energy, frequency, pf);
    } else {
        Serial.println("Error reading sensor data");
    }

    delay(2000);
}

void connectToThingsBoard() {
    while (!client.connected()) {
        Serial.print("Connecting to ThingsBoard...");
        if (client.connect("ESP32_Client", accessToken, NULL)) {
            Serial.println("connected");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void publishToThingsBoard(float voltage, float current, float power, float energy, float frequency, float pf) {
    // Create JSON payload
    String payload = "{";
    payload += "\"voltage\":" + String(voltage) + ",";
    payload += "\"current\":" + String(current) + ",";
    payload += "\"power\":" + String(power) + ",";
    payload += "\"energy\":" + String(energy) + ",";
    payload += "\"frequency\":" + String(frequency) + ",";
    payload += "\"pf\":" + String(pf);
    payload += "}";

    // Publish to ThingsBoard telemetry topic
    client.publish("v1/devices/me/telemetry", payload.c_str());
}