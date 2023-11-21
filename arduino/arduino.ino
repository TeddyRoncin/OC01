#include <WiFi.h>
#include <PubSubClient.h>

const char* WIFI_SSID = "Votre_SSID";
const char* WIFI_PASSWORD = "Votre_Mot_de_Passe";
const char* MQTT_SERVER = "Adresse_du_serveur_MQTT";
const int MQTT_PORT = 1883;
const char* MQTT_TOPIC = "topic/test";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);

  // Connexion au WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connexion au WiFi...");
  }
  Serial.println("Connecté au WiFi");

  // Connexion au serveur MQTT
  client.setServer(MQTT_SERVER, MQTT_PORT);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Publier un message
  String message = "Hello, MQTT!";
  client.publish(MQTT_TOPIC, message.c_str());
  delay(5000); // Attendre 5 secondes avant de publier le prochain message
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Tentative de reconnexion MQTT...");

    if (client.connect("ESP32Client")) {
      Serial.println("Connecté au serveur MQTT");
    } else {
      Serial.print("Échec, rc=");
      Serial.print(client.state());
      Serial.println(" Réessayer dans 5 secondes");
      delay(5000);
    }
  }
}