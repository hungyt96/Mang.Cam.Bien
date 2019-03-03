#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
 
MDNSResponder mdns;
 
ESP8266WebServer server(80);
String Web;
const char* ssid     = "BuBu";      // tên wifi 
const char* password = "13071996";  // password 
 
void setup() {
 
  pinMode(D1, OUTPUT);  
  pinMode(D2, OUTPUT); 
  pinMode(D3, OUTPUT); 
 
  Web += "<center><h1>ESP8266 Web Server</h1><p>LED 1 <a href=\"Led1on\"><button>ON</button></a>&nbsp;<a href=\"Led1off\"><button>OFF</button></a></p>";
  Web += "<p>LED 2 <a href=\"Led2on\"><button>ON</button></a>&nbsp;<a href=\"Led2off\"><button>OFF</button></a></p>";
  Web += "<p>COI 3 <a href=\"On\"><button>ON</button></a>&nbsp;<a href=\"Off\"><button>OFF</button></a></p>";
  
  Serial.begin(115200);
  delay(100);
 
 
  Serial.println();
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
  
  if (mdns.begin("esp8266", WiFi.localIP())) 
    Serial.println("MDNS responder started");
 
  server.on("/", [](){
    server.send(200, "text/html", Web);
  });
  server.on("/Led1on", [](){
    server.send(200, "text/html", Web);
    //Bật led1
    digitalWrite(D1, HIGH);
    delay(100);
  });
  server.on("/Led1off", [](){
    server.send(200, "text/html", Web);
    //Tắt led1
    digitalWrite(D1, LOW);
    delay(100); 
  });
  server.on("/Led2on", [](){
    server.send(200, "text/html", Web);
    //Bật led2
    digitalWrite(D2, HIGH);
    delay(100);
  });
  server.on("/Led2off", [](){
    server.send(200, "text/html", Web);
    //Tắt led2
    digitalWrite(D2, LOW);
    delay(100); 
  });
  server.on("/On", [](){
    server.send(200, "text/html", Web);
    //Bật Coi
    digitalWrite(D3, HIGH);
    delay(100);
  });
  server.on("/Off", [](){
    server.send(200, "text/html", Web);
    //Tắt Coi
    digitalWrite(D3, LOW);
    delay(100); 
  });
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop() {
  server.handleClient();
}
