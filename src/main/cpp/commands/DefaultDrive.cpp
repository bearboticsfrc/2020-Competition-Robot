/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DefaultDrive.h"
#include "Robot.h"

DefaultDrive::DefaultDrive(Drivetrain *drive, frc::Joystick *joystick) :
  drivetrain(drive),
  joystick(joystick)
{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({ drive });
}

// Called when the command is initially scheduled.
void DefaultDrive::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void DefaultDrive::Execute() {
  double forward = joystick->GetY();
  double turn = -joystick->GetZ();

  double leftSpeed = forward + turn;
  double rightSpeed = forward - turn;

  drivetrain->SetAllSpeed(leftSpeed, rightSpeed);
}

// Called once the command ends or is interrupted.
void DefaultDrive::End(bool interrupted) {}

// Returns true when the command should end.
bool DefaultDrive::IsFinished() { return false; }
