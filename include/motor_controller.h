#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include <Arduino.h>

#define FEEDBACK_OFFSET 10
#define FEEDBACK_SPEED 150

class EncoderMotor {
  public:
    EncoderMotor(uint8_t dir1, uint8_t dir2, uint8_t pwm,
                uint8_t encoder1, uint8_t encoder2, uint16_t encoderRes, bool isReversed=false) :
                ENCODER_RES(encoderRes), DIR1(dir1), DIR2(dir2), PWM_PIN(pwm),
                ENCODER1(encoder1), ENCODER2(encoder2), IS_REVERSED(isReversed) {
      pulse = 0;
    }
    ~EncoderMotor() {} //not in use
    
    void updateEncoder();
    void rotateDir1(int);
    void rotateDir2(int);
    void stop();
    void adjustZero();
    float getPositionDegree();
    int getPositionPulse();

    const uint16_t ENCODER_RES;

  private:
    const uint8_t DIR1, DIR2, PWM_PIN, ENCODER1, ENCODER2;
    const bool IS_REVERSED;
    int pulse;
};

class MotorController {
  public:
    MotorController(int, EncoderMotor*, EncoderMotor*);
    void rotateMotorForward(int);
    void rotateMotorBackward(int);
    void updateMotorControl(int);
    bool synchronized();
    bool checkStop(int);

  private:
    const int VELOCITY;
    EncoderMotor** encMtrs;
    int* deltaPulse;
};

#endif