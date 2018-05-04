#include <SoftwareSerial.h>

SoftwareSerial mySerial(D3, D4, false, 256);

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);

}

byte cmd[9] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79}; 
char response[9];

void loop() {
  mySerial.write(cmd,9);
  mySerial.readBytes(response, 9);
  int responseHigh = (int) response[2];
  int responseLow = (int) response[3];
  int ppm = (256*responseHigh)+responseLow;
  Serial.println("CO2="+ String(ppm));
  delay(3000);
}
