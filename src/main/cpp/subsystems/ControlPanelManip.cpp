/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/ControlPanelManip.h"
#include "units_include.h"

// TODO: DETERMINE ACTUAL IDS
const int EXT_SOLENOID_ID = 5;
const int RET_SOLENOID_ID = 6;
const int MOTOR_ID = 230;

ControlPanelManip::ControlPanelManip() :
    extendSolenoid(frc::PneumaticsModuleType::CTREPCM, EXT_SOLENOID_ID),
    retractSolenoid(frc::PneumaticsModuleType::CTREPCM, RET_SOLENOID_ID),
    motor(MOTOR_ID, rev::CANSparkMax::MotorType::kBrushless)
{
    extendSolenoid.Set(false);
    retractSolenoid.Set(true);

    motor.SetSmartCurrentLimit(40);
}

void ControlPanelManip::setPosition(double pos) {
   // motor.GetPIDController().SetOutputRange(-0.1, 0.1);
   // motor.GetPIDController().SetReference(pos, rev::CANSparkMax::ControlType::kPosition);
}

// This method will be called once per scheduler run
void ControlPanelManip::Periodic() {}
