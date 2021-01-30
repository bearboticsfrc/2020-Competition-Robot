/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>
#include <frc2/command/SequentialCommandGroup.h>

class Drivetrain;
class Intake;
class Arduino;
class Shooter;

class Autonomous
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 Autonomous> {
public:
  Autonomous(Drivetrain *drivetrain, Intake *intake, Arduino *arduino, Shooter *s);

private:
};

class FriendlyTrench
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 FriendlyTrench> {
public:
  FriendlyTrench(Drivetrain *drivetrain, Intake *intake, Arduino *arduino, Shooter *s);

private:
};

class EnemyTrench 
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 EnemyTrench> {
public:
  EnemyTrench(Drivetrain *drivetrain, Intake *intake, Arduino *arduino, Shooter *s);

private:
};

class SimpleAutonomous 
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 Autonomous> {
public:
  SimpleAutonomous(Drivetrain *drivetrain, Intake *intake, Arduino *arduino, Shooter *s, bool forwards);

private:
};

class Barrel
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                  Barrel> {
public:
  Barrel(Drivetrain *drivetrain);

private:
};

class StraightLine
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                  StraightLine> {
public:
  StraightLine(Drivetrain *drivetrain);

private:
};

class Slalom
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                  Slalom> {
public:
  Slalom(Drivetrain *drivetrain);

private:
};

class Bounce
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                  Bounce> {
public:
  Bounce(Drivetrain *drivetrain);

private:
};