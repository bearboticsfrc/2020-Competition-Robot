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
  successes = 0;
  fails = 0;
}

// Called repeatedly when this Command is scheduled to run
void AlignTarget::Execute() {
  if (Limelight::targetFound()) {
    fails = 0;

    double x = Limelight::getX();
    double lastTargetYaw = drivetrain->GetLastPose().Rotation().Degrees().to<double>() + x;
    double currentYaw = drivetrain->GetPose().Rotation().Degrees().to<double>();
    double angleError = lastTargetYaw - currentYaw;
    double speed = angleError / 40.0;

    const double ANGLE_THRESHOLD = 1.0;
    const double MAX_SPEED = 0.3;

    if (std::abs(angleError) < ANGLE_THRESHOLD) {
      successes += 1;
    }

    if (speed > MAX_SPEED) {
      speed = MAX_SPEED;
    } else if (speed < -MAX_SPEED) {
      speed = -MAX_SPEED;
    }

    drivetrain->SetAllSpeed(speed, -speed);
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
