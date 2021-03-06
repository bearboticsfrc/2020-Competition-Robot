/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Solenoid.h>
#include <rev/CANSparkMax.h>
#include "units_include.h"

class ControlPanelManip : public frc2::SubsystemBase {
 public:
  ControlPanelManip();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

  void setPosition(double pos);

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  frc::Solenoid extendSolenoid;
  frc::Solenoid retractSolenoid;

  rev::CANSparkMax motor;
};
