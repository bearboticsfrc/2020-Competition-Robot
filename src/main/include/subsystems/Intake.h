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

class Hopper;

// TODO: Determine motor IDs
namespace intake_consts {
  const int MOTOR_ID = 12;
  const int SOLENOID_ID = 3;
}

enum class IntakeMode {
  Intake,
  Outtake,
  Uptake,
  Stopped,
};

class Intake : public frc2::SubsystemBase {
 public:
  Intake(Hopper *hopper);

  void setMode(IntakeMode mode);

  void setExtended(bool extended);

  bool getExtended();

  void Periodic();

 private:
  rev::CANSparkMax motor;

  frc::Solenoid solenoid;

  Hopper *hopper;

  IntakeMode mode = IntakeMode::Stopped;
};
