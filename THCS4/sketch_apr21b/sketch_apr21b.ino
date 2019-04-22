#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WebSocketsClient.h> 
#include <DHT.h>               
#define DHTPIN D1           
#define DHTTYPE DHT11 

WebSocketsClient webSocket;
DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;

const char* ssid = "BuBu";      
const char* password = "themchuatruocpasscu";  
const char* server = "192.168.43.98";     
const int port = 3000; 
const int LED = D0;
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[WSc] Disconnected!\n");
      break;
    case WStype_CONNECTED:
      {
        Serial.printf("[WSc] Connected to url: %s\n",  payload);
      }
      break;
    case WStype_TEXT:
      Serial.printf("[WSc] get text: %s\n", payload);
      if(strcmp((char*)payload, "LED_ON") == 0) {
        digitalWrite(LED, 1); // Khi client phát sự kiện "LED_ON" thì server sẽ bật LED
      } else if(strcmp((char*)payload, "LED_OFF") == 0) {
        digitalWrite(LED, 0); // Khi client phát sự kiện "LED_OFF" thì server sẽ tắt LED
      }
      break;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  dht.begin(); 
  Serial.println("ESP8266 Websocket Client");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  webSocket.begin(server, port);
  webSocket.onEvent(webSocketEvent);

}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  if (isnan(temp) || isnan(hum)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  if (client.connect(server, port)) {       // Khởi tạo kết nối đến server thông qua IP và PORT đã mở
  //---------------------------------------------------------------------------------------
    String req_uri = "/update?temp=" + String(temp, 1) + "&hum=" + String(hum, 1) ;
    client.print("GET " + req_uri + " HTTP/1.1\n" + "Host: "+ server +"\n" + "Connection: close\n" + "Content-Length: 0\n" +"\n\n");   
  //---------------------------------------------------------------------------------------

  // temp, humi chuyển từ định dạng float sang định dạng string và in ra màn hình serial      // terminal trên Arduino.
    Serial.printf("Nhiet do %s - Do am %s\r\n", String(temp, 1).c_str(), String(hum, 1).c_str());
  }
  client.stop();                          // Ngắt kết nối đến server
  webSocket.loop();
  delay(1000);
}
