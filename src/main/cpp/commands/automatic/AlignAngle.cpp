/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/automatic/AlignAngle.h"
#include "subsystems/Drivetrain.h"

AlignAngle::AlignAngle(units::degree_t target, Drivetrain *drivetrain) :
  drivetrain(drivetrain),
  target(target)
{
  AddRequirements(drivetrain);
}

AlignAngle::AlignAngle(units::degree_t *target, Drivetrain *drivetrain) :
  drivetrain(drivetrain),
  target2(target)
{
  AddRequirements(drivetrain);
}

// Called when the command is initially scheduled.
void AlignAngle::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AlignAngle::Execute() {
  units::degree_t t;
  if (target2 != nullptr) {
    t = *target2;
  } else {
    t = target;
  }

  if (doAlign(drivetrain, t)) {
    successes += 1;
  }
}

// Called once the command ends or is interrupted.
void AlignAngle::End(bool interrupted) {
  drivetrain->SetSpeed(0.0);
}

// Returns true when the command should end.
bool AlignAngle::IsFinished() { return successes >= 5; }

double mod(double f, double value) {
  return f - floor(f / value) * value;
}

bool doAlign(Drivetrain *drivetrain, units::degree_t target) {
  auto currentYaw = drivetrain->GetPose().Rotation().Degrees();

  auto rawAngleError = target - currentYaw;
  double angleError = mod(rawAngleError.to<double>() + 180.0, 360.0) - 180.0;

  double speed = angleError / 60.0;

  const double ANGLE_THRESHOLD = 1.0;
  const double MAX_SPEED = 0.3;


  if (speed > MAX_SPEED) {
    speed = MAX_SPEED;
  } else if (speed < -MAX_SPEED) {
    speed = -MAX_SPEED;
  }

  drivetrain->SetAllSpeed(speed, -speed);

  return std::abs(angleError) < ANGLE_THRESHOLD;
}