/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Drivetrain.h"
#include <rev/CANSparkMaxLowLevel.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/geometry/Transform2d.h>
#include <frc/geometry/Translation2d.h>
#include <frc/geometry/Rotation2d.h>
#include <ctre/phoenix/sensors/PigeonIMU.h>
#include <vector>
#include <cmath>


using MotorType = rev::CANSparkMaxLowLevel::MotorType;
using PigeonIMU = ctre::phoenix::sensors::PigeonIMU;

Drivetrain::Drivetrain(PigeonIMU *gyro) :
    gyro(gyro),
    lastLeft(0),
    lastRight(0),
    leftBack(DriveConsts::LEFT_2_ID, MotorType::kBrushless),
    leftFront(DriveConsts::LEFT_1_ID, MotorType::kBrushless),
    rightBack(DriveConsts::RIGHT_2_ID, MotorType::kBrushless),
    rightFront(DriveConsts::RIGHT_1_ID, MotorType::kBrushless)
{
    leftBack.Follow(leftFront);
    rightBack.Follow(rightFront);
}

// TODO: Determine these
const double METERS_PER_REV = 10.0;
const auto WHEELBASE = units::meter_t(12.0);

// This method will be called once per scheduler run
void Drivetrain::Periodic() {
    double leftPos = leftFront.GetEncoder().GetPosition();
    double rightPos = rightFront.GetEncoder().GetPosition();

    auto l = units::meter_t(leftPos * METERS_PER_REV);
    auto r = units::meter_t(rightPos * METERS_PER_REV);

    auto leftChange = l - lastLeft;
    auto rightChange = r - lastRight;

    lastLeft = l;
    lastRight = r;

    updatePose(leftChange, rightChange);
}

void Drivetrain::updatePose(units::meter_t leftChange, units::meter_t rightChange) {
    double ypr[3];
    gyro->GetYawPitchRoll(ypr);
    double yaw = ypr[0];
    double yaw_rad = yaw / 360.0 * (2.0 * M_PI);

    // TODO: Confirm that these angles are the correct direction
    pose = frc::Pose2d(pose.Translation(), frc::Rotation2d(units::radian_t(yaw_rad)));

    if (std::abs((leftChange - rightChange).to<double>()) < 0.001) {
        pose += frc::Transform2d(
            frc::Translation2d(
                leftChange,
                rightChange
            ),
            frc::Rotation2d()
        );
    } else {
        units::meter_t r = WHEELBASE / 2.0 * (leftChange + rightChange) / (leftChange - rightChange);
        units::meter_t icc_x = pose.Translation().X() - r * pose.Rotation().Sin();
        units::meter_t icc_y = pose.Translation().Y() + r * pose.Rotation().Cos();
        auto w = units::radian_t(((rightChange - leftChange) / WHEELBASE).to<double>());

        pose += frc::Transform2d{ frc::Translation2d(-icc_x, -icc_y), frc::Rotation2d() };
        pose.Translation().RotateBy(frc::Rotation2d{ w });
        pose += frc::Transform2d{ frc::Translation2d(icc_x, icc_y), frc::Rotation2d() };
    }
}

void Drivetrain::SetSpeed(double speed) {
    SetAllSpeed(speed, speed);
}

// TODO: Handle pose properly
frc::Pose2d Drivetrain::GetPose() {
    return pose;
}   


void Drivetrain::SetAllSpeed(double leftSpeed, double rightSpeed) {
    leftFront.Set(leftSpeed);
    rightFront.Set(rightSpeed);
}

// Maybe use setPositionConversionFactor() ?
void Drivetrain::SetSpeeds(units::meters_per_second_t lSpeed, units::meters_per_second_t rSpeed) {
    auto l = units::revolutions_per_minute_t(lSpeed.to<double>() / METERS_PER_REV * 60.0);
    auto r = units::revolutions_per_minute_t(rSpeed.to<double>() / METERS_PER_REV * 60.0);

    leftFront.Set(l.to<double>());
    rightFront.Set(r.to<double>());
}