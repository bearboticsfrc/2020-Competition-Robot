/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Limelight.h"
#include <networktables/NetworkTableInstance.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "units_include.h"

Limelight::Limelight() {
}

bool Limelight::targetFound() {
    return nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv", 0.0);
}

double Limelight::getX() {
    return nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx", 0.0) - 2.5;
}

double Limelight::getY() {
    return nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ty", 0.0);
}

void Limelight::setLights(bool enabled) {
    double mode;
    if (enabled) {
        mode = 3.0;
    } else {
        mode = 1.0;
    }

    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", mode);
}

// This method will be called once per scheduler run
void Limelight::Periodic() {
    
}
