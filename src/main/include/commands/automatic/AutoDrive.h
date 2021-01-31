/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/trajectory/Trajectory.h>
#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <memory>

class Drivetrain;

namespace frc2 {
  class RamseteCommand;
}

frc2::RamseteCommand getTrajectoryCommand(Drivetrain &drivetrain);
frc2::RamseteCommand getTrajectoryCommand2(Drivetrain &drivetrain);
frc2::RamseteCommand getTrajectoryCommandBarrel(Drivetrain &drivetrain);
frc2::RamseteCommand getTrajectoryCommandStraightLine(Drivetrain &drivetrain);
frc2::RamseteCommand getTrajectoryCommandSlalom(Drivetrain &drivetrain);
frc2::RamseteCommand getTrajectoryCommandBounce(Drivetrain &drivetrain);

frc::Trajectory generateTrajectory();
frc::Trajectory generateTrajectory2();
frc::Trajectory generateTrajectoryBarrel();
frc::Trajectory generateTrajectoryStraightLine();
frc::Trajectory generateTrajectorySlalom();
frc::Trajectory generateTrajectoryBounce();