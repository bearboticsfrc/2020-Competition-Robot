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

// 21.2   91%
// 16.8   90%
// 12.7   89%
// 11.3   87%
//  9.3   85%
//  7.0   85%
//  5.5   87%
//  4.7   89%
//  2.3   90%
//  2.3   94.5%
//  0.5   97%
// -0.2   99%

/*double powerFromAngle(double y) {
  return 0.000450892 * (y * y) - 0.0166284 * y + 1.00753;
}*/

double powerFromAngle(double y) {
  return 
    1.865e-7 * std::pow(y, 6) +
    -0.00000941972639267 * std::pow(y, 5) +
     0.000154104299104 * std::pow(y, 4) +
    -0.000812733158646 * std::pow(y, 3) +
     0.000707164302267 * std::pow(y, 2) +
    -0.0174193883624 * y +
     0.983779942723;
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

      acquired = true;
      startTime = std::chrono::steady_clock::now();

      // Adjust power
      double foundY = Limelight::getY();
      double power = powerFromAngle(foundY) + 0.01;
      intake->setExtended(false);
      shooter->shoot(power);

      

      //shooter->shoot(frc::SmartDashboard::GetNumber("ShootSpeed", 1.0));

      frc::SmartDashboard::PutNumber("FoundY", foundY);
    } 
  }
}
// Called once the command ends or is interrupted.
void AutoShoot::End(bool interrupted) {
  Limelight::setLights(false);
}

// Returns true when the command should end.
bool AutoShoot::IsFinished() {
  if (failures >= 20) {
    std::cout << "Too many failures\n";
    return true;
  }

  if (acquired && shooter->IsStopped()) {
    return true;
  }

  return false;
}
