/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/automatic/PlaybackDrive.h"
#include "Robot.h"
#include "units_include.h"
#include <fstream>
#include <iostream>
#include <string>

PlaybackDrive::PlaybackDrive(Drivetrain *drive) :
  drivetrain(drive),
  inputs()
{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({ drive });
}

// Called when the command is initially scheduled.
void PlaybackDrive::Initialize() {
  // loop through inputs and write to a file
    std::string line;
    std::ifstream input_file;
    input_file.open("/home/lvuser/deploy/track.txt");
    if (input_file.is_open()){
      while (getline(input_file, line)){
        std::string::size_type sz;
        double y = std::stod(line, &sz);
        double z = std::stod(line.substr(sz));

        //std::cout << "Y = " << y << " Z = " << z << "\n";
        inputs.push_back(InputState(y , z));
      }
      std::cout << "read inputs size=" << inputs.size() << "\n";
      input_file.close();
    }
    iterator = inputs.begin();
}

// Called repeatedly when this Command is scheduled to run
void PlaybackDrive::Execute() {
  double forward = -iterator->y;
  
  double turn = 0.5 * iterator->z;
  std::cout << "DRIVING!!! y="<<iterator->y << " z="<<iterator->z <<"\n";
  iterator++;

  double leftSpeed = forward + turn;
  double rightSpeed = forward - turn;

  drivetrain->SetSpeeds(leftSpeed, rightSpeed);
}

// Called once the command ends or is interrupted.
void PlaybackDrive::End(bool interrupted) {}

// Returns true when the command should end.
bool PlaybackDrive::IsFinished() { 
  bool done = iterator == inputs.end();
  if (done) std::cout << "done driving\n;";
  return done;
  }
