/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Singulator.h"

// TODO: Determine actual numbers for these
const int ANGULAR_DRIVER_ID = 249;
const int GATE_MOTOR_ID = 248;

Singulator::Singulator() :
    angularDriver(ANGULAR_DRIVER_ID),
    gateMotor(GATE_MOTOR_ID)
{}

void Singulator::extract(bool yes) {
    if (yes) {
        angularDriver.Set(ControlMode::PercentOutput, 0.1);
        gateMotor.Set(ControlMode::PercentOutput, 0.1);
    } else {
        angularDriver.Set(ControlMode::PercentOutput, 0.0);
        gateMotor.Set(ControlMode::PercentOutput, 0.0);
    }
}

// This method will be called once per scheduler run
void Singulator::Periodic() {}
