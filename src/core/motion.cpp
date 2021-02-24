#include <Arduino.h>
#include "motion.h"

bool Motion::checkStandby() {
    return mtrController.synchronized() && mtrController.checkStop(0) && mtrController.checkStop(1);
}

void Motion::goForward() {
    mtrController.rotateMotorForward(0);
    mtrController.rotateMotorForward(1);
}

void Motion::goForwardRight() {
    mtrController.rotateMotorForward(0);
}

void Motion::goBackward() {
    mtrController.rotateMotorBackward(0);
    mtrController.rotateMotorBackward(1);
}

void Motion::goForwardLeft() {
    mtrController.rotateMotorForward(1);
}

void Motion::goTurnLeft() {
    mtrController.rotateMotorForward(1);
    mtrController.rotateMotorBackward(0);
}

void Motion::goTurnRight() {
    mtrController.rotateMotorForward(0);
    mtrController.rotateMotorBackward(1);
}