/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"
#include "commands/automatic/AutoDrive.h"
#include <frc2/command/InstantCommand.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/GenericHID.h>
#include <iostream>

const int GYRO_ID = 10;

RobotContainer::RobotContainer() :
  /* --- Sensors --- */
  m_gyro(GYRO_ID),
  /* --- Subsystems --- */
  m_drivetrain(&m_gyro),
  m_intake(&m_hopper),
  m_shooter(&m_hopper),
  /* --- Commands --- */
  m_defaultDrive(&m_drivetrain, &m_input),
  m_manualShooter(&m_shooter, m_input.ManualShootButton()),
  m_manualIntake(&m_intake, m_input.RunIntakeButton(), m_input.RunUptakeButton(), m_input.ReverseIntakeButton()),
  m_alignTarget(&m_drivetrain),
  m_ballPickup(&m_drivetrain, &m_intake, &m_arduino),
  m_showColors(&m_colorSensor),
  m_autonomous(&m_drivetrain, &m_intake, &m_arduino, &m_shooter),
  m_autonomous2(&m_drivetrain, &m_shooter, &m_intake),
  m_autoShoot(&m_shooter, &m_intake),
  m_movableAutonomous(&m_drivetrain, &m_shooter, &m_intake),
  m_alignAndShoot(&m_drivetrain, &m_shooter, &m_intake),
  /* --- Buttons --- */
  m_alignAndShootButton(m_input.AutoShootButton()),
  m_toggleIntakeButton(m_input.ToggleIntakePositionButton()),
  m_reverseIntakeButton(m_input.ReverseIntakeButton()),
  camera(frc::CameraServer::GetInstance()->StartAutomaticCapture())
{
  std::cout << "Constructor\n";
  std::cout.flush();
  // Initialize all of your commands and subsystems here
  m_gyro.SetYaw(0.0);

  // Configure the button bindings
  ConfigureButtonBindings();

  frc::SmartDashboard::PutData("Align Target", &m_alignTarget);
  frc::SmartDashboard::PutData("Ball Pickup", &m_ballPickup);
  frc::SmartDashboard::PutData("Auto shoot", &m_autoShoot);
}

void RobotContainer::ConfigureButtonBindings() {
  m_alignAndShootButton.WhenPressed(m_alignAndShoot);
  m_toggleIntakeButton.WhenPressed(frc2::InstantCommand{ [this] { m_intake.setExtended(!m_intake.getExtended()); } });
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // TODO: Maybe use SelectCommand?
  switch (choosers.autonomousChoice()) {
    case AutonomousChoice::Disabled:
      return nullptr;
    case AutonomousChoice::Default:
      return &m_autonomous;
    case AutonomousChoice::Default2:
      return &m_autonomous2;
    case AutonomousChoice::Movable:
      return &m_movableAutonomous;
    default:
      std::cerr << "UNHANDLED OPTION FOR AUTONOMOUS\n";
      return nullptr;
  }
}

std::vector<frc2::Command*> RobotContainer::GetTeleopCommands() {
  std::vector<frc2::Command*> commands;

  switch (choosers.driveChoice()) {
    case DriveChoice::Disabled:
      break;
    case DriveChoice::Manual: 
      std::cout << "Adding default drive command\n";
      commands.push_back(&m_defaultDrive);
      break;
    default:
      std::cerr << "UNHANDLED OPTION\n";
      break;
  }

  switch (choosers.shooterChoice()) {
    case ShooterChoice::Disabled:
      break;
    case ShooterChoice::Manual:
      std::cout << "Adding manual shooter command\n";
      commands.push_back(&m_manualShooter);
      break;
    default:
      std::cerr << "UNHANDLED OPTION FOR SHOOTER\n";
  }

  switch (choosers.intakeChoice()) {
    case IntakeChoice::Disabled:
      break;
    case IntakeChoice::Manual:
      commands.push_back(&m_manualIntake);
      break;
    default:
      std::cerr << "UNHANDLED OPTION FOR INTAKE\n";
  }

  // TODO: Check for subsystem requirement conflicts between the commands
  return commands;
}
