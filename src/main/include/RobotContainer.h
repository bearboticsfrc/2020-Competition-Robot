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
#include <cameraserver/CameraServer.h>
#include <frc2/command/RamseteCommand.h>

#include "commands/manual/ManualDrive.h"
#include "commands/manual/ManualShooter.h"
#include "commands/manual/ManualIntake.h"
#include "commands/manual/ManualClimb.h"
#include "commands/automatic/AlignTarget.h"
#include "commands/automatic/AutoShoot.h"
#include "commands/automatic/BallPickup.h"
#include "commands/automatic/Autonomous.h"
#include "commands/automatic/MovableAutonomous.h"
#include "commands/automatic/AlignAndShoot.h"
#include "commands/automatic/AlignShootDriveback.h"
#include "commands/ShowColors.h"

#include "subsystems/Climber.h"
#include "subsystems/Drivetrain.h"
#include "subsystems/Shooter.h" 
#include "subsystems/Intake.h"
#include "subsystems/ColorSensor.h"
#include "subsystems/Arduino.h"
#include "subsystems/Hopper.h"
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
  Climber m_climber;
  Hopper m_hopper;
  Drivetrain m_drivetrain;
  Shooter m_shooter;
  Intake m_intake;
  ColorSensor m_colorSensor;
  Arduino m_arduino;
  //ControlPanelManip m_controlPanelManip;

  /* --- Commands --- */
  ManualDrive m_manualDrive;
  ManualShooter m_manualShooter;
  ManualIntake m_manualIntake;
  ManualClimb m_manualClimb;
  AutoShoot m_autoShoot;
  AlignTarget m_alignTarget;
  BallPickup m_ballPickup;
  ShowColors m_showColors;
  Autonomous m_autonomous;
  MovableAutonomous m_movableAutonomous;
  FriendlyTrench m_friendlyTrench;
  EnemyTrench m_enemyTrench;
  SimpleAutonomous m_simpleForward;
  SimpleAutonomous m_simpleBackward;
  Barrel m_barrelRacing;

  /* --- Buttons --- */
  frc2::Button m_alignAndShootButton;
  frc2::Button m_toggleIntakeButton;
  frc2::Button m_reverseIntakeButton;

  /* --- Choosers --- */
  Choosers choosers;

  cs::UsbCamera camera;

  void ConfigureButtonBindings();
};
