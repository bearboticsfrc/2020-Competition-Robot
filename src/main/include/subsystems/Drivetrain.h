/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/SparkMax.h>

namespace DriveConsts {
  const int BACK_LEFT_ID = 4;
  const int BACK_RIGHT_ID = 3;
  const int FRONT_LEFT_ID = 6;
  const int FRONT_RIGHT_ID = 8;
}

class Drivetrain : public frc2::SubsystemBase {
 public:
  Drivetrain();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

  void SetSpeed(double speed);

  void SetAllSpeed(double leftSpeed, double rightSpeed);

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  rev::SparkMax leftBack;
  rev::SparkMax leftFront;
  rev::SparkMax rightBack;
  rev::SparkMax rightFront;
};
