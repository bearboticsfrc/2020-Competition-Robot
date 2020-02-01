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
    leftBack.SetInverted(false);
    leftFront.SetInverted(false);

    rightBack.SetInverted(true);
    rightFront.SetInverted(true);

    leftFront.GetEncoder().SetPosition(0.0);
    rightFront.GetEncoder().SetPosition(0.0);

    leftBack.Follow(leftFront);
    rightBack.Follow(rightFront);

    leftBack.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    leftFront.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    rightBack.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    rightFront.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

    leftBack.GetPIDController().SetFF(1.0 / 5700.0);
    leftFront.GetPIDController().SetFF(1.0 / 5700.0);
    rightBack.GetPIDController().SetFF(1.0 / 5700.0);
    rightFront.GetPIDController().SetFF(1.0 / 5700.0);
}

// In wheel rotations per motor rotation
const double GEARING = 24.0 / 50.0;
const double WHEEL_DIAMETER = 0.1524 /* 6 inches */;
const double METERS_PER_WHEEL_REV = WHEEL_DIAMETER * 3.1415926535897984626433;
// There's a factor of 5.25 because... reasons?
const double METERS_PER_REV = METERS_PER_WHEEL_REV * GEARING / 5.25;

const auto WHEELBASE = units::meter_t(0.56515) /* 22.25 inches */;

// This method will be called once per scheduler run
void Drivetrain::Periodic() {
    double leftPos = leftFront.GetEncoder().GetPosition();
    double rightPos = rightFront.GetEncoder().GetPosition();

    frc::SmartDashboard::PutNumber("Left Motor Rotations", leftPos);
    frc::SmartDashboard::PutNumber("Right Motor Rotations", rightPos);

    frc::SmartDashboard::PutNumber("Left Motor Current", leftFront.GetOutputCurrent());
    frc::SmartDashboard::PutNumber("Right Motor Current", rightFront.GetOutputCurrent());
    frc::SmartDashboard::PutNumber("Left Motor Current back", leftBack.GetOutputCurrent());
    frc::SmartDashboard::PutNumber("Right Motor Current back", rightBack.GetOutputCurrent());

    frc::SmartDashboard::PutNumber("Left Motor Velocity", leftFront.GetEncoder().GetVelocity());
    frc::SmartDashboard::PutNumber("Right Motor Velocity", rightFront.GetEncoder().GetVelocity());

    frc::SmartDashboard::PutNumber("X", pose.Translation().X().to<double>());
    frc::SmartDashboard::PutNumber("Y", pose.Translation().Y().to<double>());
    frc::SmartDashboard::PutNumber("Angle", pose.Rotation().Radians().to<double>());
    

    auto l = units::meter_t(leftPos * METERS_PER_REV);
    auto r = units::meter_t(rightPos * METERS_PER_REV);

    frc::SmartDashboard::PutNumber("Left Motor Meters", l.to<double>());
    frc::SmartDashboard::PutNumber("Right Motor Meters", r.to<double>());

    double ypr[3];
    gyro->GetYawPitchRoll(ypr);
    frc::SmartDashboard::PutNumber("Gyro Angle", ypr[0]);

    auto leftChange = l - lastLeft;
    auto rightChange = r - lastRight;

    lastLeft = l;
    lastRight = r;

    updatePose(leftChange, rightChange);
}

void Drivetrain::SetPose(frc::Pose2d newPose) {
    pose = newPose;
}

void Drivetrain::updatePose(units::meter_t leftChange, units::meter_t rightChange) {
    double ypr[3];
    gyro->GetYawPitchRoll(ypr);
    double yaw = ypr[0];
    double yaw_rad = (yaw / 360.0) * (2.0 * M_PI);

    if (std::abs(leftChange.to<double>()) < 0.001 || std::abs(rightChange.to<double>()) < 0.001) {
        return;
    }

    // TODO: Confirm that these angles are the correct direction
    pose = frc::Pose2d(pose.Translation(), frc::Rotation2d(units::radian_t(yaw_rad)));

    //if (std::abs((leftChange - rightChange).to<double>()) < 0.01) {
        auto avg = (leftChange + rightChange) / 2.0;
        pose += frc::Transform2d(
            frc::Translation2d(
                avg,
                units::meter_t(0.0)
            ),
            frc::Rotation2d()
        );
    /*} else {
        units::meter_t r = WHEELBASE / 2.0 * (leftChange + rightChange) / (leftChange - rightChange);
        units::meter_t icc_x = pose.Translation().X() - r * pose.Rotation().Sin();
        units::meter_t icc_y = pose.Translation().Y() + r * pose.Rotation().Cos();
        auto w = units::radian_t(((rightChange - leftChange) / WHEELBASE).to<double>());

        pose = frc::Pose2d(pose.Translation() + frc::Translation2d(-icc_x, -icc_y), pose.Rotation());
        pose = frc::Pose2d(pose.Translation().RotateBy(frc::Rotation2d{ w }), pose.Rotation());
        pose = frc::Pose2d(pose.Translation() + frc::Translation2d(icc_x, icc_y), pose.Rotation());
    }*/
}

void Drivetrain::SetSpeed(double speed) {
    SetAllSpeed(speed, speed);
}

frc::Pose2d Drivetrain::GetPose() {
    return pose;
}   


void Drivetrain::SetAllSpeed(double leftSpeed, double rightSpeed) {
    /*leftFront.Set(leftSpeed);
    rightFront.Set(rightSpeed);

    frc::SmartDashboard::PutNumber("Left Power", leftSpeed);
    frc::SmartDashboard::PutNumber("Right Power", rightSpeed);*/

    leftFront.GetPIDController().SetReference(leftSpeed * 5700.0, rev::ControlType::kVelocity);
    rightFront.GetPIDController().SetReference(rightSpeed * 5700.0, rev::ControlType::kVelocity);
}

// Maybe use setPositionConversionFactor() ?
void Drivetrain::SetSpeeds(units::meters_per_second_t lSpeed, units::meters_per_second_t rSpeed) {
    auto l = lSpeed.to<double>() / METERS_PER_REV / 10.0;
    auto r = rSpeed.to<double>() / METERS_PER_REV / 10.0;

    frc::SmartDashboard::PutNumber("Target speed average", (l + r) / 2.0);

    leftFront.GetPIDController().SetReference(l, rev::ControlType::kVelocity);
    rightFront.GetPIDController().SetReference(r, rev::ControlType::kVelocity);
}