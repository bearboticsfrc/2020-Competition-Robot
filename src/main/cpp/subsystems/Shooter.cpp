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
using shooter_consts::MOTOR_1_ID;
using shooter_consts::MOTOR_2_ID;
using shooter_consts::FEEDMOTOR_ID;
using shooter_consts::ACCELERATOR_ID;

Shooter::Shooter() :
    motor1(MOTOR_1_ID, MotorType::kBrushless),
    motor2(MOTOR_2_ID, MotorType::kBrushless),
    accelerator(ACCELERATOR_ID, MotorType::kBrushed),
    feedMotor(FEEDMOTOR_ID)
{
    initDashboardValue("Shooter P Gain", 0.0001);
    initDashboardValue("Accelerator P Gain", 0.0001);

    motor1.RestoreFactoryDefaults();
    motor2.RestoreFactoryDefaults();

    motor1.GetPIDController().SetFF(1.0 / 5770.0);
    motor1.GetPIDController().SetP(0.00001);
    motor2.GetPIDController().SetFF(1.0 / 5770.0);
    motor2.GetPIDController().SetP(0.00001);

    motor1.SetSmartCurrentLimit(40);
    motor2.SetSmartCurrentLimit(40);
    accelerator.SetSmartCurrentLimit(40);

    motor1.SetInverted(false);
    motor2.SetInverted(true);

    accelerator.SetInverted(false);
}

// This method will be called once per scheduler run
void Shooter::Periodic() {
    frc::SmartDashboard::PutNumber("Shooter Speed", motor1.GetEncoder().GetVelocity());
    frc::SmartDashboard::PutNumber("Accelerator Speed", accelerator.GetEncoder().GetVelocity());

    double feedSpeed;
    if (std::chrono::steady_clock::now() - startTime < std::chrono::milliseconds(1000)) {
        feedSpeed = 1.0;
    } else {
        feedSpeed = 0.0;
    }
    feedMotor.Set(ControlMode::PercentOutput, feedSpeed);
}

void Shooter::setSpeed(double speed) {
    motor1.GetPIDController().SetReference(speed * 5700.0, rev::ControlType::kVelocity);
    motor2.GetPIDController().SetReference(speed * 5700.0, rev::ControlType::kVelocity);

    if (speed < 0.01) {
        accelerator.Set(0.0);
    } else {
        accelerator.Set(0.75);
    }
}

void Shooter::setDistance(units::meter_t distance) {
    // TODO: Determine correspondance
    setSpeed(distance.to<double>() / 10.0);
}

void Shooter::shootOne() {
    startTime = std::chrono::steady_clock::now();
}