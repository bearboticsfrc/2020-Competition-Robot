#include "Choosers.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "units_include.h"

Choosers::Choosers() {
    m_driveChooser.AddOption("Disabled", DriveChoice::Disabled);
    m_driveChooser.AddOption("Manual", DriveChoice::Manual);

    m_shooterChooser.AddOption("Disabled", ShooterChoice::Disabled);
    m_shooterChooser.AddOption("Manual", ShooterChoice::Manual);

    m_intakeChooser.AddOption("Disabled", IntakeChoice::Disabled);
    m_intakeChooser.AddOption("Manual", IntakeChoice::Manual);

    m_climbChooser.AddOption("Disabled", ClimbChoice::Disabled);
    m_climbChooser.AddOption("Manual", ClimbChoice::Manual);

    m_autonomousChooser.AddOption("Enemy Trench", AutonomousChoice::EnemyTrench);
    m_autonomousChooser.AddOption("Disabled", AutonomousChoice::Disabled);
    m_autonomousChooser.AddOption("Default", AutonomousChoice::Default);
    m_autonomousChooser.AddOption("Movable", AutonomousChoice::Movable);
    m_autonomousChooser.AddOption("Friendly Trench", AutonomousChoice::FriendlyTrench);
    m_autonomousChooser.AddOption("Simple Forwards", AutonomousChoice::SimpleForward);
    m_autonomousChooser.AddOption("Simple Backward", AutonomousChoice::SimpleBackward);
    m_autonomousChooser.AddOption("Barrel", AutonomousChoice::Barrel);
    m_autonomousChooser.AddOption("Slalom", AutonomousChoice::Slalom);
    m_autonomousChooser.AddOption("Bounce", AutonomousChoice::Bounce);
    m_autonomousChooser.AddOption("ARed", AutonomousChoice::ARed);
    m_autonomousChooser.AddOption("BRed", AutonomousChoice::BRed);
    m_autonomousChooser.AddOption("ABlue", AutonomousChoice::ABlue);
    m_autonomousChooser.AddOption("BBlue", AutonomousChoice::BBlue);
    m_autonomousChooser.AddOption("Teleop Playback", AutonomousChoice::Playback);

    m_constantSpeedChooser.AddOption("0% Speed", ConstantSpeedChoice::Default);
    m_constantSpeedChooser.AddOption("10% Speed", ConstantSpeedChoice::Option1);
    m_constantSpeedChooser.AddOption("20% Speed", ConstantSpeedChoice::Option2);
    m_constantSpeedChooser.AddOption("30% Speed", ConstantSpeedChoice::Option3);
    m_constantSpeedChooser.AddOption("40% Speed", ConstantSpeedChoice::Option4);
    m_constantSpeedChooser.AddOption("50% Speed", ConstantSpeedChoice::Option5);

    m_compressorChooser.AddOption("On", CompressorChoice::On);
    m_compressorChooser.AddOption("Off", CompressorChoice::Off);

    m_ballTrackChooser.AddOption("On", BallTrackChoice::On);
    m_ballTrackChooser.AddOption("Off", BallTrackChoice::Off);

    frc::SmartDashboard::PutData("DriveChooser", &m_driveChooser);
    frc::SmartDashboard::PutData("ShooterChooser", &m_shooterChooser);
    frc::SmartDashboard::PutData("IntakeChooser", &m_intakeChooser);
    frc::SmartDashboard::PutData("AutoChooser", &m_autonomousChooser);
    frc::SmartDashboard::PutData("ClimbChooser", &m_climbChooser);
    frc::SmartDashboard::PutData("Constant Speed Chooser", &m_constantSpeedChooser);
    frc::SmartDashboard::PutData("Compressor Chooser", &m_compressorChooser);
    frc::SmartDashboard::PutData("BallTrackChooser", &m_ballTrackChooser);
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

ClimbChoice Choosers::climbChoice() {
    return m_climbChooser.GetSelected();
}

AutonomousChoice Choosers::autonomousChoice(){
    return m_autonomousChooser.GetSelected();
}

ConstantSpeedChoice Choosers::constantSpeedChoice(){
    return m_constantSpeedChooser.GetSelected();
}

CompressorChoice Choosers::compressorChoice(){
    return m_compressorChooser.GetSelected();
}

BallTrackChoice Choosers::ballTrackChoice(){
    return m_ballTrackChooser.GetSelected();
}