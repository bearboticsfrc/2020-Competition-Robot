/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "XboxControllerInput.h"
#include "units_include.h"

using RumbleType = frc::GenericHID::RumbleType;

const double DEADZONE = 0.05;

template<class T> int signum(T value) {
    return (value > T{0}) - (value < T{0});
}

double XboxControllerInput::applyDeadzone(double value) const {
    double sign = signum(value);
    double magn = std::abs(value);

    if (magn < DEADZONE) {
        return 0.0;
    }

    double newMag = (magn - DEADZONE) / (1.0 - DEADZONE);
    return newMag * sign;
}

double XboxControllerInput::applyFilters(double value) const {
    double deadzoned = applyDeadzone(value);
    return std::pow(deadzoned, 3.0);
}

double XboxControllerInput::GetX() const {
    return this->XboxControllerInput::applyFilters(joystick.GetX());
}

double XboxControllerInput::GetY() const {
    return this->applyFilters(joystick.GetY());
}

double XboxControllerInput::GetZ() const {
    return this->applyFilters(joystick.GetZ());
}

void XboxControllerInput::SetRumble(double rumble) {
    xboxController.SetRumble(RumbleType::kLeftRumble, rumble);
    xboxController.SetRumble(RumbleType::kRightRumble, rumble);
}

double XboxControllerInput::GetWinchSpeed() const {
    // Up is 0 (360)
    // Down is 180

    if (xboxController.GetPOV() == 270) {
        return -1.0;
    } else {
        return 0.0;
    }
}

double XboxControllerInput::GetArmSpeed() const {
    switch (xboxController.GetPOV()) {
        case 0: return 1.0;
        case 180: return -1.0;
        default: return 0.0;
    }
}

ButtonGetter XboxControllerInput::AutoShootButton() const {
    return [this]() { return xboxController.GetRightBumper(); };
}
ButtonGetter XboxControllerInput::ManualShootButton() const {
    return [this]() { return xboxController.GetRightTriggerAxis() > 0.5; };
}

ButtonGetter XboxControllerInput::ToggleIntakePositionButton() const {
    return [this]() { return xboxController.GetLeftBumper(); };
}
ButtonGetter XboxControllerInput::RunIntakeButton() const {
    return [this]() { return xboxController.GetLeftTriggerAxis() > 0.5; };
}
ButtonGetter XboxControllerInput::RunUptakeButton() const {
    return [this]() { return xboxController.GetXButton(); };
}
ButtonGetter XboxControllerInput::ReverseIntakeButton() const {
    return [this]() { return xboxController.GetYButton(); };
}