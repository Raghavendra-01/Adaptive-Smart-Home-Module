/*
====================================================
  Adaptive Smart Home IoT Module
  ESP32 + MQTT + HiveMQ Cloud (TLS)
====================================================
*/

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

/* ========== WiFi Credentials ========== */
// ⚠️ Replace with your actual credentials before flashing
const char* ssid     = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

/* ========== HiveMQ Cloud MQTT Broker ========== */
const char* mqtt_server = "YOUR_HIVEMQ_CLOUD_URL";   // e.g. xxxx.s1.eu.hivemq.cloud
const int   mqtt_port   = 8883;                       // TLS port
const char* mqtt_user   = "YOUR_MQTT_USERNAME";
const char* mqtt_pass   = "YOUR_MQTT_PASSWORD";

/* ========== Secure WiFi Client ========== */
WiFiClientSecure espClient;
PubSubClient     client(espClient);

/* ========== GPIO Pin Definitions ========== */
#define GPIO1 25   // Relay / Appliance 1
#define GPIO2  4   // Relay / Appliance 2
#define GPIO3  5   // Relay / Appliance 3

/* ============================================================
   MQTT Callback – fires whenever a subscribed message arrives
   ============================================================ */
void callback(char* topic, byte* payload, unsigned int length) {

  String message = "";
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("[MQTT] Topic: ");
  Serial.println(topic);
  Serial.print("[MQTT] Payload: ");
  Serial.println(message);

  bool turnOn = (message == "ON");

  if (String(topic) == "home/gpio1") {
    digitalWrite(GPIO1, turnOn ? HIGH : LOW);
    Serial.println(turnOn ? "→ Device 1 ON" : "→ Device 1 OFF");
  }
  else if (String(topic) == "home/gpio2") {
    digitalWrite(GPIO2, turnOn ? HIGH : LOW);
    Serial.println(turnOn ? "→ Device 2 ON" : "→ Device 2 OFF");
  }
  else if (String(topic) == "home/gpio3") {
    digitalWrite(GPIO3, turnOn ? HIGH : LOW);
    Serial.println(turnOn ? "→ Device 3 ON" : "→ Device 3 OFF");
  }
}

/* ============================================================
   MQTT Connection / Reconnection
   ============================================================ */
void connectMQTT() {
  while (!client.connected()) {
    Serial.print("[MQTT] Connecting...");

    if (client.connect("ESP32_SmartHome", mqtt_user, mqtt_pass)) {
      Serial.println(" Connected!");

      // Subscribe to all device control topics
      client.subscribe("home/gpio1");
      client.subscribe("home/gpio2");
      client.subscribe("home/gpio3");

      Serial.println("[MQTT] Subscribed to home/gpio1, gpio2, gpio3");
    }
    else {
      Serial.print(" Failed (rc=");
      Serial.print(client.state());
      Serial.println("). Retrying in 2s...");
      delay(2000);
    }
  }
}

/* ============================================================
   setup()
   ============================================================ */
void setup() {
  Serial.begin(115200);
  delay(500);

  // Configure GPIO outputs
  pinMode(GPIO1, OUTPUT);
  pinMode(GPIO2, OUTPUT);
  pinMode(GPIO3, OUTPUT);

  // Default state – all devices OFF
  digitalWrite(GPIO1, LOW);
  digitalWrite(GPIO2, LOW);
  digitalWrite(GPIO3, LOW);

  // ----- Connect to WiFi -----
  Serial.print("[WiFi] Connecting to ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n[WiFi] Connected!");
  Serial.print("[WiFi] IP Address: ");
  Serial.println(WiFi.localIP());

  // ----- Configure Secure Client -----
  // setInsecure() skips CA certificate validation.
  // For production, load a valid root CA certificate instead.
  espClient.setInsecure();

  // ----- Configure MQTT -----
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  connectMQTT();
}

/* ============================================================
   loop()
   ============================================================ */
void loop() {
  if (!client.connected()) {
    connectMQTT();
  }
  client.loop();
}
