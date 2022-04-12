/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Intake.h"
#include "subsystems/Hopper.h"
#include <rev/CANSparkMaxLowLevel.h>
#include "units_include.h"

using MotorType = rev::CANSparkMaxLowLevel::MotorType;
using intake_consts::MOTOR_ID;
using intake_consts::SOLENOID_ID;

Intake::Intake(Hopper *hopper) :
    motor(MOTOR_ID, MotorType::kBrushless),
    solenoid(frc::PneumaticsModuleType::CTREPCM, SOLENOID_ID),
    hopper(hopper)
{
    motor.SetSmartCurrentLimit(40);
}

// This method will be called once per scheduler run
void Intake::Periodic() {}

void Intake::setMode(IntakeMode mode) {
    switch (mode) {
        case IntakeMode::Intake:
            motor.Set(1.0);
            hopper->setMode(HopperMode::Intaking);
            break;
        case IntakeMode::Outtake:
            motor.Set(-1.0);
            hopper->setMode(HopperMode::Agitating);
            break;
        case IntakeMode::Uptake:
            motor.Set(-1.0);
            hopper->setMode(HopperMode::Intaking);
            break;
        case IntakeMode::Stopped:
            motor.Set(0.0);
            hopper->setMode(HopperMode::Stopped);
            break;
    }
}

void Intake::setExtended(bool extended) {
    solenoid.Set(extended);

    if (!extended) {
        setMode(IntakeMode::Stopped);
    }
}

bool Intake::getExtended() {
    return solenoid.Get();
}