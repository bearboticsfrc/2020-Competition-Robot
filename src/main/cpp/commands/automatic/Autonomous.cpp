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
#include <frc2/command/WaitCommand.h>
#include <frc/geometry/Pose2d.h>
#include <frc/smartdashboard/SmartDashboard.h>


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
FriendlyTrench::FriendlyTrench(Drivetrain *drivetrain, Intake *intake, Arduino *arduino, Shooter *s) {
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
    AlignAngle(units::degree_t(186.0), drivetrain),
    frc2::InstantCommand{ [=] { intake->setMode(IntakeMode::Stopped); } },
    DriveDistance(drivetrain, units::foot_t(-7.0)),
    AlignAngle(units::degree_t(0.0), drivetrain),
    AlignAndShoot(drivetrain, s, intake)
  );
}

// TODO: Programmable delay
// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/latest/docs/software/commandbased/convenience-features.html
Barrel::Barrel(Drivetrain *drivetrain) {
  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());

  AddCommands(
    frc2::InstantCommand{ [=] { drivetrain->SetPose(generateTrajectoryBarrel().States()[0].pose); } },
    getTrajectoryCommandBarrel(*drivetrain)
  );
}

Slalom::Slalom(Drivetrain *drivetrain) {
  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());

  AddCommands(
    frc2::InstantCommand{ [=] { drivetrain->SetPose(generateTrajectorySlalom().States()[0].pose); } },
    getTrajectoryCommandSlalom(*drivetrain)
  );
}

Bounce::Bounce(Drivetrain *drivetrain) {
  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());

  AddCommands(
    frc2::InstantCommand{ [=] { drivetrain->SetPose(generateTrajectoryBounce1().States()[0].pose); } },
    getTrajectoryCommandBounce1(*drivetrain),
    frc2::InstantCommand{ [=] { drivetrain->SetPose(generateTrajectoryBounce2().States()[0].pose); } },
    getTrajectoryCommandBounce2(*drivetrain),
    frc2::InstantCommand{ [=] { drivetrain->SetPose(generateTrajectoryBounce3().States()[0].pose); } },
    getTrajectoryCommandBounce3(*drivetrain),
    frc2::InstantCommand{ [=] { drivetrain->SetPose(generateTrajectoryBounce4().States()[0].pose); } },
    getTrajectoryCommandBounce4(*drivetrain)
  );
}

EnemyTrench::EnemyTrench(Drivetrain *drivetrain, Intake *intake, Arduino *arduino, Shooter *shooter) {
  AddCommands(
    frc2::InstantCommand{ [=] { 
      drivetrain->SetPose(frc::Pose2d());
      intake->setExtended(true);
      intake->setMode(IntakeMode::Intake);
    } },
    frc2::WaitCommand(units::second_t(1)),
    // Drive into trench run
    DriveDistance(drivetrain, units::foot_t(9.75)),
    DriveDistance(drivetrain, units::foot_t(-1.0)),
    AlignAngle(units::degree_t(-30.0), drivetrain),
    DriveDistance(drivetrain, units::foot_t(2.0)),
    DriveDistance(drivetrain, units::foot_t(-8.0)),
    frc2::InstantCommand{ [=] { intake->setMode(IntakeMode::Stopped); } },
    AlignAngle(units::degree_t(135.0), drivetrain),
    AlignAndShoot(drivetrain, shooter, intake)
  );
}

SimpleAutonomous::SimpleAutonomous(Drivetrain *drivetrain, Intake *intake, Arduino *arduino, Shooter *shooter, bool forward) {
  units::foot_t distance;
  if (forward) {
    distance = units::foot_t(3.0);
  } else {
    distance = units::foot_t(-3.0);
  }

  AddCommands(
    frc2::WaitCommand(units::second_t(frc::SmartDashboard::GetNumber("Auto Delay", 0.0))),
    AlignAndShoot(drivetrain, shooter, intake),
    DriveDistance(drivetrain, distance)
  );
}
