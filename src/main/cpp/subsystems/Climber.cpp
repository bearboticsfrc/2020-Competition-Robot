/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Climber.h"

// TODO: Determine motor IDs
const int ARM_ID = 250;
const int WINCH_ID = 251;

Climber::Climber() :
    armMotor(ARM_ID),
    winchMotor(WINCH_ID)
{
    armMotor.SetNeutralMode(NeutralMode::Brake);
    winchMotor.SetNeutralMode(NeutralMode::Brake);

    // TODO: Determine these
    armMotor.SetInverted(false);
    winchMotor.SetInverted(false);

    // TODO: Reset encoders, maybe?
}

// This method will be called once per scheduler run
void Climber::Periodic() {
    
}

void Climber::SetSpeed(double speed) {
    SetArmSpeed(speed);
    SetWinchSpeed(speed);
}

void Climber::SetArmSpeed(double speed) {
    armMotor.Set(ControlMode::PercentOutput, speed);
}

void Climber::SetWinchSpeed(double speed) {
    winchMotor.Set(ControlMode::PercentOutput, speed);
}