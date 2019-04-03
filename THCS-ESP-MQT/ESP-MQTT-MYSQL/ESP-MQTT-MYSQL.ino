#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHTTYPE DHT11   
#define ssid "BuBu"
#define password "13071996"
// Thông tin về MQTT Broker
#define mqtt_server "m16.cloudmqtt.com" 
#define mqtt_topic_pub "Test"   
#define mqtt_topic_sub "Test"
#define mqtt_user "yrqlioxg"    
#define mqtt_pwd "y4VBmtB7xy-v"

const uint16_t mqtt_port = 13073; 


WiFiClient espClient;
PubSubClient client(espClient);

const int DHTPin1 = D1;      
const int DHTPin2 = D2;

long lastMsg = 0;
char msg[50];
int value = 0;
// Timers auxiliar variables
long now = millis();
long lastMeasure = 0;

// Thiet Lap cam bien DHT.
DHT dht1(DHTPin1, DHTTYPE);
DHT dht2(DHTPin2, DHTTYPE);

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port); 
  dht1.begin();
  dht2.begin();

}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Chờ tới khi kết nối
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client",mqtt_user, mqtt_pwd)) {
      Serial.println("connected");
      client.publish(mqtt_topic_pub, "ESP_reconnected");
      client.subscribe(mqtt_topic_sub);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
    client.connect("ESP8266Client");

  now = millis();
  if (now - lastMeasure > 1000) {
    lastMeasure = now;
    Data();
  }
}

void Data()
{
  int h1 = dht1.readHumidity();
  int t1 = dht1.readTemperature();
  int h2 = dht2.readHumidity();
  int t2 = dht2.readTemperature();
  if (isnan(h1) || isnan(t1) || isnan(h2) || isnan(t2)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity 1: ");
  Serial.print(h1);
  Serial.print(" %\t");
  Serial.print("Temperature 1: ");
  Serial.print(t1);
  Serial.print(" *C ");
  Serial.print("Humidity 2: ");
  Serial.print(h2);
  Serial.print(" %\t");
  Serial.print("Temperature 2: ");
  Serial.print(t2);
  Serial.print(" *C ");

  String temperature1 = String(t1);
  String humidity1 = String(h1);
  String temperature2 = String(t2);
  String humidity2 = String(h2);

  // Prepare a JSON payload string
  String payload = "{";
  payload += "\"Temp1\":"; payload += temperature1; payload += ",";
  payload += "\"Hum1\":"; payload += humidity1; payload += ",";
  payload += "\"Temp2\":"; payload += temperature2; payload += ",";
  payload += "\"Hum2\":"; payload += humidity2;
  payload += "}";

  // Send payload
  char attributes[100];
  payload.toCharArray( attributes, 100 );
  client.publish( "Test", attributes );
  Serial.println( attributes );
  delay(5000);
}
