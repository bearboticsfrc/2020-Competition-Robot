// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include "subsystems/Drivetrain.h"
#include "subsystems/Arduino.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class BallTrack
    : public frc2::CommandHelper<frc2::CommandBase, BallTrack> {
 public:
  BallTrack(Arduino *arduino, Drivetrain *drivetrain);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  Arduino* m_arduino;
  Drivetrain* m_drivetrain;
};
/*
class ARed
    : public frc2::CommandHelper<frc2::SequentialCommandGroup, 
                                 ARed>{
 public:
   ARed(Drivetrain *drivetrain);

   private:
};

class BRed
    : public frc2::CommandHelper<frc2::SequentialCommandGroup, 
                                 BRed>{
 public:
   BRed(Drivetrain *drivetrain);

   private:
};

class ABlue
    : public frc2::CommandHelper<frc2::SequentialCommandGroup, 
                                 ABlue>{
 public:
   ABlue(Drivetrain *drivetrain);

   private:
};

class BBlue
    : public frc2::CommandHelper<frc2::SequentialCommandGroup, 
                                 BBlue>{
 public:
   BBlue(Drivetrain *drivetrain);

   private:
};
    */
