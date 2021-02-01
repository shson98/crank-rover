#include <MsTimer2.h>

#define Motor1_Dir_1 24
#define Motor1_Dir_2 25
#define Motor1_PWM 12
#define Encoder1_A 20 //interrupt A
#define Encoder1_B 21 //interrupt B

#define Motor2_Dir_3 22
#define Motor2_Dir_4 23
#define Motor2_PWM 13
#define Encoder2_A 18 //interrupt A
#define Encoder2_B 19 //interrupt A

#define Motor3_Dir_1 26
#define Motor3_Dir_2 27
#define Motor3_PWM 11
#define Encoder3_A 2 //interrupt A
#define Encoder3_B 3 //interrupt A

#define Motor4_Dir_3 
#define Motor4_Dir_4 
#define Motor4_PWM 
#define Encoder4_A 
#define Encoder4_B 

int EncoderPos1 = 0;
int EncoderPos2 = 0;
int EncoderPos3 = 0;

int Rotation_count1 = 0;
int Rotation_count2 = 0;
int Rotation_count3 = 0;

void doEncoder1() {
  if (digitalRead(Encoder1_A) == digitalRead(Encoder1_B)) {
    EncoderPos1 ++;
    if (abs(EncoderPos1) >= 67) {
      Rotation_count1 ++;
      EncoderPos1 = 0;
    }
  }
  else  {
    EncoderPos1 --;
    if (abs(EncoderPos1) >= 67) {
      Rotation_count1 --;
      EncoderPos1 = 0;
    }
  }
}

void doEncoder2() {
  if (digitalRead(Encoder2_A) == digitalRead(Encoder2_B)) {
    EncoderPos2 ++;
    if (abs(EncoderPos2) >= 67) {
      Rotation_count2 ++;
      EncoderPos2 = 0;
    }
  }
  else  {
    EncoderPos2 --;
    if (abs(EncoderPos2) >= 67) {
      Rotation_count2 --;
      EncoderPos2 = 0;
    }
  }
}

void doEncoder3() {
  if (digitalRead(Encoder3_A) == digitalRead(Encoder3_B)) {
    EncoderPos3 ++;
    if (abs(EncoderPos3) >= 67) {
      Rotation_count3 ++;
      EncoderPos3 = 0;
    }
  }
  else  {
    EncoderPos3 --;
    if (abs(EncoderPos3) >= 67) {
      Rotation_count3 --;
      EncoderPos3 = 0;
    }
  }
}

float before1 = 0;
float before2 = 0;
float before3 = 0;

void Deg_per_sec() {
  float Dps_1 = float(abs(float(Rotation_count1))/(26))*360;
  float result1 = (Dps_1 - before1);
  Serial.print("M1 -> ");
  Serial.print("Deg/s: ");
  Serial.print(result1);
  Serial.print("  ");
  Serial.print("rad/s: ");
  Serial.print(result1*(3.1415926535/180));
  Serial.print("  |  ");
  before1 = Dps_1;

  float Dps_2 = float(abs(float(Rotation_count2))/(26))*360;
  float result2 = (Dps_2 - before2);
  Serial.print("M2 -> ");
  Serial.print("Deg/s: ");
  Serial.print(result2);
  Serial.print("  ");
  Serial.print("rad/s: ");
  Serial.print(result2*(3.1415926535/180));
  Serial.print("  |  ");
  before2 = Dps_2;

  float Dps_3 = float(abs(float(Rotation_count3))/(26))*360;
  float result3 = (Dps_3 - before3);
  Serial.print("M3 -> ");
  Serial.print("Deg/s: ");
  Serial.print(result3);
  Serial.print("  ");
  Serial.print("rad/s: ");
  Serial.print(result3*(3.1415926535/180));
  Serial.println("  |  ");
  before3 = Dps_3;
}

void doMotor1(int a, int b, int vel1) {
  digitalWrite(Motor1_Dir_1, a);
  digitalWrite(Motor1_Dir_2, b);
  analogWrite(Motor1_PWM, vel1);
}

void doMotor2(int c, int d, int vel2) {
  digitalWrite(Motor2_Dir_3, c);
  digitalWrite(Motor2_Dir_4, d);
  analogWrite(Motor2_PWM, vel2);
}

void doMotor3(int e, int f, int vel3) {
  digitalWrite(Motor3_Dir_1, e);
  digitalWrite(Motor3_Dir_2, f);
  analogWrite(Motor3_PWM, vel3);
}


void setup() {
  pinMode(Motor1_Dir_1, OUTPUT);
  pinMode(Motor1_Dir_2, OUTPUT);
  pinMode(Motor1_PWM, OUTPUT);

  pinMode(Motor2_Dir_3, OUTPUT);
  pinMode(Motor2_Dir_4, OUTPUT);
  pinMode(Motor2_PWM, OUTPUT);

  pinMode(Motor3_Dir_1, OUTPUT);
  pinMode(Motor3_Dir_2, OUTPUT);
  pinMode(Motor3_PWM, OUTPUT);

  pinMode(Encoder1_A, INPUT_PULLUP);
  pinMode(Encoder1_B, INPUT_PULLUP);
  attachInterrupt(3, doEncoder1, CHANGE);

  pinMode(Encoder2_A, INPUT_PULLUP);
  pinMode(Encoder2_B, INPUT_PULLUP);
  attachInterrupt(5, doEncoder2, CHANGE);

  pinMode(Encoder3_A, INPUT_PULLUP);
  pinMode(Encoder3_B, INPUT_PULLUP);
  attachInterrupt(0, doEncoder3, CHANGE);

  MsTimer2::set(1000, Deg_per_sec);
  MsTimer2::start();

  Serial.begin(9600);
}


void loop() {
  if (Serial.available()) {
    char input = Serial.read();
    if (input == 'w') {
      doMotor1(LOW, HIGH,60);
      doMotor2(HIGH, LOW,60);
      doMotor3(LOW, HIGH,60);
    } 
    else if (input == 'a') {
      doMotor1(HIGH, LOW,60);
      doMotor2(HIGH, LOW,60);
      doMotor3(LOW, HIGH,60);
    } 
    else if (input == 'd') {
      doMotor1(LOW, HIGH,60);
      doMotor2(LOW, HIGH,60);
      doMotor3(HIGH, LOW,60);
    } 
    else if (input == 's') {
      doMotor1(HIGH, LOW,60);
      doMotor2(LOW, HIGH,60);
      doMotor3(HIGH, LOW,60);
    }
    else if (input == 'f') {
      doMotor1(HIGH, HIGH, 0);
      doMotor2(HIGH, HIGH, 0);
      doMotor3(HIGH, HIGH, 0);
    }
  }
}
