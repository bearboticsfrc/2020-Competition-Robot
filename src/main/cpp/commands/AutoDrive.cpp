/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoDrive.h"

#include <frc/trajectory/Trajectory.h>
#include <frc/trajectory/TrajectoryConfig.h>
#include <frc/trajectory/TrajectoryGenerator.h>
#include <frc/trajectory/TrajectoryUtil.h>
#include <frc/trajectory/constraint/DifferentialDriveVoltageConstraint.h>
#include <frc2/command/RamseteCommand.h>
#include "subsystems/Drivetrain.h"

frc::Trajectory generateTrajectory() {
  frc::Trajectory trajectory = frc::TrajectoryUtil::FromPathweaverJson("/home/lvuser/deploy/Default.wpilib.json");
  return trajectory;
}

frc::DifferentialDriveKinematics getKinematics() {
  return frc::DifferentialDriveKinematics { 12_in };
}

namespace constants {
  double KS = 0.0; // TODO
  double KV = 0.0; // TODO
  double KA = 0.0; // TODO

  double MAX_SPEED = 0.0; // TODO
  double MAX_ACCEL = 0.0; // TODO
}

std::unique_ptr<frc2::Command> getTrajectoryCommand(Drivetrain &drivetrain) {
  return std::unique_ptr<frc2::Command>(new frc2::RamseteCommand(
    generateTrajectory(),
    [&drivetrain]() { return drivetrain.GetPose(); },
    frc::RamseteController(
      2.0,
      0.6
    ),
    getKinematics(),
    [&drivetrain](units::meters_per_second_t left, units::meters_per_second_t right) { drivetrain.SetSpeeds(left, right); },
    { &drivetrain }
  ));
}

AutoDrive::AutoDrive() {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void AutoDrive::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AutoDrive::Execute() {}

void AutoDrive::End(bool interrupted) {}

bool AutoDrive::IsFinished() { return false; }