// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "Choosers.h"
#include "commands/manual/ManualDrive.h"

class ManualDrive;
class Choosers;

class ConstantSpeed {
public:
  ConstantSpeed(ManualDrive *manualdrive, Choosers *choosers);
  void activate();

private:
ManualDrive *manualdrive;
Choosers *choosers;

double speed;
bool activated;
};

