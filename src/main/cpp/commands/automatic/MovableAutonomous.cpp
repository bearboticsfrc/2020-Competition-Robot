/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/automatic/MovableAutonomous.h"
#include "commands/automatic/AlignTarget.h"
#include "commands/automatic/AlignAngle.h"
#include "commands/automatic/AutoShoot.h"
#include "subsystems/Drivetrain.h"
#include "subsystems/Shooter.h"

units::degree_t calcDestAngle(units::degree_t startAngle) {
  // All distances in meters, but this uses double for the sake of compile time
  double x = -3.048 * tan(static_cast<units::radian_t>(startAngle).to<double>());
  double h = 0.8663;
  double d = 0.9466;

  double ang = atan2(h, d + x) * 360.0 / (2.0 * M_PI);
  return units::degree_t(-90 - ang);
}

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/latest/docs/software/commandbased/convenience-features.html
MovableAutonomous::MovableAutonomous(Drivetrain *drivetrain, Shooter *shooter) :
  target(std::make_unique<units::degree_t>(0.0)),
  drivetrain(drivetrain)
{
  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());
  
  AddCommands(
    AlignTarget(drivetrain),
    AutoShoot(shooter),
    AlignAngle(target.get(), drivetrain).BeforeStarting([this] { *target = calcDestAngle(this->drivetrain->GetPose().Rotation().Degrees()); })
    // TODO: Drive forward
  );
}
