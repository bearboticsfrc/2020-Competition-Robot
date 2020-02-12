/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/automatic/AlignTarget.h"
#include "commands/automatic/AlignAngle.h"
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
  successes = 0;
  fails = 0;
}

// Called repeatedly when this Command is scheduled to run
void AlignTarget::Execute() {
  if (Limelight::targetFound()) {
    fails = 0;

    auto lastTargetYaw = drivetrain->GetLastPose().Rotation().Degrees() + units::degree_t(Limelight::getX());

    if(doAlign(drivetrain, lastTargetYaw)) {
      successes += 1;
    }
  } else {
    drivetrain->SetAllSpeed(0.0, 0.0);
    fails += 1;
    successes = 0;
  }
}

// Called once the command ends or is interrupted.
void AlignTarget::End(bool interrupted) {
  Limelight::setLights(false);
  drivetrain->SetAllSpeed(0.0, 0.0);
}

// Returns true when the command should end.
bool AlignTarget::IsFinished() {
  return successes >= 5 || fails >= 5;
}
