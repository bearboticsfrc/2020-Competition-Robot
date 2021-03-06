/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/manual/ManualDrive.h"
#include "Robot.h"
#include "units_include.h"

ManualDrive::ManualDrive(Drivetrain *drive, Input *in) :
  drivetrain(drive),
  input(in),
  useConstantSpeed(false)
{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({ drive });
}

// Called when the command is initially scheduled.
void ManualDrive::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ManualDrive::Execute() {
  //double forward = -input->GetY();
  double forward = -input->GetY();

  if (useConstantSpeed == true) {
    forward = constantSpeed;
  }
  
  double turn = 0.4 * input->GetX();

  double leftSpeed = forward + turn;
  double rightSpeed = forward - turn;

  drivetrain->SetSpeeds(leftSpeed, rightSpeed);
}

// Called once the command ends or is interrupted.
void ManualDrive::End(bool interrupted) {}

// Returns true when the command should end.
bool ManualDrive::IsFinished() { return false; }

void ManualDrive::setConstantSpeed(double speed) {
  useConstantSpeed = true;
  constantSpeed = speed;
}
