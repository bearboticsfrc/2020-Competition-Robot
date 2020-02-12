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
 * <p>Note that this extendshttps://prod.liveshare.vsengsaas.visualstudio.com/join?7D329AFCA8E55FE215E76321BF1B04C7BAE2 CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class AlignTarget
    : public frc2::CommandHelper<frc2::CommandBase, AlignTarget> {
 public:
  AlignTarget(Drivetrain *drivetrain);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;
private:
  int successes = 0;
  int fails = 0;

  Drivetrain *drivetrain;
};
