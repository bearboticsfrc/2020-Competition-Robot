/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/automatic/Autonomous.h"
#include "commands/automatic/BallPickup.h"
#include "commands/automatic/AutoDrive.h"
#include "commands/automatic/AlignAndShoot.h"
#include "commands/automatic/AlignAngle.h"
#include "commands/automatic/DriveDistance.h"
#include "subsystems/Intake.h"
#include "subsystems/Drivetrain.h"
#include <frc2/command/RamseteCommand.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/ParallelRaceGroup.h>
#include <frc/geometry/Pose2d.h>


// TODO: Programmable delay
// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/latest/docs/software/commandbased/convenience-features.html
Autonomous::Autonomous(Drivetrain *drivetrain, Intake *intake, Arduino *arduino, Shooter *s) {
  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());

  AddCommands(
    frc2::InstantCommand{ [=] { drivetrain->SetPose(generateTrajectory().States()[0].pose); } },
    AlignAndShoot(drivetrain, s, intake),
    getTrajectoryCommand(*drivetrain),
    BallPickup(drivetrain, intake, arduino).WithTimeout(std::chrono::seconds(5))
    // TODO: Drive back
    //AlignAndShoot(drivetrain, s, intake),
  );
}

// TODO: Programmable delay
// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/latest/docs/software/commandbased/convenience-features.html
Autonomous2::Autonomous2(Drivetrain *drivetrain, Intake *intake, Arduino *arduino, Shooter *s) {
  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());

  /*AddCommands(
    frc2::InstantCommand{ [=] { drivetrain->SetPose(generateTrajectory2().States()[0].pose); } },
    AlignAndShoot(drivetrain, s, intake),
    frc2::InstantCommand{ [=] { intake->setMode(IntakeMode::Intake); } },
    getTrajectoryCommand2(*drivetrain)
    frc2::InstantCommand{ [=] { intake->setMode(IntakeMode::Stopped); } }
    // TODO: This, Drive back
    //BallPickup(drivetrain, intake, arduino).WithTimeout(std::chrono::seconds(5))
    //AlignAndShoot(drivetrain, s, intake),
  );*/

  AddCommands(
    frc2::InstantCommand{ [=] { drivetrain->SetPose(frc::Pose2d()); } },
    AlignAndShoot(drivetrain, s, intake),
    AlignAngle(units::degree_t(181.0), drivetrain),
    frc2::InstantCommand{ [=] { intake->setMode(IntakeMode::Intake); } },
    DriveDistance(drivetrain, units::foot_t(13.0)),
    frc2::InstantCommand{ [=] { intake->setMode(IntakeMode::Stopped); } },
    DriveDistance(drivetrain, units::foot_t(-5.0)),
    AlignAngle(units::degree_t(90.0), drivetrain),
    AlignAngle(units::degree_t(20.0), drivetrain),
    AlignAndShoot(drivetrain, s, intake)
  );
}
