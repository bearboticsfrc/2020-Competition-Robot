/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/automatic/AutoDrive.h"

#include <frc/trajectory/TrajectoryConfig.h>
#include <frc/trajectory/TrajectoryGenerator.h>
#include <frc/trajectory/TrajectoryUtil.h>
#include <frc/trajectory/constraint/DifferentialDriveVoltageConstraint.h>
#include <frc/kinematics/DifferentialDriveKinematics.h>
#include <frc2/command/RamseteCommand.h>
#include "subsystems/Drivetrain.h"

frc::Trajectory generateTrajectory() {
  frc::Trajectory trajectory = frc::TrajectoryUtil::FromPathweaverJson("/home/lvuser/deploy/Unnamed.wpilib.json");
  return trajectory;
}

frc::Trajectory generateTrajectory2() {
  frc::Trajectory trajectory = frc::TrajectoryUtil::FromPathweaverJson("/home/lvuser/deploy/Unnamed_0.wpilib.json");
  return trajectory;
}

frc::Trajectory generateTrajectoryBarrel() {
  frc::Trajectory trajectory = frc::TrajectoryUtil::FromPathweaverJson("/home/lvuser/deploy/2-5 Barrel Racing Path.wpilib.json");
  return trajectory;
}

frc::Trajectory generateTrajectoryStraightLine() {
  frc::Trajectory trajectory = frc::TrajectoryUtil::FromPathweaverJson("/home/lvuser/deploy/StraightLine.wpilib.json");
  return trajectory;
}

frc::DifferentialDriveKinematics getKinematics() {
  return frc::DifferentialDriveKinematics { 24_in };
}

frc2::RamseteCommand getTrajectoryCommand(Drivetrain &drivetrain, frc::Trajectory trajectory) {
  return frc2::RamseteCommand(
    trajectory,
    [&drivetrain]() { return drivetrain.GetPose(); },
    frc::RamseteController(
      2.0,
      0.6
    ),
    getKinematics(),
    [&drivetrain](units::meters_per_second_t left, units::meters_per_second_t right) { drivetrain.SetSpeeds(left, right); },
    { &drivetrain }
  );
}

frc2::RamseteCommand getTrajectoryCommand(Drivetrain &drivetrain) {
  return getTrajectoryCommand(drivetrain, generateTrajectory());
}

frc2::RamseteCommand getTrajectoryCommand2(Drivetrain &drivetrain) {
  return getTrajectoryCommand(drivetrain, generateTrajectory2());
}

frc2::RamseteCommand getTrajectoryCommandBarrel(Drivetrain &drivetrain) {
  return getTrajectoryCommand(drivetrain, generateTrajectoryBarrel());
}

frc2::RamseteCommand getTrajectoryCommandStraightLine(Drivetrain &drivetrain) {
  return getTrajectoryCommand(drivetrain, generateTrajectoryStraightLine());
}