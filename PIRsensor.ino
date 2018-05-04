int pirPin = D8;
int val;

void setup() {
  Serial.begin(115200);
  pinMode(D2, OUTPUT);
}

void loop() {
val = digitalRead(pirPin); //read state of the PIR

if (val == LOW) {
digitalWrite(D2, LOW);
Serial.println("LOW");
}
else {
digitalWrite(D2, HIGH);
Serial.println("HIGH");
}
delay(1000); 

} 

