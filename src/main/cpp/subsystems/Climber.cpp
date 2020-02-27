/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Climber.h"
#include <rev/CANSparkMaxLowLevel.h>

using MotorType = rev::CANSparkMaxLowLevel::MotorType;
using climber_consts::EXTEND_ID;
using climber_consts::WINCH_ID;



Climber::Climber() :
    extendMotor(EXTEND_ID),
    winchMotor1(WINCH_ID)
{
    extendMotor.SetNeutralMode(NeutralMode::Brake);
    winchMotor1.SetNeutralMode(NeutralMode::Brake);

}

// This method will be called once per scheduler run
void Climber::Periodic() {}

// on off
void Climber::setClimb(bool climb) {
    /*motor1.Set(climb);
    motor2.Set(climb);*/
    winchMotor1.Set(ControlMode::PercentOutput, climb);
}
void Climber::Extend(double speed) {
    extendMotor.Set(ControlMode::PercentOutput, speed);
}
// set speed
void Climber::setSpeed(double speed) {
    /*motor1.Set(speed);
    motor2.Set(speed);*/
    winchMotor1.Set(ControlMode::PercentOutput, speed);
}