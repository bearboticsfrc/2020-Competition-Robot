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
    StraightLine,
    Slalom,
    Bounce,
};

class Choosers {
public:
    Choosers();

    DriveChoice driveChoice();

    ShooterChoice shooterChoice();

    IntakeChoice intakeChoice();

    ClimbChoice climbChoice();

    AutonomousChoice autonomousChoice();

private:
  frc::SendableChooser<DriveChoice> m_driveChooser;
  frc::SendableChooser<ShooterChoice> m_shooterChooser;
  frc::SendableChooser<IntakeChoice> m_intakeChooser;
  frc::SendableChooser<ClimbChoice> m_climbChooser;
  frc::SendableChooser<AutonomousChoice> m_autonomousChooser;
};