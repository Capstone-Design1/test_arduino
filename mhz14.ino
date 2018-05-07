#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid     = "MMlab1001";
const char* password = "mpeglab10";
const char* host = "api.thingspeak.com";
String apiKey = "9ZWD5P5078OR9YO6"; // thingspeak.com api key goes here

SoftwareSerial mySerial(D2, D1, false, 256);

ESP8266WebServer server(80);
WiFiClient client;

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);
  connectToWiFi();
}

byte cmd[9] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79}; 
char response[9];

void loop() {
  delay(3000); // 3초 마다
  mySerial.write(cmd,9);
  mySerial.readBytes(response, 9);
  int responseHigh = (int) response[2];
  int responseLow = (int) response[3];
  //Serial.println(String(responseHigh)+" "+String(responseLow) );
  int ppm = (256*responseHigh)+responseLow;
  Serial.println("CO2="+ String(ppm));

  client.connect(host,80);
  String postStr = apiKey;
    postStr +="&field1=";
    postStr += String(ppm);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    client.stop();
}

void connectToWiFi(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
 
  Serial.print("Connecting to ");
  Serial.println(ssid); 

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  startServer();
}

void startServer(){
  //server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}
