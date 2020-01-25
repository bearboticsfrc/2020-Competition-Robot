#include "Choosers.h"

Choosers::Choosers() {
    m_driveChooser.AddObject("Drive disabled", DriveChoice::Disabled);
    m_driveChooser.AddObject("Drive manual", DriveChoice::Manual);

    m_shooterChooser.AddObject("Shooter disabled", ShooterChoice::Disabled);
    m_shooterChooser.AddObject("Shooter manual", ShooterChoice::Manual);

    m_intakeChooser.AddObject("Intake disabled", IntakeChoice::Disabled);
    m_intakeChooser.AddObject("Intake manual", IntakeChoice::Manual);

    m_autonomousChooser.AddObject("Autonomous disabled", AutonomousChoice::Disabled);
    m_autonomousChooser.AddObject("Autonomous default", AutonomousChoice::Default);
}

DriveChoice Choosers::driveChoice() {
    return m_driveChooser.GetSelected();
}

ShooterChoice Choosers::shooterChoice() {
    return m_shooterChooser.GetSelected();
}

IntakeChoice Choosers::intakeChoice() {
    return m_intakeChooser.GetSelected();
}

AutonomousChoice Choosers::autonomousChoice(){
    return m_autonomousChooser.GetSelected();
}