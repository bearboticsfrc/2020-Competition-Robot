/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoShoot.h"
#include <frc2/command/SubsystemBase.h>
#include "Robot.h"
#include <rev/CANSparkMax.h>

AutoShoot::AutoShoot() {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void AutoShoot::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AutoShoot::Execute() {}

// Called once the command ends or is interrupted.
void AutoShoot::End(bool interrupted) {}

// Returns true when the command should end.
bool AutoShoot::IsFinished() { return false; }
