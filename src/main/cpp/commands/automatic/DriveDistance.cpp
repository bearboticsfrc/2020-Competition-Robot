/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/automatic/DriveDistance.h"
#include "subsystems/Drivetrain.h"

DriveDistance::DriveDistance(Drivetrain *drivetrain, units::meter_t distance) :
  drivetrain(drivetrain),
  distance(distance)
{
  AddRequirements(drivetrain);
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void DriveDistance::Initialize() {
  angle = drivetrain->GetPose().Rotation().Degrees();
  startPosition = drivetrain->GetAverageEncoder();
  waiter = 0;
}

double DriveDistance::ForwardSpeed() {
  auto fromStart = std::abs((drivetrain->GetAverageEncoder() - startPosition).to<double>());
  auto fromEnd = std::abs(fromStart - std::abs(distance.to<double>()));

  const double MAIN_SPEED = 0.6;
  const double RAMP_DISTANCE = 1.0;
  const double MIN_SPEED = 0.2;

  if (fromStart < RAMP_DISTANCE && fromEnd < RAMP_DISTANCE) {
    return MIN_SPEED;
  } else if (fromStart < RAMP_DISTANCE) {
    return MIN_SPEED + (MAIN_SPEED - MIN_SPEED) * fromStart / RAMP_DISTANCE;
  } else if (fromEnd < RAMP_DISTANCE) {
    return MAIN_SPEED - (MAIN_SPEED - MIN_SPEED) * (RAMP_DISTANCE - fromEnd) / RAMP_DISTANCE;
  } else {
    return MAIN_SPEED;
  }
}

// Called repeatedly when this Command is scheduled to run
void DriveDistance::Execute() {
  units::degree_t current = drivetrain->GetPose().Rotation().Degrees();
  
  double diff = (angle - current).to<double>();
  diff -= floor((diff + 180.0) / 360.0) * 360.0;

  const double FORWARD_SPEED = ForwardSpeed();
  const double ANGLE_GAIN = 0.01;

  double angleSpeed = diff * ANGLE_GAIN;

  if (distance.to<double>() > 0.0) {
    drivetrain->SetSpeeds(-angleSpeed + FORWARD_SPEED, angleSpeed + FORWARD_SPEED);
  } else {
    drivetrain->SetSpeeds(-angleSpeed - FORWARD_SPEED, angleSpeed - FORWARD_SPEED);
  }

  ++waiter;
}

// Called once the command ends or is interrupted.
void DriveDistance::End(bool interrupted) {
  drivetrain->SetSpeed(0.0);
}

// Returns true when the command should end.
bool DriveDistance::IsFinished() {
  auto driven = drivetrain->GetAverageEncoder() - startPosition;

  return waiter > 5 && std::abs(driven.to<double>()) > std::abs(distance.to<double>());
}
