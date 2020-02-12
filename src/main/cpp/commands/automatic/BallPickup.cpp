/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/automatic/BallPickup.h"
#include "subsystems/Arduino.h"
#include "subsystems/Drivetrain.h"
#include "subsystems/Intake.h"
#include <frc/smartdashboard/SmartDashboard.h>

BallPickup::BallPickup(Drivetrain *drivetrain, Intake *intake, Arduino *arduino) :
  drivetrain(drivetrain),
  intake(intake),
  arduino(arduino)
{
  AddRequirements({ drivetrain, intake });
}

// Called when the command is initially scheduled.
void BallPickup::Initialize() {
  leftSpeed = 0.0;
  rightSpeed = 0.0;
  intake->setExtended(true);
  intake->setIntake(true);
}

std::pair<double, double> BallPickup::getTargetSpeeds() {
  auto [all_data, valid] = arduino->readData();
  if (valid && all_data.size() > 0) {
    auto data = all_data[0];
    if (!(data.x == 0 && data.y == 0 && data.width == 0 && data.height == 0)) {
      intake->setIntake(true);

      const double CENTER = 160.0;

      double angleError = data.x - CENTER;
      angleError /= 500.0;

      frc::SmartDashboard::PutNumber("Area", data.width * data.height);

      double ballDistance = 100.0 / (data.width * data.height);

      return { ballDistance + angleError, ballDistance - angleError };
    } else {
      return { 0.0, 0.0 };
    }
  } else {
    std::cout << "BALL TRACKING INFORMATION NOT VALID\n";
    return { 0.0, 0.0 };
  }
}

// Called repeatedly when this Command is scheduled to run
void BallPickup::Execute() {
  auto [leftTargetSpeed, rightTargetSpeed] = getTargetSpeeds();

  double leftDiff = leftTargetSpeed - leftSpeed;
  double rightDiff = rightTargetSpeed - rightSpeed;

  const double MAX_CHANGE = 0.01;

  double leftChange = std::clamp(leftDiff, -MAX_CHANGE, MAX_CHANGE);
  double rightChange = std::clamp(rightDiff, -MAX_CHANGE, MAX_CHANGE);

  leftSpeed += leftChange;
  rightSpeed += rightChange;

  drivetrain->SetAllSpeed(leftSpeed, rightSpeed);
}

// Called once the command ends or is interrupted.
void BallPickup::End(bool interrupted) {
  intake->setIntake(false);
  drivetrain->SetAllSpeed(0.0, 0.0);
}

// Returns true when the command should end.
bool BallPickup::IsFinished() {
  // TODO: End it properly
  return false;
}


