#include <DHT.h>            
#include <ESP8266WiFi.h>    
#define DHTPIN1 D1 
#define DHTPIN2 D2           
#define DHTTYPE DHT11       

DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);
WiFiClient client;          
const char* ssid = "BuBu";      
const char* password = "13071996";  
const char* server = "192.168.0.100";     
const int port = 3000;                    

void setup() {
  Serial.begin(115200);
  dht1.begin();  
  dht2.begin();                          
  Serial.println("Connecting");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println("\r\nWiFi connected");
}

void loop() {
  float temp1 = dht1.readTemperature();
  float hum1 = dht1.readHumidity();
  float temp2 = dht2.readTemperature();
  float hum2 = dht2.readHumidity();
  if (isnan(temp1) || isnan(hum1) || isnan(temp2) || isnan(hum2)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  if (client.connect(server, port)) {       // Khởi tạo kết nối đến server thông qua IP và PORT đã mở
  //---------------------------------------------------------------------------------------
    String req_uri = "/update?temp1=" + String(temp1, 1) + "&hum1=" + String(hum1, 1) + "&temp2=" + String(temp2, 1) + "&hum2=" + String(hum2, 1);
    client.print("GET " + req_uri + " HTTP/1.1\n" + "Host: "+ server +"\n" + "Connection: close\n" + "Content-Length: 0\n" +"\n\n");   
  //---------------------------------------------------------------------------------------

  // temp, humi chuyển từ định dạng float sang định dạng string và in ra màn hình serial      // terminal trên Arduino.
    Serial.printf("Nhiet do %s - Do am %s\r\n", String(temp1, 1).c_str(), String(hum1, 1).c_str(), String(temp2, 1).c_str(), String(hum2, 1).c_str());
  }
  client.stop();                          // Ngắt kết nối đến server

  delay(2000);
}
