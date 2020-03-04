/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/manual/ManualClimb.h"
#include "subsystems/Climber.h"
#include "Input.h"

ManualClimb::ManualClimb(Climber *climber, Input *input) :
  climber(climber),
  input(input)
{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(climber);
}

// Called when the command is initially scheduled.
void ManualClimb::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ManualClimb::Execute() {
  climber->SetSpeed(input->GetClimbSpeed());
}

// Called once the command ends or is interrupted.
void ManualClimb::End(bool interrupted) {
  climber->SetSpeed(0.0);
}

// Returns true when the command should end.
bool ManualClimb::IsFinished() { return false; }
