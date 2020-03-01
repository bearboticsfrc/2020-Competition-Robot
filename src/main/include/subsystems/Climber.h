/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <ctre/Phoenix.h> 


//TODO: What is the rotation direction
class Climber : public frc2::SubsystemBase {
 public:
  Climber();

  void SetExtended(bool extended);

  void Periodic();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  VictorSPX armMotor;
  VictorSPX winchMotor;

  // Positive values mean the arm is moving upwards/extending
  // Negative values mean the arm is moving downwards/retracting
  void SetArmSpeed(double speed);

  // Positive values mean the winch is unwinding/extending
  // Negative values mean the winch is winding/retracting
  void SetWinchSpeed(double speed);

  bool extended = false;
};
