/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AlignTarget.h"
#include "subsystems/Limelight.h"
#include "subsystems/Drivetrain.h"

AlignTarget::AlignTarget(Drivetrain *drivetrain) :
  drivetrain(drivetrain)
{
  AddRequirements(drivetrain);
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void AlignTarget::Initialize() {
  Limelight::setLights(true);
}

// Called repeatedly when this Command is scheduled to run
void AlignTarget::Execute() {
  double x = Limelight::getX();
  drivetrain->SetAllSpeed(x / 30.0, -x / 30.0);
}

// Called once the command ends or is interrupted.
void AlignTarget::End(bool interrupted) {
  Limelight::setLights(false);
  drivetrain->SetAllSpeed(0.0, 0.0);
}

// Returns true when the command should end.
bool AlignTarget::IsFinished() {
  //return !Limelight::targetFound() || std::abs(Limelight::getX()) < 1.0;
  //return std::abs(Limelight::getX()) < 1.0;
  return false;
}
