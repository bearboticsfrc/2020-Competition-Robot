/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Shooter.h"
#include <rev/CANSparkMaxLowLevel.h>

using MotorType = rev::CANSparkMaxLowLevel::MotorType;
using shooter_consts::MOTOR_1_ID;



Shooter::Shooter() :
    motor1(MOTOR_1_ID, MotorType::kBrushless)
{}

// This method will be called once per scheduler run
void Shooter::Periodic() {}


void Shooter::setSpeed(double speed) {
    motor1.Set(speed);
}