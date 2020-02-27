/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/automatic/AlignAndShoot.h"
#include "commands/automatic/AlignTarget.h"
#include "commands/automatic/AutoShoot.h"
#include "subsystems/Shooter.h"
#include <frc2/command/WaitCommand.h>
#include <frc2/command/ConditionalCommand.h>
#include <frc2/command/InstantCommand.h>
#include "subsystems/Intake.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/latest/docs/software/commandbased/convenience-features.html
AlignAndShoot::AlignAndShoot(Drivetrain *drivetrain, Shooter *shooter, Intake *intake) {
  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());
  AddCommands(
    frc2::ConditionalCommand(
      std::unique_ptr<frc2::Command>(new frc2::InstantCommand([]{})),
      std::unique_ptr<frc2::Command>(new frc2::WaitCommand(std::chrono::seconds(1))),
      [=] { return intake->getExtended(); }
    ),
    frc2::InstantCommand([=] { shooter->shoot(1.0, [] { return false; }); }),
    AlignTarget(drivetrain, intake),
    AutoShoot(shooter, intake)
    );
} 