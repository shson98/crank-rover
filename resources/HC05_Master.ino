#include <SoftwareSerial.h>
 
SoftwareSerial BTSerial(11,13);
int ENpin=12;

const int joystick_x=A0;
int x_pos;
const int joystick_y=A1;
int y_pos;
const int button_B=3;
int B_pos;
const int button_D=5;
int D_pos;

void setup() {
  pinMode(ENpin,OUTPUT);
  digitalWrite(ENpin,HIGH);

  Serial.begin(9600);
  BTSerial.begin(9600);
  Serial.println("AT command!");

  pinMode(joystick_x,INPUT_PULLUP);
  pinMode(joystick_y,INPUT_PULLUP);
  pinMode(button_B,INPUT_PULLUP);
  pinMode(button_D,INPUT_PULLUP);
  

}

void loop() {
  x_pos=analogRead(joystick_x);
  y_pos=analogRead(joystick_y);
  B_pos=digitalRead(button_B);
  D_pos=digitalRead(button_D);
  
  //BTSerial.write(x_pos);
  //BTSerial.write(y_pos);
  //BTSerial.write(B_pos);
  //BTSerial.write(D_pos);
  
  BTSerial.print("x : ");
  BTSerial.print(x_pos);
  BTSerial.print(" & y : ");
  BTSerial.print(y_pos);
  BTSerial.print("& B : ");
  BTSerial.print(B_pos);
  BTSerial.print("& D : ");
  BTSerial.println(D_pos);
  
  Serial.print("x : ");
  Serial.print(x_pos);
  Serial.print(" & y : ");
  Serial.print(y_pos);
  Serial.print("& B : ");
  Serial.print(B_pos);
  Serial.print("& D : ");
  Serial.println(D_pos);
}
