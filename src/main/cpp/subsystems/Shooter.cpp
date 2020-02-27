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
    hopper(hopper),
    state(StoppedState(this))
{
    initDashboardValue("Shooter P Gain", 0.0001);
    initDashboardValue("Accelerator P Gain", 0.0001);

    motor.RestoreFactoryDefaults();

    motor.GetPIDController().SetFF(1.0 / 5330.0);
    motor.GetPIDController().SetP(0.0002);
    motor.GetPIDController().SetI(0.0);
    motor.GetPIDController().SetD(0.0);

    motor.SetSmartCurrentLimit(40);

    motor.SetInverted(true);

    accelerator.SetInverted(true);
}

StoppedState::StoppedState(Shooter *shooter) {
    std::cout << "Transitioning to stopped state\n";
    shooter->motor.Set(0.0);
    shooter->accelerator.Set(ControlMode::PercentOutput, 0.0);
    shooter->feedMotor.Set(ControlMode::PercentOutput, 0.0);
    shooter->hopper->setMode(HopperMode::Stopped);
}

SpinningState::SpinningState(Shooter *shooter, double targetRpm, std::function<bool()> runCheck) :
    targetRpm(targetRpm),
    runCheck(runCheck)
{
    std::cout << "Transitioning to spinning state\n";
    shooter->motor.GetPIDController().SetReference(targetRpm, rev::ControlType::kVelocity);
    shooter->accelerator.Set(ControlMode::PercentOutput, 0.75);
}

ShootingState::ShootingState(Shooter *shooter) :
    startTime(steady_clock::now())
{
    std::cout << "Transitioning to shooting state\n";
    shooter->hopper->setMode(HopperMode::Agitating);
    shooter->feedMotor.Set(ControlMode::PercentOutput, true);
}

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

// This method will be called once per scheduler run
void Shooter::Periodic() {
    frc::SmartDashboard::PutNumber("Shooter Speed", motor.GetEncoder().GetVelocity());

    state = std::visit(overloaded {
        [this](StoppedState s) {
            return ShooterState(s);
        },
        [this](SpinningState s) {
            double speedError = motor.GetEncoder().GetVelocity() - s.targetRpm;
            frc::SmartDashboard::PutNumber("Shoot Speed Error", speedError);

            if (std::abs(speedError) < 150.0) {
                ++s.spinSuccesses;
            } else {
                s.spinSuccesses = 0;
            }

            if (s.spinSuccesses >= 5 && s.runCheck()) {
                return ShooterState(ShootingState(this));
            }

            return ShooterState(s);
        },
        [this](ShootingState s) {
            // TODO: Determine how long we need to spend shooting or 
            // find a better system to shoot all of the power cells
            auto elapsed = steady_clock::now() - s.startTime;
            if (elapsed > milliseconds(5000)) {
                return ShooterState(StoppedState(this));
            }

            return ShooterState(s);
        }
    }, state);
}

void Shooter::shoot(double speed, std::function<bool()> runCheck) {
    if (!std::holds_alternative<ShootingState>(state)) {
        state = ShooterState(SpinningState(this, speed * 5330.0, runCheck));
    }
}

bool Shooter::IsStopped() const {
    return std::holds_alternative<StoppedState>(state);
}