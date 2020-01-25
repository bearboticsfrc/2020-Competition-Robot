/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/GenericHID.h>
#include <iostream>

using JoystickHand = frc::GenericHID::JoystickHand;

// TODO: Determine this
const int GYRO_ID = 5;

RobotContainer::RobotContainer() :
  /* --- Controllers --- */
  m_joystick(0),
  m_xboxController(1),
  /* --- Sensors --- */
  m_gyro(GYRO_ID),
  /* --- Subsystems --- */
  m_drivetrain(&m_gyro),
  /* --- Commands --- */
  m_defaultDrive(&m_drivetrain, &m_joystick),
  m_manualShooter(&m_shooter, [this]() { return m_joystick.GetTrigger(); }),
  m_manualIntake(&m_intake, [this]() { return m_xboxController.GetAButton(); }),
  m_alignTarget(&m_drivetrain),
  m_showColors(&m_colorSensor),
  m_autonomous(&m_drivetrain, &m_intake, &m_arduino, &m_shooter),
  /* --- Buttons --- */
  m_alignButton([this]() { return m_xboxController.GetAButton();})
{
  // Initialize all of your commands and subsystems here
  m_gyro.SetYaw(0.0);

  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
  m_alignButton.WhenPressed(m_alignTarget);
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  switch (choosers.autonomousChoice()) {
    case AutonomousChoice::Disabled:
      return nullptr;
    case AutonomousChoice::Default:
      return &m_autonomous;
    default:
      std::cerr << "UNHANDLED OPTION FOR AUTONOMOUS\n";
      break;
  }
}

std::vector<frc2::Command*> RobotContainer::GetTeleopCommands() {
  std::vector<frc2::Command*> commands;

  switch (choosers.driveChoice()) {
    case DriveChoice::Disabled:
      break;
    case DriveChoice::Manual: 
      commands.push_back(&m_defaultDrive);
      break;
    default:
      std::cerr << "UNHANDLED OPTION\n";
  }

  switch (choosers.shooterChoice()) {
    case ShooterChoice::Disabled:
      break;
    case ShooterChoice::Manual:
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
