/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Shooter.h"
#include <rev/CANSparkMaxLowLevel.h>
#include <rev/CANSparkMax.h>
#include <rev/ControlType.h>


using MotorType = rev::CANSparkMaxLowLevel::MotorType;
using shooter_consts::MOTOR_1_ID;
using shooter_consts::FEEDMOTOR_1_ID;
using shooter_consts::ACCELERATOR_ID;

Shooter::Shooter() :
    motor1(MOTOR_1_ID, MotorType::kBrushless),
    feedMotor(FEEDMOTOR_1_ID, MotorType::kBrushless),
    accelerator(ACCELERATOR_ID)
{}

// This method will be called once per scheduler run
void Shooter::Periodic() {}

void Shooter::setSpeed(double speed) {
    motor1.Set(speed);
    accelerator.Set(ControlMode::PercentOutput, speed);
}

void Shooter::setDistance(units::meter_t distance) {
    // TODO: Determine correspondance
    setSpeed(distance.to<double>() / 10.0);
}

void Shooter::shootOne() {
    double position = feedMotor.GetEncoder().GetPosition();
    feedMotor.GetPIDController().SetReference(position + 1.0, rev::ControlType::kPosition);
}