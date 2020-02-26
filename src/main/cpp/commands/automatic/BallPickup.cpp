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
  failures = 0;
  leftSpeed = 0.0;
  rightSpeed = 0.0;
  intake->setExtended(true);
  intake->setMode(IntakeMode::Intake);
}

std::pair<double, double> getTargetSpeeds(SensorFrame data) {
  const double CENTER = 160.0;
  const double ANGLE_GAIN = 0.002;
  const double AREA_GAIN = 100.0;

  double area = data.width * data.height;
  double angleError = data.x - CENTER;

  double turnSpeed = angleError * ANGLE_GAIN;
  double forwardSpeed = area / AREA_GAIN;

  return { forwardSpeed + turnSpeed, forwardSpeed - turnSpeed };
}

std::pair<double, double> BallPickup::getTargetSpeeds() {
  auto [all_data, valid] = arduino->readData();

  if (valid && all_data.size() > 0) {
    auto data = all_data[0];
    if (!(data.x == 0 && data.y == 0 && data.width == 0 && data.height == 0)) {
      failures = 0;
      return ::getTargetSpeeds(data);
    }
  } else {
    std::cout << "BALL TRACKING INFORMATION NOT VALID\n";
  }

  ++failures;
  return { 0.0, 0.0 };
}

// Called repeatedly when this Command is scheduled to run
void BallPickup::Execute() {
  const double MAX_CHANGE = 0.01;

  auto [leftTargetSpeed, rightTargetSpeed] = getTargetSpeeds();

  double leftDiff = leftTargetSpeed - leftSpeed;
  double rightDiff = rightTargetSpeed - rightSpeed;

  double leftChange = std::clamp(leftDiff, -MAX_CHANGE, MAX_CHANGE);
  double rightChange = std::clamp(rightDiff, -MAX_CHANGE, MAX_CHANGE);

  leftSpeed += leftChange;
  rightSpeed += rightChange;

  drivetrain->SetSpeeds(leftSpeed, rightSpeed);
}

// Called once the command ends or is interrupted.
void BallPickup::End(bool interrupted) {
  intake->setMode(IntakeMode::Stopped);
  drivetrain->SetSpeeds(0.0, 0.0);
}

// Returns true when the command should end.
bool BallPickup::IsFinished() {
  if (failures >= 20) {
    std::cout << "Too many failures in ball pickup command\n";
    return true;
  }

  // TODO: Figure out a success condition (maybe)
  return false;
}


