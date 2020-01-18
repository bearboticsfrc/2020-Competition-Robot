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
namespace intake_consts {
  const int MOTOR_1_ID = 3;
  const int MOTOR_2_ID = 4;
}

class Intake : public frc2::SubsystemBase {
 public:
  Intake();

  void setIntake(bool intake);


  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  rev::CANSparkMax motor1;
  rev::CANSparkMax motor2;

};
