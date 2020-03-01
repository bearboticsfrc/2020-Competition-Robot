/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h> 

// TODO: Determine motor IDs
 namespace climber_consts {
  const int EXTEND_ID = 250;
  const int WINCH_ID = 251;
}

//TODO: What is the rotation direction
class Climber : public frc2::SubsystemBase {
 public:
  Climber();

  void setClimb(bool climb);
    void setSpeed(double speed);
    void Extend(double speed); 

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
    void Periodic();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  /*
  rev::CANSparkMax motor1;
  rev::CANSparkMax motor2;
  */
  VictorSPX extendMotor;
  VictorSPX winchMotor1;

};
