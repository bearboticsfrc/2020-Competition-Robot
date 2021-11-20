/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Climber.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "units_include.h"

// TODO: Determine motor IDs
const int ARM_ID = 17;
const int WINCH_ID = 16;

Climber::Climber() :
    armMotor(ARM_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless),
    winchMotor(WINCH_ID)
{
    armMotor.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, 0.0);
    armMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    winchMotor.SetNeutralMode(NeutralMode::Brake);

    // TODO: Determine these
    armMotor.SetInverted(true);
    winchMotor.SetInverted(true);

    // TODO: Reset encoders, maybe?
    armMotor.GetEncoder().SetPosition(0.0);

    clamp.Set(0.0);
}

// This method will be called once per scheduler run
void Climber::Periodic() {
    frc::SmartDashboard::PutNumber("Arm Position", armMotor.GetEncoder().GetPosition());
}

void Climber::SetSpeed(double speed) {
   //SetArmSpeed(speed);
    SetWinchSpeed(speed);
}

void Climber::SetArmSpeed(double speed) {
    if (speed < 0) {
        clamp.Set(0.8);
        armMotor.Set(speed * 0.15);
    }
    else {
        if (speed != 0.0) {
            clamp.Set(0.8); }
        armMotor.Set(speed * 0.2);
        
    
    }
    
}

void Climber::SetWinchSpeed(double speed) {
    if (speed > 0.0) {
        speed = 0.0;
    }

    winchMotor.Set(ControlMode::PercentOutput, speed);
}