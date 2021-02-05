#include <SoftwareSerial.h>
 
SoftwareSerial BTSerial(2,3); 
int ENpin=8;

void setup() {
  pinMode(ENpin,OUTPUT);
  digitalWrite(ENpin,HIGH);
  
  Serial.begin(9600);
  BTSerial.begin(9600);
  Serial.println("ATcommand");
}

void loop() {
  if(BTSerial.available()){
    Serial.write(BTSerial.read());
  }
  if (Serial.available()){
    BTSerial.write(Serial.read());
  }
}
