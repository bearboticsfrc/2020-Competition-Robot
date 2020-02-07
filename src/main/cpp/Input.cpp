/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Input.h"

const double DEADZONE = 0.10;

template<class T> int signum(T value) {
    return value > T{0} - value < T{0};
}

double applyDeadzone(double value, double deadzone) {
    double sign = signum(value);
    double magn = std::abs(value);

    if (magn < DEADZONE) {
        return 0.0;
    }

    double newMag = (magn - DEADZONE) / (1.0 - DEADZONE);
    return newMag * sign;
}

double Input::GetX() const {
    return applyDeadzone(joystick.GetX(), DEADZONE);
}

double Input::GetY() const {
    return applyDeadzone(joystick.GetY(), DEADZONE);
}

double Input::GetZ() const {
    return applyDeadzone(joystick.GetZ(), DEADZONE);
}
