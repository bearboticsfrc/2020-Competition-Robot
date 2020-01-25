/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>
#include <frc2/command/SequentialCommandGroup.h>
#include "commands/BallPickup.h"
#include "commands/AutoDrive.h"

class Autonomous
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 Autonomous> {
 public:
  Autonomous(Drivetrain *drivetrain, Intake *intake, Arduino *arduino);

  private:
  Arduino *arduino;
  Drivetrain *drivetrain;
  Intake *intake;
};


