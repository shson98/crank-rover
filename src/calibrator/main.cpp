#include <Arduino.h>
#include <Thread.h>

#include "motion.h"
#include "motor_controller.h"

// USING HC06
#define BT_RX 18 //DUE TX
#define BT_TX 19 //DUE RX
#define ENCODER_RES (26*75)

#define MOTOR0_SPEED 247
#define MOTOR0_DIR_1 22
#define MOTOR0_DIR_2 23
#define MOTOR0_PWM 13
#define ENCODER0_A 30
#define ENCODER0_B 31
#define ENCODER0_INT ENCODER0_A //pin21, ENCODER1_A


#define MOTOR1_SPEED 255
#define MOTOR1_DIR_1 24
#define MOTOR1_DIR_2 25
#define MOTOR1_PWM 12
#define ENCODER1_A 32
#define ENCODER1_B 33
#define ENCODER1_INT ENCODER1_A //pin20

EncoderMotor encMtr0 = EncoderMotor(MOTOR0_SPEED, MOTOR0_DIR_1, MOTOR0_DIR_2, MOTOR0_PWM, ENCODER0_A, ENCODER0_B, ENCODER_RES);
EncoderMotor encMtr1 = EncoderMotor(MOTOR1_SPEED, MOTOR1_DIR_1, MOTOR1_DIR_2, MOTOR1_PWM, ENCODER1_A, ENCODER1_B, ENCODER_RES, true);
MotorController mtrController = MotorController(&encMtr0, &encMtr1);
Motion motion = Motion(mtrController);
Thread serialThread = Thread();

//attach callbacks to interrupts
void encoderCallback0()
{
    mtrController.updateMotorControl(0, true);
}

void encoderCallback1()
{
    mtrController.updateMotorControl(1, true);
}

void reportCallback()
{
    Serial.print("Motor0 Pos: ");
    Serial.print(encMtr0.getPositionPulse());
    Serial.print(" Motor1 Pos: ");
    Serial.println(encMtr1.getPositionPulse());
}

void setup()
{
    Serial.begin(9600);
    Serial1.begin(9600);

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

void loop()
{
    if (serialThread.shouldRun())
        serialThread.run();

    if (Serial.available())
    {
        char msg = Serial.read();
        Serial.print("Read: ");
        Serial.println(msg);
        switch (msg)
        {
        case 'q':
            mtrController.rotateMotorForward(0, 10);
            break;
        case 'a':
            mtrController.rotateMotorBackward(0, 10);
            break;
        case 'w':
            mtrController.rotateMotorForward(0, 10);
            mtrController.rotateMotorForward(1, 10);
            break;
        case 's':
            mtrController.rotateMotorBackward(0, 10);
            mtrController.rotateMotorBackward(1, 10);
            break;
        case 'e':
            mtrController.rotateMotorForward(1, 10);
            break;
        case 'd':
            mtrController.rotateMotorBackward(1, 10);
        default:
            break;
        }
    }
}