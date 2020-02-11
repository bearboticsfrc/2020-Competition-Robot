/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Intake.h"
#include <rev/CANSparkMaxLowLevel.h>

using MotorType = rev::CANSparkMaxLowLevel::MotorType;
using intake_consts::MOTOR_1_ID;
using intake_consts::MOTOR_2_ID;
using intake_consts::SOLENOID_ID;

Intake::Intake() :
    motor1(MOTOR_1_ID, MotorType::kBrushless),
    motor2(MOTOR_2_ID, MotorType::kBrushless),
    solenoid(SOLENOID_ID)
{
    motor1.SetSmartCurrentLimit(40);
    motor2.SetSmartCurrentLimit(40);
}

// This method will be called once per scheduler run
void Intake::Periodic() {}

void Intake::setIntake(bool intake) {
    motor1.Set(intake);
    motor2.Set(intake);
}

void Intake::setExtended(bool extended) {
    solenoid.Set(extended);

    if (!extended) {
        setIntake(false);
    }
}