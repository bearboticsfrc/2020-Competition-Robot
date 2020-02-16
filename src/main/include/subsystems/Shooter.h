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
#include <chrono>

// TODO: Determine motor IDs
 namespace shooter_consts {
  const int MOTOR_1_ID = 7;
  const int MOTOR_2_ID = 8;
  const int FEEDMOTOR_ID = 11;
  const int ACCELERATOR_ID = 5;
}

class Shooter : public frc2::SubsystemBase {
 public:
  Shooter();

  void setSpeed(double speed);
  void shootOne();
  void setFeed(double speed);

  void setDistance(units::meter_t distance);

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  rev::CANSparkMax motor1;
  rev::CANSparkMax motor2;

  rev::CANSparkMax accelerator;

  VictorSPX feedMotor;

  std::chrono::time_point<std::chrono::steady_clock> startTime;
};
