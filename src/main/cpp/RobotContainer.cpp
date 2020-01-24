/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"
#include <frc/GenericHID.h>

using JoystickHand = frc::GenericHID::JoystickHand;

RobotContainer::RobotContainer() :
  m_joystick(0),
  m_xboxController(1),
  m_defaultDrive(&m_drivetrain, &m_joystick),
  m_manualShooter(&m_shooter, &m_joystick),
  m_alignTarget(&m_drivetrain),
  m_showColors(&m_colorSensor)
{
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
  m_xboxController.GetBumper(JoystickHand::kLeftHand);
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return nullptr;
}

frc2::Command* RobotContainer::GetTeleopCommand() {
  return &m_defaultDrive;
}
