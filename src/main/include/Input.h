/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <functional>
#include <frc/Joystick.h>
#include <frc/XboxController.h>
#include "units_include.h"

using ButtonGetter = std::function<bool()>;

class Input {
 public:
  virtual double GetX() const = 0;
  virtual double GetY() const = 0;
  virtual double GetZ() const = 0;

  virtual void SetRumble(double rumble) = 0;

  virtual double GetWinchSpeed() const = 0;
  virtual double GetArmSpeed() const = 0;

  virtual ButtonGetter AutoShootButton() const = 0;
  virtual ButtonGetter ManualShootButton() const = 0;

  virtual ButtonGetter ToggleIntakePositionButton() const = 0;
  virtual ButtonGetter RunIntakeButton() const = 0;
  virtual ButtonGetter RunUptakeButton() const = 0;
  virtual ButtonGetter ReverseIntakeButton() const = 0;

 private:
 // frc::Joystick joystick = frc::Joystick(0);
 // frc::XboxController xboxController = frc::XboxController(1);
};