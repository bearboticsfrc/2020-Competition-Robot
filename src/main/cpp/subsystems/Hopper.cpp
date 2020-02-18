/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Hopper.h"
#include <rev/CANSparkMaxLowLevel.h>
#include <rev/CANSparkMax.h>
#include <rev/ControlType.h>

using MotorType = rev::CANSparkMax::MotorType;
using hopper_consts::MOTOR_1_ID;

Hopper::Hopper() :
    motor1(MOTOR_1_ID, MotorType::kBrushless)
{
    motor1.SetSmartCurrentLimit(20);
}

// This method will be called once per scheduler run
void Hopper::Periodic() {}


void Hopper::setIntake(bool intake) {
    motor1.Set(intake);
}