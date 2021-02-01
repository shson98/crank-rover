#include "motor_controller.h"

void EncoderMotor::updateEncoder() {
    (digitalRead(ENCODER1) == digitalRead(ENCODER2)) ? pulse++ : pulse--;
        
    if (pulse == ENCODER_RES) {
        pulse = 0;
    } else if (pulse == -1) {
        pulse = ENCODER_RES-1;
    }
}

float EncoderMotor::getPositionDegree() {
    return pulse*360/(float)ENCODER_RES;
}

int EncoderMotor::getPositionPulse() {
    return pulse;
}

void EncoderMotor::rotateDir1(int vel) {
    if(!IS_REVERSED) {
        digitalWrite(DIR1, HIGH);
        digitalWrite(DIR2, LOW);
    } else {
        digitalWrite(DIR1, LOW);
        digitalWrite(DIR2, HIGH);
    }
    analogWrite(PWM_PIN, vel);
}

void EncoderMotor::rotateDir2(int vel) {
    if(!IS_REVERSED) {
        digitalWrite(DIR1, LOW);
        digitalWrite(DIR2, HIGH);    
    } else {
        digitalWrite(DIR1, HIGH);
        digitalWrite(DIR2, LOW);
    }
    analogWrite(PWM_PIN, vel);
}

void EncoderMotor::adjustZero() {
    int pulse = getPositionPulse();
    int half = ENCODER_RES/2;
    if(pulse >= FEEDBACK_OFFSET && pulse < half) {
        (!IS_REVERSED)?rotateDir1(FEEDBACK_SPEED):rotateDir2(FEEDBACK_SPEED); //inverse feedback
    } else if (pulse <= ENCODER_RES-FEEDBACK_OFFSET && pulse >= half) {
        (!IS_REVERSED)?rotateDir2(FEEDBACK_SPEED):rotateDir1(FEEDBACK_SPEED); //inverse feedback
    } else {
        stop();
    }
}

void EncoderMotor::stop() {
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, HIGH);
    analogWrite(PWM_PIN, 0);
}

MotorController::MotorController(int velocity,EncoderMotor* encMtr0, EncoderMotor* encMtr1):VELOCITY(velocity) {
      encMtrs = new EncoderMotor*[2];
      encMtrs[0] = encMtr0;
      encMtrs[1] = encMtr1;
      deltaPulse = new int[2];
      deltaPulse[0] = 0;
      deltaPulse[1] = 0;
}

void MotorController::rotateMotorForward(int i) {
    deltaPulse[i] = encMtrs[i]->ENCODER_RES;
    updateMotorControl(i);
}

void MotorController::rotateMotorBackward(int i) {
    deltaPulse[i] = -encMtrs[i]->ENCODER_RES;
    updateMotorControl(i);
}

void MotorController::updateMotorControl(int i) {
    if (deltaPulse[i] > 0) {
        encMtrs[i]->rotateDir1(VELOCITY);
        deltaPulse[i]--;
    } else if (deltaPulse[i] < 0) {
        encMtrs[i]->rotateDir2(VELOCITY);
        deltaPulse[i]++;
    } else { //feedback
        encMtrs[i]->adjustZero();
    }
}

bool MotorController::synchronized() {
    int pos0 = encMtrs[0]->getPositionPulse();
    int pos1 = encMtrs[1]->getPositionPulse();
    int res = encMtrs[0]->ENCODER_RES;
    
    int diff = pos0 - pos1;

    if(abs(diff)<FEEDBACK_OFFSET || abs(diff-res)<FEEDBACK_OFFSET) {
        return true;
    } else {
        return false;
    }
}

bool MotorController::checkStop(int i) {
    if(deltaPulse[i]==0) {
        return true;
    } else {
        return false;
    }
}