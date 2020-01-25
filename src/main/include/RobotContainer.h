/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/Command.h>
#include <frc2/command/button/JoystickButton.h>
#include <frc/Joystick.h>
#include <frc/XboxController.h>
#include <ctre/phoenix/sensors/PigeonIMU.h>

#include "commands/ExampleCommand.h"
#include "commands/DefaultDrive.h"
#include "commands/AlignTarget.h"
#include "commands/ManualShooter.h"
#include "commands/ShowColors.h"
#include "commands/ManualIntake.h"
#include "subsystems/ExampleSubsystem.h"
#include "subsystems/Drivetrain.h"
#include "subsystems/Shooter.h" 
#include "subsystems/Intake.h"
#include "subsystems/ColorSensor.h"

using PigeonIMU = ctre::phoenix::sensors::PigeonIMU;

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainer {
 public:
  RobotContainer();

  frc2::Command* GetAutonomousCommand();
  frc2::Command* GetTeleopCommand();

 private:
  /* --- Controls --- */
  frc::Joystick m_joystick;
  frc::XboxController m_xboxController;

  /* --- Sensors --- */
  PigeonIMU m_gyro;

  /* --- Subsystems --- */
  Drivetrain m_drivetrain;
  Shooter m_shooter;
  Intake m_intake;
  ColorSensor m_colorSensor;

  /* --- Commands --- */
  DefaultDrive m_defaultDrive;
  ManualShooter m_manualShooter;
  ManualIntake m_manualIntake;
  AlignTarget m_alignTarget;
  ShowColors m_showColors;

  /* --- Buttons --- */
  frc2::Button m_alignButton;

  void ConfigureButtonBindings();
};
