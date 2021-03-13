// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Compressor.h"

Compressor::Compressor(Choosers *choosers) :
choosers(choosers) 
{
  // Use addRequirements() here to declare subsystem dependencies.
  std::cout << ":)\n";
}

// Called when the command is initially scheduled.
void Compressor::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void Compressor::Execute() {
  frc::Compressor compressor{0};

  switch (choosers->compressorChoice()) {
    case CompressorChoice::On:
      isActive = true;
      break;
    case CompressorChoice::Off:
      isActive = false;
      break;
    default:
      isActive = true;
  }

  if (isActive == false) {
    std::cout << "Stopping Compressor\n";
    compressor.Stop();  
  }
  else
  {
    std::cout << "Starting Compressor\n";
    compressor.Start();
  }
}

// Called once the command ends or is interrupted.
void Compressor::End(bool interrupted) {}

// Returns true when the command should end.
bool Compressor::IsFinished() {
  return false;
}

/*void Compressor::activate(Choosers *choosers){
  switch (choosers.compressorChoice) {
    case CompressorChoice::On:
      compressor.Start();
  }
}*/
