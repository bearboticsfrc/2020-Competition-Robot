/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/automatic/AutoShoot.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/SubsystemBase.h>
#include "Robot.h"
#include <rev/CANSparkMax.h>
#include "subsystems/Shooter.h"
#include "subsystems/Intake.h"
#include "subsystems/Limelight.h"
#include <variant>

double powerFromAngle(double y) {
  return 0.000450892 * (y * y) - 0.0166284 * y + 1.00753;
}

AutoShoot::AutoShoot(Shooter *s, Intake *i) :
  shooter(s),
  intake(i)
{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({shooter, intake});
}

// Called when the command is initially scheduled.
void AutoShoot::Initialize() {
  frc::SmartDashboard::PutNumber("FoundY", 0.0);

  Limelight::setLights(true);
  acquired = false;
  failures = 0;
  successes = 0;
  speedSuccesses = 0;

  oldIntakeState = intake->getExtended();
  intake->setExtended(true);
}

// Called repeatedly when this Command is scheduled to run
void AutoShoot::Execute() {
  if (successes <= 5) {
    if (Limelight::targetFound()) {
      std::cout << "SUCCEED";
      ++successes;
      failures = 0;
    } else {
      std::cout << "FAIL";
      successes = 0;
      ++failures;
    }
  } else {
    // We have enough successes to acquire
    if (!acquired) {
      // Adjust power
      double foundY = Limelight::getY();
      frc::SmartDashboard::PutNumber("FoundY", foundY);
      shooter->setSpeed(powerFromAngle(foundY));
      acquired = true;
      startTime = std::chrono::steady_clock::now();
      shooter->shootAll();
    } 
  }
}
// Called once the command ends or is interrupted.
void AutoShoot::End(bool interrupted) {
  shooter->setSpeed(0.0);
  Limelight::setLights(false);

  intake->setExtended(oldIntakeState);
}

// Returns true when the command should end.
bool AutoShoot::IsFinished() {
  auto diff = std::chrono::steady_clock::now() - startTime;

  if (failures >= 20) {
    std::cout << "Too many failures\n";
    return true;
  }

  // TODO: Determine how long we need to spend shooting or 
  // find a better system to shoot all of the power cells
  if (acquired && diff > std::chrono::seconds(4)) {
    std::cout << "Ran for 3 seconds\n";
    return true;
  }

  return false;
}
