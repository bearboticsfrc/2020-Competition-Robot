/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Limelight.h"
#include <networktables/NetworkTableInstance.h>

Limelight::Limelight() {}

bool Limelight::targetFound() {
    return nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetEntry("tv").GetDouble(0.0);
}

double Limelight::getX() {
    return nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetEntry("tx").GetDouble(0.0);
}

double Limelight::getY() {
    return nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetEntry("ty").GetDouble(0.0);
}

// This method will be called once per scheduler run
void Limelight::Periodic() {}
