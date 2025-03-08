#include <PubSubClient.h>
#include <ESP8266WiFi.h>

const char* ssid     = "chocolatAuLait";
const char* password = "tomate59";

const char* mqtt_server    = "192.168.31.106";
const int   mqtt_port      = 1883;
const char* mqtt_client_id = "ESP8266_D1_Mini";
const char* mqtt_user      = "";
const char* mqtt_pass      = "";

const char* temperature_topic = "temperature";
const char* humidity_topic    = "humidity";

WiFiClient espClient;
PubSubClient client(espClient);

float currentHumidity    = 0.0;
float currentTemperature = 0.0;

bool newHumidity    = false;
bool newTemperature = false;

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("[MQTT] Message recu sur le topic: ");
  Serial.print(topic);
  Serial.print(" | Message : ");

  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);

  if (String(topic) == temperature_topic) {
    currentTemperature = message.toFloat();
    newTemperature = true;
  } else if (String(topic) == humidity_topic) {
    currentHumidity = message.toFloat();
    newHumidity = true;
  }

  if (newTemperature && newHumidity) {
    String json = String("{\"temperature\":") + currentTemperature + ",\"humidity\":" + currentHumidity + "}";
    Serial.println(json);
    newTemperature = false;
    newHumidity = false;
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("[MQTT] Tentative de connexion... ");
    if (client.connect(mqtt_client_id, mqtt_user, mqtt_pass)) {
      Serial.println("Connecte !");
      client.subscribe(temperature_topic);
      client.subscribe(humidity_topic);
    } else {
      Serial.print("Echec, code=");
      Serial.print(client.state());
      Serial.println(" Nouvelle tentative dans 5 secondes...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  delay(1000);

  Serial.println();
  Serial.println("Connexion au Wi-Fi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Connexion etablie !");
  Serial.print("Adresse IP : ");
  Serial.println(WiFi.localIP());
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}