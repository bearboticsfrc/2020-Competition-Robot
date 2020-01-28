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
 namespace climber_consts {
  const int MOTOR_1_ID = 5;
  const int MOTOR_2_ID = 6;
}

//TODO: What is the rotation direction
class Climber : public frc2::SubsystemBase {
 public:
  Climber();

    void setClimb(bool climb);
    void setSpeed(double speed);

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
