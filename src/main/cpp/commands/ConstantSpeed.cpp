// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ConstantSpeed.h"
#include "units_include.h"

ConstantSpeed::ConstantSpeed(ManualDrive *manualDrive, Choosers *choosers) :
  manualdrive(manualdrive),
  choosers(choosers),
  activated(false)
 {

} 

void ConstantSpeed::activate() {
  activated = !activated;

  switch(choosers->constantSpeedChoice()){
    case ConstantSpeedChoice::Default:
      speed = 0.0;
      break;
    case ConstantSpeedChoice::Option1:
      speed = .05;
      break;
    case ConstantSpeedChoice::Option2:
      speed = .1;
      break;
    case ConstantSpeedChoice::Option3:
      speed = .15;
      break;
    default:
      std::cerr << "UNHANDLED OPTION FOR CONSTANT SPEED\n";
      speed = 0.0;
  }
}

