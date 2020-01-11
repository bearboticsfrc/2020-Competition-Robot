/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Drivetrain.h"

Drivetrain::Drivetrain() :
    leftBack(DriveConsts::BACK_LEFT_ID),
    leftFront(DriveConsts::FRONT_LEFT_ID),
    rightBack(DriveConsts::BACK_RIGHT_ID),
    rightFront(DriveConsts::FRONT_RIGHT_ID)
{

}

// This method will be called once per scheduler run
void Drivetrain::Periodic() {}

void Drivetrain::SetSpeed(double speed) {
    SetAllSpeed(speed, speed);
}


void Drivetrain::SetAllSpeed(double leftSpeed, double rightSpeed) {
    leftBack.Set(leftSpeed);
    leftFront.Set(leftSpeed);

    rightBack.Set(rightSpeed);
    rightFront.Set(rightSpeed);
}