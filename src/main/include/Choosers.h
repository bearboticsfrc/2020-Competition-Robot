#pragma once

#include <frc/smartdashboard/SendableChooser.h>
#include "units_include.h"

enum class DriveChoice {
    Disabled,
    Manual
};

enum class ShooterChoice {
    Disabled,
    Manual
};

enum class IntakeChoice {
    Disabled,
    Manual
};

enum class ClimbChoice {
    Disabled,
    Manual
};

enum class AutonomousChoice {
    Disabled,
    Default,
    Movable,
    FriendlyTrench,
    EnemyTrench,
    SimpleForward,
    SimpleBackward,
    Barrel,
    Slalom,
    Bounce,
    ARed,
    BRed,
    ABlue,
    BBlue
};

enum class ConstantSpeedChoice {
    Default,
    Option1,
    Option2,
    Option3 
};

enum class CompressorChoice {
    On,
    Off
};

class Choosers {
public:
    Choosers();

    DriveChoice driveChoice();

    ShooterChoice shooterChoice();

    IntakeChoice intakeChoice();

    ClimbChoice climbChoice();

    AutonomousChoice autonomousChoice();

    ConstantSpeedChoice constantSpeedChoice();

    CompressorChoice compressorChoice();

private:
  frc::SendableChooser<DriveChoice> m_driveChooser;
  frc::SendableChooser<ShooterChoice> m_shooterChooser;
  frc::SendableChooser<IntakeChoice> m_intakeChooser;
  frc::SendableChooser<ClimbChoice> m_climbChooser;
  frc::SendableChooser<AutonomousChoice> m_autonomousChooser;
  frc::SendableChooser<ConstantSpeedChoice> m_constantSpeedChooser;
  frc::SendableChooser<CompressorChoice> m_compressorChooser;
};