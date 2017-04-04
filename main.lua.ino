#include <ESP8266WiFi.h>

const char* ssid     = "xxxx"; // YOUR_WIFI_NAME
const char* password = "xxxxxx";
String pubString;
const char* host     = "xxx.xxx.xx.xxx"; // Ip of server where data has to be sent
float sensor1Value   = 0;
float sensor2Value   = 0 ;
float sensor3Value   = 0 ;
const int httpPort   = 3000;

//Mux control pins
int s0 = 16;
int s1 = 5;
int s2 = 4;
int s3 = 0;

//Mux in "SIG" pin
int SIG_pin = 0;

void setup() {
    pinMode(s0, OUTPUT); 
    pinMode(s1, OUTPUT); 
    pinMode(s2, OUTPUT); 
    pinMode(s3, OUTPUT); 
  
    digitalWrite(s0, LOW);
    digitalWrite(s1, LOW);
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);

    Serial.begin(9600);
    delay(100);
  
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP()); 
   
}

void loop(){
  POST();
}

void POST(void){
  WiFiClient client;
    // This is your NodeMCU IP address. Could be handy for other projects
  if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
   } 
  delay(100);  
  sensor1Value = readMux(0); 
  sensor2Value = readMux(1);
  sensor3Value = readMux(2);
  pubString = "{\"sensor1Val\": " + String(sensor1Value) + ", \"sensor2Val\": " + String(sensor2Value) + ", \"sensor3Val\": " + String(sensor3Value) + "}";
  String pubStringLength = String(pubString.length(), DEC);
  Serial.print("Requesting POST: ");
  client.println("POST /?sensor1Val="+ String(sensor1Value) + "&sensor2Val=" + String(sensor2Value) + "&sensor3Val=" + String(sensor3Value)  +" HTTP/1.1");
  client.println("Content-Type: application/json");
  client.println("Connection: close");
  client.print("Content-Length: ");
  client.println(pubStringLength);
  client.println();
  Serial.print("Sending Analog Value" + pubString);
  client.print(pubString);
  client.println();  
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }  
}

int readMux(int channel){
  int controlPin[] = {s0, s1, s2, s3};

  int muxChannel[16][4]={
    {0,0,0,0}, //channel 0
    {1,0,0,0}, //channel 1
    {0,1,0,0}, //channel 2
    {1,1,0,0}, //channel 3
    {0,0,1,0}, //channel 4
    {1,0,1,0}, //channel 5
    {0,1,1,0}, //channel 6
    {1,1,1,0}, //channel 7
    {0,0,0,1}, //channel 8
    {1,0,0,1}, //channel 9
    {0,1,0,1}, //channel 10
    {1,1,0,1}, //channel 11
    {0,0,1,1}, //channel 12
    {1,0,1,1}, //channel 13
    {0,1,1,1}, //channel 14
    {1,1,1,1}  //channel 15
  };

  //loop through the 4 sig
  for(int i = 0; i < 4; i ++){
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }
  //read the value at the SIG pin
  int val = analogRead(SIG_pin);
  //return the value
  return val;
}
