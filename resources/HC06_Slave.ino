#include <SoftwareSerial.h>
 
SoftwareSerial BTSerial(2,3); 
byte x_pos;
byte X_pos;
byte y_pos;
byte Y_pos;
byte B_pos;
byte BB_pos;
byte D_pos;
byte DD_pos;
byte data;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop() {
  if(BTSerial.available()){
    Serial.write(BTSerial.read());
  }
  if (Serial.available()){
    BTSerial.write(Serial.read());
  }

}
