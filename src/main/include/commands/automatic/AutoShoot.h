/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <chrono>

class Shooter;
class Intake;

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class AutoShoot
    : public frc2::CommandHelper<frc2::CommandBase, AutoShoot> {
public:
  AutoShoot(Shooter *shooter, Intake *intake);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

private:
  Shooter *shooter;
  Intake *intake;

  std::chrono::time_point<std::chrono::steady_clock> startTime;
  int successes = 0;
  int failures = 0;
  bool acquired = false;

  int speedSuccesses = 0;
};