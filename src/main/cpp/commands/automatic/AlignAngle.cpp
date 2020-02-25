/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/automatic/AlignAngle.h"
#include "subsystems/Drivetrain.h"

double Aligner::getAngle() const {
  double angle = drivetrain->GetPose().Rotation().Degrees().to<double>();
  return std::fmod(std::fmod(angle, 360.0) + 360.0, 360.0);
}

void Aligner::setOutput(double output) {
  drivetrain->SetSpeeds(output, -output);
}

void Aligner::update() {
  setOutput(Calculate(getAngle()));
}

Aligner::Aligner(Drivetrain *drivetrain) :
  frc2::PIDController(0.01, 0.0, 0.0),
  drivetrain(drivetrain)
{
  EnableContinuousInput(0.0, 360.0);
  SetTolerance(0.5);
  Reset();
}

AlignAngle::AlignAngle(units::degree_t target, Drivetrain *drivetrain) :
  drivetrain(drivetrain),
  target(target),
  aligner(drivetrain)
{
  AddRequirements(drivetrain);
}

AlignAngle::AlignAngle(units::degree_t *target, Drivetrain *drivetrain) :
  drivetrain(drivetrain),
  target2(target),
  aligner(drivetrain)
{
  AddRequirements(drivetrain);
}

// Called when the command is initially scheduled.
void AlignAngle::Initialize() {
  aligner.Reset();
  successes = 0;
}

// Called repeatedly when this Command is scheduled to run
void AlignAngle::Execute() {
  units::degree_t t;
  if (target2 != nullptr) {
    t = *target2;
  } else {
    t = target;
  }

  aligner.SetSetpoint(t.to<double>());
  aligner.update();

  if (aligner.AtSetpoint()) {
    successes += 1;
  }
}

// Called once the command ends or is interrupted.
void AlignAngle::End(bool interrupted) {
  drivetrain->SetSpeeds(0.0, 0.0);
}

// Returns true when the command should end.
bool AlignAngle::IsFinished() {
  return successes >= 5;
}