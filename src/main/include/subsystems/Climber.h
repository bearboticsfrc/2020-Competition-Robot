/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>
#include <rev/CANSparkMax.h>


//TODO: What is the rotation direction
class Climber : public frc2::SubsystemBase {
 public:
  Climber();

  // 1.0 means extending, -1.0 means retracting
  void SetSpeed(double speed);

  void Periodic();

  // Positive values mean the arm is moving upwards/extending
  // Negative values mean the arm is moving downwards/retracting
  void SetArmSpeed(double speed);

  // Positive values mean the winch is unwinding/extending
  // Negative values mean the winch is winding/retracting
  void SetWinchSpeed(double speed);

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  rev::CANSparkMax armMotor;
  VictorSPX winchMotor;

  bool extended = false;
};
