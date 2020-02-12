/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/automatic/AutoShoot.h"
#include <frc2/command/SubsystemBase.h>
#include "Robot.h"
#include <rev/CANSparkMax.h>
#include "subsystems/Shooter.h"
#include "subsystems/Limelight.h"

AutoShoot::AutoShoot(Shooter *s) :
shooter(s)

 {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(shooter);
}

// Called when the command is initially scheduled.
void AutoShoot::Initialize() {
  Limelight::setLights(true);

  startTime = std::chrono::steady_clock::now();
}

// Called repeatedly when this Command is scheduled to run
void AutoShoot::Execute() {
  if (successes <= 5) {
    if (Limelight::targetFound()) {
      ++successes;
      failures = 0;
    } else {
      successes = 0;
      ++failures;
    }
  } else if (!acquired) {
    shooter->setDistance(Limelight::getDistance());
    acquired = true;
    Limelight::setLights(false);
  }

  shooter->shootOne();
}
// Called once the command ends or is interrupted.
void AutoShoot::End(bool interrupted) {
  shooter->setSpeed(0.0);
  Limelight::setLights(false);
}

// Returns true when the command should end.
bool AutoShoot::IsFinished() {
  auto diff = std::chrono::steady_clock::now() - startTime;

  // TODO: Determine how long we need to spend shooting or 
  // find a better system to shoot all of the power cells
  return diff > std::chrono::seconds(5) || failures >= 5;
}
