/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

class Arduino;
class Drivetrain;
class Intake;

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class BallPickup
    : public frc2::CommandHelper<frc2::CommandBase, BallPickup> {
 public:
  BallPickup(Drivetrain *drivetrain, Intake *intake, Arduino *arduino);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  Drivetrain *drivetrain;
  Intake *intake;
  Arduino *arduino;

  std::pair<double, double> getTargetSpeeds();

  int failures = 0;

  double leftSpeed = 0.0;
  double rightSpeed = 0.0;
};
