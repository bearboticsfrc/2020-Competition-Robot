// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/automatic/BallTrack.h"
#include "commands/automatic/AutoDrive.h"
#include <frc/trajectory/TrajectoryConfig.h>
#include <frc/trajectory/TrajectoryGenerator.h>
#include <frc/trajectory/TrajectoryUtil.h>
#include <frc/trajectory/constraint/DifferentialDriveVoltageConstraint.h>
#include <frc/kinematics/DifferentialDriveKinematics.h>
#include <frc2/command/RamseteCommand.h>
#include "subsystems/Drivetrain.h"
#include <frc2/command/InstantCommand.h>
#include <frc/geometry/Pose2d.h>

BallTrack::BallTrack(Arduino *arduino, Drivetrain *drivetrain) 
 : m_arduino{arduino},m_drivetrain{drivetrain}
 {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_drivetrain);
  
}



// Called when the command is initially scheduled.
void BallTrack::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void BallTrack::Execute() {
  double ballX = 0; 
  double ballWidth = 0;
  
  auto data = m_arduino->readData();
  if (data.second && data.first.size() != 0){
      for (SensorFrame frame : data.first) {
        ballX = frame.x;
        ballWidth = frame.width;
      }
      double turn = (ballX - 150) / 250;
      double speed = 0.0;

      if (turn > 150.0 / 500.0)
      {
        turn = 150.0 / 500.0;
      }

      if (turn < -150.0 / 500.0)
      {
        turn = -150.0 / 500.0;
      }

      if (abs(ballX - 150) < 30 && ballWidth > 20) 
      {
        speed = 5 / ballWidth;
      }

      
      m_drivetrain->SetSpeeds(speed + turn, speed -turn);

  } else {
    m_drivetrain->SetSpeeds(0.0,0.0);
  }

}
// Called once the command ends or is interrupted.
void BallTrack::End(bool interrupted) {}

// Returns true when the command should end.
bool BallTrack::IsFinished() {
  return false;
}
/*
ARed::ARed(Drivetrain *drivetrain) {
  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());

  AddCommands(
    frc2::InstantCommand{ [=] { drivetrain->SetPose(generateTrajectoryARed().States()[0].pose); } },
    getTrajectoryCommandARed(*drivetrain)
    // TODO: Drive back
  );
}

BRed::BRed(Drivetrain *drivetrain) {
  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());

  AddCommands(
    frc2::InstantCommand{ [=] { drivetrain->SetPose(generateTrajectoryBRed().States()[0].pose); } },
    getTrajectoryCommandBRed(*drivetrain)
    // TODO: Drive back
  );
}

ABlue::ABlue(Drivetrain *drivetrain) {
  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());

  AddCommands(
    frc2::InstantCommand{ [=] { drivetrain->SetPose(generateTrajectoryABlue().States()[0].pose); } },
    getTrajectoryCommandABlue(*drivetrain)
    // TODO: Drive back
  );
}

BBlue::BBlue(Drivetrain *drivetrain) {
  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());

  AddCommands(
    frc2::InstantCommand{ [=] { drivetrain->SetPose(generateTrajectoryBBlue().States()[0].pose); } },
    getTrajectoryCommandBBlue(*drivetrain)
    // TODO: Drive back
  );
} */