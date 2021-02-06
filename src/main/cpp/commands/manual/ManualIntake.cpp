/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/manual/ManualIntake.h"
#include "subsystems/Intake.h"
#include "units_include.h"

ManualIntake::ManualIntake(Intake *intake, std::function<bool()> shouldIntake, std::function<bool()> shouldUptake, std::function<bool()> shouldReverse) :
  intake(intake),
  shouldIntake(shouldIntake),
  shouldUptake(shouldUptake),
  shouldReverse(shouldReverse)
{
  AddRequirements(intake);
}

// Called when the command is initially scheduled.
void ManualIntake::Initialize() {
  
}

// Called repeatedly when this Command is scheduled to run
void ManualIntake::Execute() {
  bool doIntake = shouldIntake();
  bool doUptake = shouldUptake();
  bool doReverse = shouldReverse();

  static bool changed = true;

  if (doUptake) {
    changed = true;
    intake->setMode(IntakeMode::Uptake);
  } else if (doReverse) {
    changed = true;
    intake->setMode(IntakeMode::Outtake);
  } else if (doIntake) {
    changed = true;
    intake->setMode(IntakeMode::Intake);
  } else {
    if (changed) {
      intake->setMode(IntakeMode::Stopped);
    }

    changed = false;
  }
}

// Called once the command ends or is interrupted.
void ManualIntake::End(bool interrupted) {}

// Returns true when the command should end.
bool ManualIntake::IsFinished() { return false; }
