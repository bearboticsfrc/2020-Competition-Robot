/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <vector>
#include "units_include.h"

struct InputState {
	double z;
	double y;
  InputState( double yee, double zee) {
    y = yee;
    z = zee;
  }
};

class Record {
 public:

  Record();
  
  void SaveYZ(double y, double z);
  void SaveState(InputState state);
  void WriteInputs();

 private:
  std::vector<InputState> inputs;

};