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
  SpinningState(Shooter *shooter, double targetRpm, std::function<bool()> runCheck);

  int spinSuccesses = 0;
  double targetRpm = 0.0;
  std::function<bool()> runCheck;
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

  // Begins the shooting process with the given speed.
  // If you provide a runCheck function, then it will wait
  // at the Spinning state until the function returns true.
  void shoot(double speed, std::function<bool()> runCheck = [] { return true; });

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

  bool IsStopped() const;

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

  ShooterState state;
};
