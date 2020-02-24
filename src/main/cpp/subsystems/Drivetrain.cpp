/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Drivetrain.h"
#include "Util.h"
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

const std::string LB_P_GAIN_NAME = "Left Back P Gain";
const std::string LF_P_GAIN_NAME = "Left Front P Gain";
const std::string RB_P_GAIN_NAME = "Right Back P Gain";
const std::string RF_P_GAIN_NAME = "Right Front P Gain";

Drivetrain::Drivetrain(PigeonIMU *gyro) :
    gyro(gyro),
    lastLeft(0),
    lastRight(0),
    leftBack(DriveConsts::LEFT_2_ID, MotorType::kBrushless),
    leftFront(DriveConsts::LEFT_1_ID, MotorType::kBrushless),
    rightBack(DriveConsts::RIGHT_2_ID, MotorType::kBrushless),
    rightFront(DriveConsts::RIGHT_1_ID, MotorType::kBrushless)
{
    initDashboardValue(LB_P_GAIN_NAME, 0.0);
    initDashboardValue(LF_P_GAIN_NAME, 0.0);
    initDashboardValue(RB_P_GAIN_NAME, 0.0);
    initDashboardValue(RF_P_GAIN_NAME, 0.0);

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

    leftBack.SetSmartCurrentLimit(40);
    leftFront.SetSmartCurrentLimit(40);
    rightBack.SetSmartCurrentLimit(40);
    rightFront.SetSmartCurrentLimit(40);
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
    if (PID_TUNING) {
        leftBack.GetPIDController().SetP(
            frc::SmartDashboard::GetNumber(LB_P_GAIN_NAME, 0.0)
        );
        leftFront.GetPIDController().SetP(
            frc::SmartDashboard::GetNumber(LF_P_GAIN_NAME, 0.0)
        );
        rightBack.GetPIDController().SetP(
            frc::SmartDashboard::GetNumber(RB_P_GAIN_NAME, 0.0)
        );
        rightFront.GetPIDController().SetP(
            frc::SmartDashboard::GetNumber(RF_P_GAIN_NAME, 0.0)
        );
    }

    double leftPos = leftFront.GetEncoder().GetPosition();
    double rightPos = rightFront.GetEncoder().GetPosition();

    //frc::SmartDashboard::PutNumber("Left Motor Rotations", leftPos);
    //frc::SmartDashboard::PutNumber("Right Motor Rotations", rightPos);

    //frc::SmartDashboard::PutNumber("Left Motor Current", leftFront.GetOutputCurrent());
    //frc::SmartDashboard::PutNumber("Right Motor Current", rightFront.GetOutputCurrent());
    //frc::SmartDashboard::PutNumber("Left Motor Current back", leftBack.GetOutputCurrent());
    //frc::SmartDashboard::PutNumber("Right Motor Current back", rightBack.GetOutputCurrent());

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
    gyro->SetYaw(newPose.Rotation().Degrees().to<double>());
    pose = newPose;
}

void Drivetrain::updatePose(units::meter_t leftChange, units::meter_t rightChange) {
    previousPose = pose;

    double ypr[3];
    gyro->GetYawPitchRoll(ypr);
    double yaw = ypr[0];
    double yaw_rad = (yaw / 360.0) * (2.0 * M_PI);

    pose = frc::Pose2d(pose.Translation(), frc::Rotation2d(units::radian_t(yaw_rad)));

    auto avg = (leftChange + rightChange) / 2.0;
    pose += frc::Transform2d(
        frc::Translation2d(
            avg,
            units::meter_t(0.0)
        ),
        frc::Rotation2d()
    );
}

void Drivetrain::SetSpeed(double speed) {
    SetSpeeds(speed, speed);
}

frc::Pose2d Drivetrain::GetPose() {
    return pose;
}   

frc::Pose2d Drivetrain::GetLastPose() {
    return previousPose;
}

void Drivetrain::SetSpeeds(double leftSpeed, double rightSpeed) {
    leftFront.GetPIDController().SetReference(leftSpeed * 5700.0, rev::ControlType::kVelocity);
    rightFront.GetPIDController().SetReference(rightSpeed * 5700.0, rev::ControlType::kVelocity);
}

void Drivetrain::SetSpeeds(units::meters_per_second_t lSpeed, units::meters_per_second_t rSpeed) {
    auto l = lSpeed.to<double>() / METERS_PER_REV * 60.0;
    auto r = rSpeed.to<double>() / METERS_PER_REV * 60.0;

    //frc::SmartDashboard::PutNumber("Target speed average", (l + r) / 2.0);

    leftFront.GetPIDController().SetReference(l, rev::ControlType::kVelocity);
    rightFront.GetPIDController().SetReference(r, rev::ControlType::kVelocity);
}
