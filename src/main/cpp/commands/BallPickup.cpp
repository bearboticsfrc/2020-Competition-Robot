/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/BallPickup.h"
#include "subsystems/Arduino.h"
#include "subsystems/Drivetrain.h"
#include "subsystems/Intake.h"

BallPickup::BallPickup(Drivetrain *drivetrain, Intake *intake, Arduino *arduino) :
  drivetrain(drivetrain),
  intake(intake),
  arduino(arduino)
{
  AddRequirements({ drivetrain, intake });
}

// Called when the command is initially scheduled.
void BallPickup::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void BallPickup::Execute() {
  auto [data, valid] = arduino->readData();
  if (valid) {
    if (!(data.x == 0 && data.y == 0 && data.width == 0 && data.height == 0)) {
      intake->setIntake(true);

      // Follow the ball!
      // TODO: Determine what the center of the camera vision is
      const double CENTER = 300.0;

      // TODO: Should this be swapped around
      double angleError = data.x - CENTER;

      // TODO: Pick a proper number to divide this by
      double ballDistance = 1000.0 / (data.width * data.height);

      // TODO: Maybe adjust how sensitive this is
      drivetrain->SetAllSpeed(ballDistance + angleError, ballDistance - angleError);
    }
  }

  drivetrain->SetAllSpeed(0.0, 0.0);
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


