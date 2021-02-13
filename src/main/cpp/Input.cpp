/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Input.h"
#include "units_include.h"

using RumbleType = frc::GenericHID::RumbleType;
using JoystickHand = frc::GenericHID::JoystickHand;

const double DEADZONE = 0.05;

template<class T> int signum(T value) {
    return (value > T{0}) - (value < T{0});
}

double applyDeadzone(double value) {
    double sign = signum(value);
    double magn = std::abs(value);

    if (magn < DEADZONE) {
        return 0.0;
    }

    double newMag = (magn - DEADZONE) / (1.0 - DEADZONE);
    return newMag * sign;
}

double applyFilters(double value) {
    double deadzoned = applyDeadzone(value);
    return std::pow(deadzoned, 3.0);
}

double Input::GetX() const {
    return applyFilters(xboxController.GetX(JoystickHand::kLeftHand));
}

double Input::GetY() const {
    return applyFilters(xboxController.GetY(JoystickHand::kLeftHand));
}

void Input::SetRumble(double rumble) {
    xboxController1.SetRumble(RumbleType::kLeftRumble, rumble);
    xboxController1.SetRumble(RumbleType::kRightRumble, rumble);
}

double Input::GetWinchSpeed() const {
    // Up is 0 (360)
    // Down is 180

    if (xboxController1.GetPOV() == 270) {
        return -1.0;
    } else {
        return 0.0;
    }
}

double Input::GetArmSpeed() const {
    switch (xboxController1.GetPOV()) {
        case 0: return 1.0;
        case 180: return -1.0;
        default: return 0.0;
    }
}

ButtonGetter Input::AutoShootButton() const {
    return [this]() { return xboxController1.GetBumper(JoystickHand::kRightHand); };
}
ButtonGetter Input::ManualShootButton() const {
    return [this]() { return xboxController1.GetTriggerAxis(JoystickHand::kRightHand) > 0.5; };
}

ButtonGetter Input::ToggleIntakePositionButton() const {
    return [this]() { return xboxController1.GetBumper(JoystickHand::kLeftHand); };
}
ButtonGetter Input::RunIntakeButton() const {
    return [this]() { return xboxController1.GetTriggerAxis(JoystickHand::kLeftHand) > 0.5; };
}
ButtonGetter Input::RunUptakeButton() const {
    return [this]() { return xboxController1.GetXButton(); };
}
ButtonGetter Input::ReverseIntakeButton() const {
    return [this]() { return xboxController1.GetYButton(); };
}