#ifndef MOTION_H
#define MOTION_H
#include "motor_controller.h"

class Motion {
    public:
        Motion(MotorController& mtrController) : mtrController(mtrController) {};
        ~Motion(){} //not in use

        bool checkStandby();

        void goForward();
        void goForwardRight();
        void goBackward();
        void goForwardLeft();
        void goTurnLeft();
        void goTurnRight();

    private:
        MotorController& mtrController;
};

#endif