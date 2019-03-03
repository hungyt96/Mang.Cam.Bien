
 #include<DHT.h>           
 
const int DHTPIN1 = D2;       //Chân đọc dữ liệu từ cảm biến
const int DHTTYPE = DHT11;  //Loại cảm biến dùng
DHT dht(DHTPIN1, DHTTYPE);
 
void setup() {
  Serial.begin(115200);
  dht.begin();         // Khởi động cảm biến
}
 
void loop() {
  float h = dht.readHumidity();    //Đọc độ ẩm
  float t = dht.readTemperature(); //Đọc nhiệt độ
  
  Serial.print("Nhiet do : ");
  Serial.println(t);               
  Serial.print("Do am : ");
  Serial.println(h);  
  
  delay(1500);
  Serial.println();                //Xuống hàng
  
}
