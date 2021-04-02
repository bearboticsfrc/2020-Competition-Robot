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
#include <frc/geometry/Pose2d.h>


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

frc::Trajectory generateTrajectorySlalom() {
  frc::Trajectory trajectory = frc::TrajectoryUtil::FromPathweaverJson("/home/lvuser/deploy/2-6 Slalom Path.wpilib.json");
  return trajectory;
}

frc::Trajectory generateTrajectoryBounce1() {
  frc::Trajectory trajectory = frc::TrajectoryUtil::FromPathweaverJson("/home/lvuser/deploy/Bounce1.wpilib.json");
  return trajectory;
}

frc::Trajectory generateTrajectoryBounce2() {
  frc::Trajectory trajectory = frc::TrajectoryUtil::FromPathweaverJson("/home/lvuser/deploy/Bounce2.wpilib.json");
  return trajectory;
}

frc::Trajectory generateTrajectoryBounce3() {
  frc::Trajectory trajectory = frc::TrajectoryUtil::FromPathweaverJson("/home/lvuser/deploy/Bounce3.wpilib.json");
  return trajectory;
}

frc::Trajectory generateTrajectoryBounce4() {
  frc::Trajectory trajectory = frc::TrajectoryUtil::FromPathweaverJson("/home/lvuser/deploy/Bounce4.wpilib.json");
  return trajectory;
}

frc::Trajectory generateTrajectoryARed() {
  frc::Trajectory trajectory = frc::TrajectoryUtil::FromPathweaverJson("/home/lvuser/deploy/ARed.wpilib.json");
  return trajectory;
}


frc::Trajectory generateTrajectoryBRed() {
  frc::Trajectory trajectory = frc::TrajectoryUtil::FromPathweaverJson("/home/lvuser/deploy/BRed.wpilib.json");
  return trajectory;
}


frc::Trajectory generateTrajectoryABlue() {
  frc::Trajectory trajectory = frc::TrajectoryUtil::FromPathweaverJson("/home/lvuser/deploy/ABlue.wpilib.json");
  return trajectory;
}


frc::Trajectory generateTrajectoryBBlue() {
  frc::Trajectory trajectory = frc::TrajectoryUtil::FromPathweaverJson("/home/lvuser/deploy/BBlue.wpilib.json");
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

frc2::RamseteCommand getTrajectoryCommandSlalom(Drivetrain &drivetrain) {
  return getTrajectoryCommand(drivetrain, generateTrajectorySlalom());
}

// make trajectory command for each segment of the path
frc2::RamseteCommand getTrajectoryCommandBounce1(Drivetrain &drivetrain) {
  return getTrajectoryCommand(drivetrain, generateTrajectoryBounce1());
}

frc2::RamseteCommand getTrajectoryCommandBounce2(Drivetrain &drivetrain){
  return getTrajectoryCommand(drivetrain, generateTrajectoryBounce2());
}

frc2::RamseteCommand getTrajectoryCommandBounce3(Drivetrain &drivetrain) {
  return getTrajectoryCommand(drivetrain, generateTrajectoryBounce3());
}

frc2::RamseteCommand getTrajectoryCommandBounce4(Drivetrain &drivetrain){
  return getTrajectoryCommand(drivetrain, generateTrajectoryBounce4());
}

frc2::RamseteCommand getTrajectoryCommandARed(Drivetrain &drivetrain) {
  return getTrajectoryCommand(drivetrain, generateTrajectoryARed());
}

frc2::RamseteCommand getTrajectoryCommandBRed(Drivetrain &drivetrain) {
  return getTrajectoryCommand(drivetrain, generateTrajectoryBRed());
}

frc2::RamseteCommand getTrajectoryCommandABlue(Drivetrain &drivetrain) {
  return getTrajectoryCommand(drivetrain, generateTrajectoryABlue());
}

frc2::RamseteCommand getTrajectoryCommandBBlue(Drivetrain &drivetrain) {
  return getTrajectoryCommand(drivetrain, generateTrajectoryBBlue());
}


