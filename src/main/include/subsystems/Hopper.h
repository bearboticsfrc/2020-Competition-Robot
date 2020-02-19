/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>

// TODO: Determine motor IDs
 namespace hopper_consts {
  const int INTAKE_MOTOR_ID = 13;
  const int AGITATE_MOTOR_ID = 14;
}

class Hopper : public frc2::SubsystemBase {
 public:
  Hopper();

  void setIntake(bool intake);
  void setOuttake(bool outtake);

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  rev::CANSparkMax intakeMotor;
  rev::CANSparkMax agitateMotor;
};
