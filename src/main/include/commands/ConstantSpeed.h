#pragma once

#include "Choosers.h"

class ConstantSpeed {
public:
  ConstantSpeed(Choosers *choosers);
  void activate();

  bool isActivated();
  double getSpeed();

private:
  Choosers *choosers;

  double speed;
  bool active;
};

