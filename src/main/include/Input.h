/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <frc/Joystick.h>
#include <frc/XboxController.h>

class Input {
 public:
  double GetX() const;
  double GetY() const;
  double GetZ() const;

  frc::Joystick joystick = frc::Joystick(0);
  frc::XboxController xboxController = frc::XboxController(1);
};
