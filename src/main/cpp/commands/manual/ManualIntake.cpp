/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/manual/ManualIntake.h"
#include "subsystems/Intake.h"

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
  intake->setExtended(true);
}

// Called repeatedly when this Command is scheduled to run
void ManualIntake::Execute() {
  bool doIntake = shouldIntake();
  bool doUptake = shouldUptake();
  bool doReverse = shouldReverse();

  if (doUptake) {
    intake->setUptake(true);
  } else if (doReverse) {
    intake->setOuttake(true);
  } else {
    intake->setIntake(doIntake);
  }
}

// Called once the command ends or is interrupted.
void ManualIntake::End(bool interrupted) {}

// Returns true when the command should end.
bool ManualIntake::IsFinished() { return false; }
