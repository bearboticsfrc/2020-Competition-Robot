/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Intake.h"
#include "subsystems/Hopper.h"
#include <rev/CANSparkMaxLowLevel.h>

using MotorType = rev::CANSparkMaxLowLevel::MotorType;
using intake_consts::MOTOR_ID;
using intake_consts::SOLENOID_ID;

Intake::Intake(Hopper *hopper) :
    motor(MOTOR_ID, MotorType::kBrushless),
    solenoid(SOLENOID_ID),
    hopper(hopper)
{
    motor.SetSmartCurrentLimit(40);
}

// This method will be called once per scheduler run
void Intake::Periodic() {}

void Intake::setIntake(bool intake) {
    motor.Set(intake);
    hopper->setIntake(intake);
}

void Intake::setOuttake(bool outtake) {
    motor.Set(-outtake);
}

void Intake::setUptake(bool uptake) {
    motor.Set(-uptake);
    hopper->setIntake(uptake);
}

void Intake::setExtended(bool extended) {
    solenoid.Set(extended);

    if (!extended) {
        setIntake(false);
    }
}

bool Intake::getExtended() {
    return solenoid.Get();
}