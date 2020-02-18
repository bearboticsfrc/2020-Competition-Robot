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

// TODO: Determine motor IDs
namespace intake_consts {
  const int MOTOR_1_ID = 250;
  const int MOTOR_2_ID = 249;
  const int SOLENOID_ID = 1;
}

class Intake : public frc2::SubsystemBase {
 public:
  Intake();

  void setIntake(bool intake);

  void setExtended(bool extended);

  bool getExtended();

  void Periodic();

 private:
  rev::CANSparkMax motor1;

  frc::Solenoid solenoid;
};
