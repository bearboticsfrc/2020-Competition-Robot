#include "Choosers.h"
#include <frc/smartdashboard/SmartDashboard.h>

Choosers::Choosers() {
    m_driveChooser.AddOption("Drive disabled", DriveChoice::Disabled);
    m_driveChooser.AddOption("Drive manual", DriveChoice::Manual);

    m_shooterChooser.AddOption("Shooter disabled", ShooterChoice::Disabled);
    m_shooterChooser.AddOption("Shooter manual", ShooterChoice::Manual);

    m_intakeChooser.AddOption("Intake disabled", IntakeChoice::Disabled);
    m_intakeChooser.AddOption("Intake manual", IntakeChoice::Manual);

    m_autonomousChooser.AddOption("Autonomous disabled", AutonomousChoice::Disabled);
    m_autonomousChooser.AddOption("Autonomous default", AutonomousChoice::Default);
    m_autonomousChooser.AddOption("Autonomous default2", AutonomousChoice::Default2);
    m_autonomousChooser.AddOption("Autonomous movable", AutonomousChoice::Movable);

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