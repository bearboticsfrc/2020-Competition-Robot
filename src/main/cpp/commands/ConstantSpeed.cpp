// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ConstantSpeed.h"
#include "units_include.h"

ConstantSpeed::ConstantSpeed(Choosers *choosers) :
  choosers(choosers),
  active(false)
{
} 

void ConstantSpeed::activate() {
  active = !active;
  std::cout << "Constant Speed Activated";
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
  
  std::cout << "Constant Speed Finished\n";
}

bool ConstantSpeed::isActivated() {
  return active;
}

double ConstantSpeed::getSpeed() {
  return speed;
}
