/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/manual/ManualShooter.h"
#include "Robot.h"
#include <rev/CANSparkMax.h>
#include "subsystems/Shooter.h"
#include <frc2/command/SubsystemBase.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "Util.h"

ManualShooter::ManualShooter(Shooter *s, std::function<bool()> shouldShoot) :
  shooter(s),
  shouldShoot(shouldShoot)
{
  initDashboardValue("ShootSpeed", 0.1);
  AddRequirements({shooter});
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void ManualShooter::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ManualShooter::Execute() {
  bool shoot = shouldShoot();

  if (shoot) {
    shooter->shoot(frc::SmartDashboard::GetNumber("ShootSpeed", 0));
  }
}

// Called once the command ends or is interrupted.
void ManualShooter::End(bool interrupted) {}

// Returns true when the command should end.
bool ManualShooter::IsFinished() { return false; }
