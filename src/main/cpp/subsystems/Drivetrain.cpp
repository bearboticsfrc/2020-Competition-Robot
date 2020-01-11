/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Drivetrain.h"

Drivetrain::Drivetrain() :
    backLeft(DriveConsts::BACK_LEFT_ID),
    backRight(DriveConsts::BACK_RIGHT_ID),
    frontLeft(DriveConsts::FRONT_LEFT_ID),
    frontRight(DriveConsts::FRONT_RIGHT_ID)
{
    backLeft.SetInverted(true);
    frontLeft.SetInverted(true);
}

// This method will be called once per scheduler run
void Drivetrain::Periodic() {}

void Drivetrain::SetSpeed(double speed) {
    backLeft.Set(ControlMode::PercentOutput, speed);
    backRight.Set(ControlMode::PercentOutput, speed);
    frontLeft.Set(ControlMode::PercentOutput, speed);
    frontRight.Set(ControlMode::PercentOutput, speed);
}


void Drivetrain::SetAllSpeed(double backLeftSpeed, double backRightSpeed, double frontLeftSpeed, double frontRightSpeed) {
    backLeft.Set(ControlMode::PercentOutput, backLeftSpeed);
    backRight.Set(ControlMode::PercentOutput, backRightSpeed);
    frontLeft.Set(ControlMode::PercentOutput, frontLeftSpeed);
    frontRight.Set(ControlMode::PercentOutput, frontRightSpeed);
}