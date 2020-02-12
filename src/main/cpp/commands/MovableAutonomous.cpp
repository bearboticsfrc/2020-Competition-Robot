/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/MovableAutonomous.h"
#include "commands/AlignTarget.h"
#include "commands/AlignAngle.h"
#include "commands/AutoShoot.h"
#include "subsystems/Drivetrain.h"
#include "subsystems/Shooter.h"

units::degree_t calcDestAngle(units::degree_t startAngle) {
  units::meter_t x = units::foot_t(-10 * tan(static_cast<units::radian_t>(startAngle).to<double>()));
  units::meter_t h = units::centimeter_t(86.63);
  units::meter_t d = units::centimeter_t(94.66);

  auto ang = units::radian_t(atan2(h.to<double>(), (d + x).to<double>()));
  return units::degree_t(-90) - static_cast<units::degree_t>(ang);
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
