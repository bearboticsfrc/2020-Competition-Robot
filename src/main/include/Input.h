/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <frc/Joystick.h>
#include <frc/XboxController.h>
#include "units_include.h"

using ButtonGetter = std::function<bool()>;

class Input {
 public:
  double GetX() const;
  double GetY() const;
  double GetZ() const;

  void SetRumble(double rumble);

  double GetWinchSpeed() const;
  double GetArmSpeed() const;

  ButtonGetter AutoShootButton() const;
  ButtonGetter ManualShootButton() const;

  ButtonGetter ToggleIntakePositionButton() const;
  ButtonGetter RunIntakeButton() const;
  ButtonGetter RunUptakeButton() const;
  ButtonGetter ReverseIntakeButton() const;
  ButtonGetter SetConstantSpeedButton() const;

 private:
  frc::Joystick joystick = frc::Joystick(0);
  frc::XboxController xboxController = frc::XboxController(1);
};