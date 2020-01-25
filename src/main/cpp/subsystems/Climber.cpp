/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Climber.h"
#include <rev/CANSparkMaxLowLevel.h>

using MotorType = rev::CANSparkMaxLowLevel::MotorType;
using climber_consts::MOTOR_1_ID;
using climber_consts::MOTOR_2_ID;

Climber::Climber() :
    motor1(MOTOR_1_ID, MotorType::kBrushless),
    motor2(MOTOR_2_ID, MotorType::kBrushless)
{}

// This method will be called once per scheduler run
void Climber::Periodic() {}

// on off
void Climber::setClimb(bool climb) {
    motor1.Set(climb);
    motor2.Set(climb);
}

// set speed
void Climber::setSpeed(double speed) {
    motor1.Set(speed);
    motor2.Set(speed);
}