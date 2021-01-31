/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "rev/ColorSensorV3.h"
#include "rev/ColorMatch.h"
#include "units_include.h"

class ColorSensor : public frc2::SubsystemBase {
 public:
  ColorSensor();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  rev::ColorSensorV3 m_colorSensor;

  // This Color Match object is used to register and detect known colors
  // This object uses a simple euclidian distance to estimate the closest match with given confidence range.
  rev::ColorMatch m_colorMatcher;
};
