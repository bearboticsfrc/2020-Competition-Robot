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
#include "subsystems/Drivetrain.h"
#include <frc2/command/RamseteCommand.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/ParallelRaceGroup.h>


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

  AddCommands(
    frc2::InstantCommand{ [=] { drivetrain->SetPose(generateTrajectory2().States()[0].pose); } },
    AlignAndShoot(drivetrain, s, intake),
    getTrajectoryCommand2(*drivetrain),
    BallPickup(drivetrain, intake, arduino).WithTimeout(std::chrono::seconds(5))
    // TODO: Drive back
    //AlignAndShoot(drivetrain, s, intake),
  );
}
