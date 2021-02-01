#include <Arduino.h>
#include <Thread.h>
#include "motion.h"
#include "motor_controller.h"

#define ENCODER_RES (26*75)

#define MOTOR0_DIR_1 22
#define MOTOR0_DIR_2 23
#define MOTOR0_PWM 13
#define ENCODER0_A 18
#define ENCODER0_B 19
#define ENCODER0_INT ENCODER0_A //pin21, ENCODER1_A

#define MOTOR1_DIR_1 24
#define MOTOR1_DIR_2 25
#define MOTOR1_PWM 12
#define ENCODER1_A 20
#define ENCODER1_B 21
#define ENCODER1_INT ENCODER1_A //pin20

#define SPEED 255

EncoderMotor encMtr0 = EncoderMotor(MOTOR0_DIR_1, MOTOR0_DIR_2, MOTOR0_PWM, ENCODER0_A, ENCODER0_B, ENCODER_RES);
EncoderMotor encMtr1 = EncoderMotor(MOTOR1_DIR_1, MOTOR1_DIR_2, MOTOR1_PWM, ENCODER1_A, ENCODER1_B, ENCODER_RES, true);
MotorController mtrController = MotorController(255, &encMtr0, &encMtr1);
Motion motion = Motion(mtrController);
Thread serialThread = Thread();

//attach callbacks to interrupts
void encoderCallback0() {
  encMtr0.updateEncoder();
  mtrController.updateMotorControl(0);
}

void encoderCallback1() {
  encMtr1.updateEncoder();
  mtrController.updateMotorControl(1);
}

void reportCallback() {
  Serial.print("Motor0 Pos: ");
  Serial.print(encMtr0.getPositionPulse());
  Serial.print(" Motor1 Pos: ");
  Serial.println(encMtr1.getPositionPulse());
}

void setup() {
  Serial.begin(115200);
  
  pinMode(MOTOR0_DIR_1, OUTPUT);
  pinMode(MOTOR0_DIR_2, OUTPUT);
  pinMode(MOTOR0_PWM, OUTPUT);
  pinMode(ENCODER0_A, INPUT_PULLUP);
  pinMode(ENCODER0_B, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCODER0_INT), encoderCallback0, CHANGE);

  pinMode(MOTOR1_DIR_1, OUTPUT);
  pinMode(MOTOR1_DIR_2, OUTPUT);
  pinMode(MOTOR1_PWM, OUTPUT);
  pinMode(ENCODER1_A, INPUT_PULLUP);
  pinMode(ENCODER1_B, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCODER1_INT), encoderCallback1, CHANGE);

  serialThread.onRun(reportCallback);
  serialThread.setInterval(500);
}

void loop() {
  if(serialThread.shouldRun())
    serialThread.run();

  if(motion.checkStandby()) {
    if(Serial.available()) {
      char msg = Serial.read();
      switch(msg) { 
        case 'w':
          motion.goForward();  break;
        case 's':
          motion.goBackward();  break;
        case 'a':
          motion.goTurnLeft();  break;
        case 'd':
          motion.goTurnRight();  break;
        case 'q':
          motion.goForwardLeft();  break;
        case 'e':
          motion.goForwardRight();  break;
        default:  
          break;
      }
    }
  } else {
    while(Serial.available())
      Serial.read(); //empty buffer
  }
}