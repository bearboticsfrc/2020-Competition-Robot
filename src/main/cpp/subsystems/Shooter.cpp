/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// Determine Shooter Max Speed -> Feedforward
// Determine Accelerator Max Speed -> Feedforward
// Tune Shooter PID
// Tune Accelerator PID
// Determine limelight distance calculations
// Determine speeds/distance calculation

#include "Util.h"
#include "subsystems/Shooter.h"
#include "subsystems/Hopper.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <rev/CANSparkMaxLowLevel.h>
#include <rev/CANSparkMax.h>
#include <rev/ControlType.h>


using MotorType = rev::CANSparkMaxLowLevel::MotorType;
using shooter_consts::MOTOR_ID;
using shooter_consts::FEEDMOTOR_ID;
using shooter_consts::ACCELERATOR_ID;
using std::chrono::steady_clock;
using std::chrono::milliseconds;

Shooter::Shooter(Hopper *hopper) :
    motor(MOTOR_ID, MotorType::kBrushless),
    accelerator(ACCELERATOR_ID),
    feedMotor(FEEDMOTOR_ID),
    feedStartTime(steady_clock::now()),
    hopper(hopper)
{
    initDashboardValue("Shooter P Gain", 0.0001);
    initDashboardValue("Accelerator P Gain", 0.0001);

    motor.RestoreFactoryDefaults();

    motor.GetPIDController().SetFF(1.0 / 5770.0);
    motor.GetPIDController().SetP(0.0002);
    motor.GetPIDController().SetI(0.0);
    motor.GetPIDController().SetD(0.0);

    motor.SetSmartCurrentLimit(40);

    motor.SetInverted(true);

    accelerator.SetInverted(true);
}

// This method will be called once per scheduler run
void Shooter::Periodic() {
    frc::SmartDashboard::PutNumber("Shooter Speed", motor.GetEncoder().GetVelocity());

    double speedError = motor.GetEncoder().GetVelocity() - targetRPM;
    bool spinCorrect = std::abs(speedError) < 300.0;
    frc::SmartDashboard::PutNumber("Shoot Speed Error", speedError);
    if (spinCorrect) {
        ++spinSuccesses;
    } else {
        spinSuccesses = 0;
    }

    bool spinGood = spinSuccesses >= 5;

    if (stopped) {
        queueFeed = false;
    }

    if (queueFeed && spinGood) {
        //feedStartTime = steady_clock::now();
        queueFeed = false;
    }

    auto timeDiff = steady_clock::now() - feedStartTime;

    bool feedTimeGood = timeDiff > std::chrono::milliseconds(1000) && timeDiff < std::chrono::milliseconds(6000);
    bool feeding = feedTimeGood && !stopped;

    if (feeding) {
        // TODO: Determine when to stop
        hopper->setMode(HopperMode::Agitating);
    }

    double feedSpeed;
    if (feeding) {
        feedSpeed = 1.0;
    } else {
        feedSpeed = 0.0;
    }
    feedMotor.Set(ControlMode::PercentOutput, feedSpeed);
}

void Shooter::setSpeed(double speed) {
    motor.GetPIDController().SetReference(speed * 5700.0, rev::ControlType::kVelocity);
    targetRPM = speed * 5700.0;

    stopped = speed < 0.1;
    

    if (speed < 0.1) {
        accelerator.Set(ControlMode::PercentOutput, 0.0);
    } else {
        accelerator.Set(ControlMode::PercentOutput, 0.75);
    }
}

void Shooter::shootAll() {
    feedStartTime = steady_clock::now();
    queueFeed = true;
}