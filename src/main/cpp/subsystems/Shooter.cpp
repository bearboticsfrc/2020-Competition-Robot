/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// Determine Shooter Max Speed -> Feedforward
// Determine Accelerator Max Speed -> Feedforward
// Tune Shooter PID
// Tune Accelerator PID
// Determine limelight distance calculations
// Determine speeds/distance calculation

#include "Util.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "subsystems/Shooter.h"
#include <rev/CANSparkMaxLowLevel.h>
#include <rev/CANSparkMax.h>
#include <rev/ControlType.h>


using MotorType = rev::CANSparkMaxLowLevel::MotorType;
using shooter_consts::MOTOR_ID;
using shooter_consts::FEEDMOTOR_ID;
using shooter_consts::ACCELERATOR_ID;

Shooter::Shooter() :
    motor(MOTOR_ID, MotorType::kBrushless),
    accelerator(ACCELERATOR_ID),
    feedMotor(FEEDMOTOR_ID)
{
    initDashboardValue("Shooter P Gain", 0.0001);
    initDashboardValue("Accelerator P Gain", 0.0001);

    motor.RestoreFactoryDefaults();

    motor.GetPIDController().SetFF(1.0 / 5770.0);
    motor.GetPIDController().SetP(0.00001);

    motor.SetSmartCurrentLimit(40);

    motor.SetInverted(true);

    accelerator.SetInverted(false);
}

// This method will be called once per scheduler run
void Shooter::Periodic() {
    frc::SmartDashboard::PutNumber("Shooter Speed", motor.GetEncoder().GetVelocity());

    double feedSpeed;
    if (std::chrono::steady_clock::now() - startTime < std::chrono::milliseconds(1000)) {
        feedSpeed = 1.0;
    } else {
        feedSpeed = 0.0;
    }
    feedMotor.Set(ControlMode::PercentOutput, feedSpeed);
}

void Shooter::setSpeed(double speed) {
    motor.GetPIDController().SetReference(speed * 5700.0, rev::ControlType::kVelocity);

    if (speed < 0.01) {
        accelerator.Set(ControlMode::PercentOutput, 0.0);
    } else {
        accelerator.Set(ControlMode::PercentOutput, 0.75);
    }
}

void Shooter::shootOne() {
    startTime = std::chrono::steady_clock::now();
}