/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/automatic/SortaDrive.h"

SortaDrive::SortaDrive(Drivetrain *drivetrain, double seconds) :
  backwards(true),
  max_counts(seconds * 50.0),
  drivetrain(drivetrain)
{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(drivetrain);
}

SortaDrive::SortaDrive(Drivetrain *drivetrain, double seconds, bool backwards) :
  backwards(backwards),
  max_counts(seconds * 50.0),
  drivetrain(drivetrain)
{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(drivetrain);
}

// Called when the command is initially scheduled.
void SortaDrive::Initialize() {
  counts = 0;
}

// Called repeatedly when this Command is scheduled to run
void SortaDrive::Execute() {
  ++counts;
  if (backwards) {
    drivetrain->SetSpeeds(-0.1, -0.1);
  } else {
    drivetrain->SetSpeeds(0.1, 0.1);
  }
}

// Called once the command ends or is interrupted.
void SortaDrive::End(bool interrupted) {
  drivetrain->SetSpeeds(0.0, 0.0);
}

// Returns true when the command should end.
bool SortaDrive::IsFinished() { return counts >= max_counts; }
