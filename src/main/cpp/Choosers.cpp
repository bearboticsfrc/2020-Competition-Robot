#include "Choosers.h"
#include <frc/smartdashboard/SmartDashboard.h>

Choosers::Choosers() {
    m_driveChooser.AddOption("Disabled", DriveChoice::Disabled);
    m_driveChooser.AddOption("Manual", DriveChoice::Manual);

    m_shooterChooser.AddOption("Disabled", ShooterChoice::Disabled);
    m_shooterChooser.AddOption("Manual", ShooterChoice::Manual);

    m_intakeChooser.AddOption("Disabled", IntakeChoice::Disabled);
    m_intakeChooser.AddOption("Manual", IntakeChoice::Manual);

    m_autonomousChooser.AddOption("Disabled", AutonomousChoice::Disabled);
    m_autonomousChooser.AddOption("Default", AutonomousChoice::Default);
    m_autonomousChooser.AddOption("Movable", AutonomousChoice::Movable);
    m_autonomousChooser.AddOption("Friendly Trench", AutonomousChoice::FriendlyTrench);
    m_autonomousChooser.AddOption("Enemy Trench", AutonomousChoice::EnemyTrench);
    m_autonomousChooser.AddOption("Simple Forwards", AutonomousChoice::SimpleForward);
    m_autonomousChooser.AddOption("Simple Backward", AutonomousChoice::SimpleBackward);

    frc::SmartDashboard::PutData("DriveChooser", &m_driveChooser);
    frc::SmartDashboard::PutData("ShooterChooser", &m_shooterChooser);
    frc::SmartDashboard::PutData("IntakeChooser", &m_intakeChooser);
    frc::SmartDashboard::PutData("AutoChooser", &m_autonomousChooser);
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