#include <SoftwareSerial.h>
#include <Arduino.h>

// USING HC05

#define BT_RX 11
#define BT_TX 13
#define EN_PIN 12

#define JOY_UP 800
#define JOY_DOWN 200
#define BUTTON_UP 1
#define BUTTON_DOWN 0

SoftwareSerial BTSerial(BT_RX, BT_TX);

const int JOYSTICK_Y = A1;
const int BUTTON_B=3;
const int BUTTON_D=5;
int y_pos;
int b_pos;
int d_pos;

char msg;

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
  b_pos=digitalRead(BUTTON_B);
  d_pos=digitalRead(BUTTON_D);

  if (y_pos > JOY_UP && d_pos==BUTTON_UP && b_pos==BUTTON_UP) {
    msg = 'w';
  } else if (y_pos > JOY_UP && d_pos==BUTTON_DOWN && b_pos==BUTTON_UP) {
    msg = 'q';
  } else if (y_pos > JOY_UP && d_pos==BUTTON_UP && b_pos==BUTTON_DOWN) {
    msg = 'e';
  } else if (y_pos < JOY_DOWN && d_pos==BUTTON_UP && b_pos==BUTTON_UP) {
    msg = 's';
  } else if (y_pos < JOY_DOWN && d_pos==BUTTON_DOWN && b_pos==BUTTON_UP) {
    msg = 'z';
  } else if (y_pos < JOY_DOWN && d_pos==BUTTON_UP && b_pos==BUTTON_DOWN) {
    msg = 'c';
  } else if (d_pos==BUTTON_DOWN && b_pos==BUTTON_UP) {
    msg = 'a';
  } else if (d_pos==BUTTON_UP && b_pos==BUTTON_DOWN) {
    msg = 'd';
  } else {
    msg = 0;
  }

  BTSerial.print(msg);
  
  Serial.print("y : ");
  Serial.print(y_pos);
  Serial.print("& B : ");
  Serial.print(b_pos);
  Serial.print("& D : ");
  Serial.print(d_pos);
  Serial.print(" msg : ");
  Serial.print(msg);
}
