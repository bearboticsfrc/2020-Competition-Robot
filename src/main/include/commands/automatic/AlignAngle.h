/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

class Drivetrain;

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class AlignAngle
    : public frc2::CommandHelper<frc2::CommandBase, AlignAngle> {
 public:
  AlignAngle(units::degree_t target, Drivetrain *drivetrain);

  AlignAngle(units::degree_t *target, Drivetrain *drivetrain);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

private:
  Drivetrain *drivetrain;
  units::degree_t target;
  units::degree_t *target2 = nullptr;
  int successes = 0;
};


// Returns true if the robot is sufficiently aligned
bool doAlign(Drivetrain *drivetrain, units::degree_t target);