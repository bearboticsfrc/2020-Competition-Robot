/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/Command.h>
#include <frc2/command/button/JoystickButton.h>
#include <ctre/phoenix/sensors/PigeonIMU.h>

#include "commands/ExampleCommand.h"
#include "commands/DefaultDrive.h"
#include "commands/AlignTarget.h"
#include "commands/BallPickup.h"
#include "commands/ManualShooter.h"
#include "commands/ShowColors.h"
#include "commands/ManualIntake.h"
#include "commands/Autonomous.h"
#include "subsystems/ExampleSubsystem.h"
#include "subsystems/Drivetrain.h"
#include "subsystems/Shooter.h" 
#include "subsystems/Intake.h"
#include "subsystems/ColorSensor.h"
#include "subsystems/Singulator.h"
#include "subsystems/Arduino.h"
#include "subsystems/ControlPanelManip.h"
#include "Choosers.h"
#include "Input.h"
#include <vector>


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
  std::vector<frc2::Command*> GetTeleopCommands();

 private:
  /* --- Controls --- */
  Input m_input;

  /* --- Sensors --- */
  PigeonIMU m_gyro;

  /* --- Subsystems --- */
  Drivetrain m_drivetrain;
  Shooter m_shooter;
  Intake m_intake;
  ColorSensor m_colorSensor;
  Arduino m_arduino;
  Singulator m_singulator;
  ControlPanelManip m_controlPanelManip;

  /* --- Commands --- */
  DefaultDrive m_defaultDrive;
  ManualShooter m_manualShooter;
  ManualIntake m_manualIntake;
  AlignTarget m_alignTarget;
  BallPickup m_ballPickup;
  ShowColors m_showColors;
  Autonomous m_autonomous;

  /* --- Buttons --- */
  frc2::Button m_alignButton;

  /* --- Choosers --- */
  Choosers choosers;

  void ConfigureButtonBindings();
};
