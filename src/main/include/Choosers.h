#include <frc/smartdashboard/SendableChooser.h>

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

enum class AutonomousChoice {
    Disabled,
    Default,
};

class Choosers {
public:
    Choosers();

    DriveChoice driveChoice();

    ShooterChoice shooterChoice();

    IntakeChoice intakeChoice();

    AutonomousChoice autonomousChoice();

private:
  frc::SendableChooser<DriveChoice> m_driveChooser;
  frc::SendableChooser<ShooterChoice> m_shooterChooser;
  frc::SendableChooser<IntakeChoice> m_intakeChooser;
  frc::SendableChooser<AutonomousChoice> m_autonomousChooser;
};