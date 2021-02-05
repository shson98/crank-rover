#include <SoftwareSerial.h>
#include <Arduino.h>

// USING HC05

#define BT_RX 11
#define BT_TX 13
#define EN_PIN 12

#define BUTTON_UP 0
#define BUTTON_DOWN 0

SoftwareSerial BTSerial(BT_RX, BT_TX);

const int JOYSTICK_Y = A1;
const int BUTTON_B=3;
const int BUTTON_D=5;
int y_pos;
int B_pos;
int D_pos;

byte msg;

void setup() {
  pinMode(EN_PIN,OUTPUT);
  digitalWrite(EN_PIN,HIGH);

  Serial.begin(9600);
  BTSerial.begin(9600);
  Serial.println("AT command!");

  pinMode(JOYSTICK_Y,INPUT_PULLUP);
  pinMode(BUTTON_B,INPUT_PULLUP);
  pinMode(BUTTON_D,INPUT_PULLUP);
}

void loop() {
  y_pos=analogRead(JOYSTICK_Y);
  B_pos=digitalRead(BUTTON_B);
  D_pos=digitalRead(BUTTON_D);

  if (y_pos > 700 && B_pos==BUTTON_UP && D_pos==BUTTON_UP) {
    msg = 'w';
  } else if (y_pos > 700 && B_pos==BUTTON_DOWN && D_pos==BUTTON_UP) {
    msg = 'q';
  } else if (y_pos > 700 && B_pos==BUTTON_UP && D_pos==BUTTON_DOWN) {
    msg = 'e';
  } else if (y_pos < 300 && B_pos==BUTTON_UP && D_pos==BUTTON_UP) {
    msg = 's';
  } else if (y_pos < 300 && B_pos==BUTTON_DOWN && D_pos==BUTTON_UP) {
    msg = 'z';
  } else if (y_pos < 300 && B_pos==BUTTON_UP && D_pos==BUTTON_DOWN) {
    msg = 'c';
  } else if (B_pos==BUTTON_DOWN && D_pos==BUTTON_UP) {
    msg = 'a';
  } else if (B_pos==BUTTON_UP && D_pos==BUTTON_DOWN) {
    msg = 'd';
  }

  BTSerial.print(msg);
  
  Serial.print(" & y : ");
  Serial.print(y_pos);
  Serial.print("& B : ");
  Serial.print(B_pos);
  Serial.print("& D : ");
  Serial.print(D_pos);
  Serial.print(" msg : ");
  Serial.print(msg);
}
