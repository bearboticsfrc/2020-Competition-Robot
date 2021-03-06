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
#include <frc2/command/ParallelRaceGroup.h>
#include <iostream>
#include "units_include.h"

const int GYRO_ID = 10;

RobotContainer::RobotContainer() :
  /* --- Sensors --- */
  m_gyro(GYRO_ID),
  /* --- Subsystems --- */
  m_climber(),
  m_hopper(),
  m_drivetrain(&m_gyro),
  m_shooter(&m_hopper),
  m_intake(&m_hopper),
  m_colorSensor(),
  m_arduino(),
  /* --- Commands --- */
  m_manualDrive(&m_drivetrain, &m_input),
  m_manualShooter(&m_shooter, m_input.ManualShootButton()),
  m_manualIntake(&m_intake, m_input.RunIntakeButton(), m_input.RunUptakeButton(), m_input.ReverseIntakeButton()),
  m_manualClimb(&m_climber, &m_input),
  m_autoShoot(&m_shooter, &m_intake),
  m_alignTarget(&m_drivetrain, &m_intake),
  m_ballPickup(&m_drivetrain, &m_intake, &m_arduino),
  m_showColors(&m_colorSensor),
  m_autonomous(&m_drivetrain, &m_intake, &m_arduino, &m_shooter),
  m_movableAutonomous(&m_drivetrain, &m_shooter, &m_intake),
  m_friendlyTrench(&m_drivetrain, &m_intake, &m_arduino, &m_shooter),
  m_enemyTrench(&m_drivetrain, &m_intake, &m_arduino, &m_shooter),
  m_simpleForward(&m_drivetrain, &m_intake, &m_arduino, &m_shooter, true),
  m_simpleBackward(&m_drivetrain, &m_intake, &m_arduino, &m_shooter, false),
  m_barrelRacing((&m_drivetrain)),
  m_slalom((&m_drivetrain)),
  m_bounce((&m_drivetrain)),
  m_aRed(&m_drivetrain),
  m_bRed(&m_drivetrain),
  m_aBlue(&m_drivetrain),
  m_bBlue(&m_drivetrain), 
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
  m_alignAndShootButton.ToggleWhenPressed(AlignAndShoot(&m_drivetrain, &m_shooter, &m_intake)/*.WithInterrupt([this] { return !m_input.AutoShootButton()(); })*/);
  m_toggleIntakeButton.WhenPressed(frc2::InstantCommand{ [this] { m_intake.setExtended(!m_intake.getExtended()); } });
  
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // TODO: Maybe use SelectCommand?
  switch (choosers.autonomousChoice()) {
    case AutonomousChoice::Disabled:
      return nullptr;
    case AutonomousChoice::Default:
      return &m_autonomous;
    case AutonomousChoice::Movable:
      return &m_movableAutonomous;
    case AutonomousChoice::FriendlyTrench:
      return &m_friendlyTrench;
    case AutonomousChoice::EnemyTrench:
      return &m_enemyTrench;
    case AutonomousChoice::SimpleForward:
      return &m_simpleForward;
    case AutonomousChoice::SimpleBackward:
      return &m_simpleBackward;
    case AutonomousChoice::Barrel:
      return &m_barrelRacing;
    case AutonomousChoice::Slalom:
      return &m_slalom;
    case AutonomousChoice::Bounce:
      return &m_bounce;
    case AutonomousChoice::ARed:
      return &m_aRed;
    case AutonomousChoice::BRed:
      return &m_bRed;
    case AutonomousChoice::ABlue:
      return &m_aBlue;
    case AutonomousChoice::BBlue:
      return &m_bBlue;
    default:
      std::cerr << "UNHANDLED OPTION FOR AUTONOMOUS\n";
      return nullptr;
  }
}

std::vector<frc2::Command*> RobotContainer::GetTeleopCommands() {
  std::vector<frc2::Command*> commands;

  /*switch (choosers.driveChoice()) {
    case DriveChoice::Disabled:
      break;
    case DriveChoice::Manual: */
      std::cout << "Adding default drive command\n";
      commands.push_back(&m_manualDrive);
      m_drivetrain.SetDefaultCommand(m_manualDrive);
    /*  break;
    default:
      std::cerr << "UNHANDLED OPTION\n";
      break;
  }*/

  /*switch (choosers.shooterChoice()) {
    case ShooterChoice::Disabled:
      break;
    case ShooterChoice::Manual:*/
      std::cout << "Adding manual shooter command\n";
      commands.push_back(&m_manualShooter);
      m_shooter.SetDefaultCommand(m_manualShooter);
    /*  break;
    default:
      std::cerr << "UNHANDLED OPTION FOR SHOOTER\n";
  }*/

  /*switch (choosers.intakeChoice()) {
    case IntakeChoice::Disabled:
      break;
    case IntakeChoice::Manual:*/
      commands.push_back(&m_manualIntake);
      m_intake.SetDefaultCommand(m_manualIntake);
  /*    break;
    default:
      std::cerr << "UNHANDLED OPTION FOR INTAKE\n";
  }*/

  /*switch (choosers.climbChoice()) {
    case ClimbChoice::Disabled:
      break;
    case ClimbChoice::Manual:*/
      commands.push_back(&m_manualClimb);
      m_climber.SetDefaultCommand(m_manualClimb);
  /*    break;
    default:
      std::cerr << "UNHANDLED OPTION FOR CLIMBER\n";
  }*/

  // TODO: Check for subsystem requirement conflicts between the commands
  return commands;
}
