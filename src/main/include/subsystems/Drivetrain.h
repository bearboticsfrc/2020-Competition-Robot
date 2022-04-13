/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "rev/CANSparkMax.h"
#include <frc/geometry/Pose2d.h>
#include <units/velocity.h>
#include <units/length.h>
#include "units_include.h"

namespace ctre {
  namespace phoenix {
    namespace sensors {
      class PigeonIMU;
    }
  }
}

namespace DriveConsts {
  const int LEFT_2_ID = 1;
  const int RIGHT_2_ID = 3;
  const int LEFT_1_ID = 2;
  const int RIGHT_1_ID = 4;
}

class Drivetrain : public frc2::SubsystemBase {
 public:
  Drivetrain(ctre::phoenix::sensors::PigeonIMU *gyro);

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

  void SetSpeed(double speed);
  void SetSpeeds(double leftSpeed, double rightSpeed);
  void SetSpeeds(units::meters_per_second_t leftSpeed, units::meters_per_second_t rightSpeed);

  units::meter_t GetAverageEncoder() ;

  frc::Pose2d GetPose();

  frc::Pose2d GetLastPose();

  void SetPose(frc::Pose2d newPose);

private:
  frc::Pose2d previousPose;

  void updatePose(units::meter_t leftChange, units::meter_t rightSpeed);

  ctre::phoenix::sensors::PigeonIMU *gyro;

  units::meter_t lastLeft;
  units::meter_t lastRight;

  rev::CANSparkMax leftBack;
  rev::CANSparkMax leftFront;
  rev::CANSparkMax rightBack;
  rev::CANSparkMax rightFront;

  rev::SparkMaxPIDController leftBackPIDController;
  rev::SparkMaxPIDController leftFrontPIDController;
  rev::SparkMaxPIDController rightBackPIDController;
  rev::SparkMaxPIDController rightFrontPIDController;

  rev::SparkMaxRelativeEncoder leftFrontEncoder;
  rev::SparkMaxRelativeEncoder rightFrontEncoder;

  frc::Pose2d pose;

};
