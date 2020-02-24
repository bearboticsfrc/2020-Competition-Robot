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
#include <variant>

class Hopper;

// TODO: Determine motor IDs
 namespace shooter_consts {
  const int MOTOR_ID = 8;
  const int FEEDMOTOR_ID = 11;
  const int ACCELERATOR_ID = 5;
}

class Shooter;

struct StoppedState {
  StoppedState() = delete;
  StoppedState(Shooter *shooter);
};
struct SpinningState {
  SpinningState() = delete;
  SpinningState(Shooter *shooter);

  int spinSuccesses = 0;
};
struct ShootingState {
  ShootingState() = delete;
  ShootingState(Shooter *shooter);

  std::chrono::time_point<std::chrono::steady_clock> startTime;
};

using ShooterState = std::variant<StoppedState, SpinningState, ShootingState>;

class Shooter : public frc2::SubsystemBase {
 public:
  Shooter(Hopper *hopper);

  void setSpeed(double speed);
  void shootAll();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

 private:
  friend class StoppedState;
  friend class SpinningState;
  friend class ShootingState;

  rev::CANSparkMax motor;
  VictorSPX accelerator;
  VictorSPX feedMotor;

  // The hopper is controlled because the agitator
  // must be run when shooting
  Hopper *hopper;

  bool feedQueued = false;

  ShooterState state;

  double targetRPM = 0.0;
};
