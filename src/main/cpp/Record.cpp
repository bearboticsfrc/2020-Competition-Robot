
#include "Record.h"
#include <iostream>
#include <fstream>

Record::Record() :
active(false)
{ 
    inputs.clear(); 
}

void Record::SaveYZ(double y, double z) {
    //std::cout << "saving y="<<y << ",z="<<z<<"\n";
    this->SaveState(InputState(y,z));
}

void Record::SaveState(InputState state) {
    inputs.push_back(state);
}

void Record::WriteInputs( ) {
    SaveYZ(0, 0);
    // loop through inputs and write to a file
    std::ofstream output_file;
    output_file.open("/home/lvuser/deploy/track.txt", std::ofstream::trunc);
    for(const auto& input: inputs) {
        output_file << input.y << " " << input.z << "\n";
    }
    output_file.close();

}

void Record::ClearInputs() {
    inputs.clear();
}

void Record::activate() {
    active = !active;

    if (active){
        std::cout << "inputs cleared\n";
        ClearInputs();
    }
    else
    {
        std::cout << "inputs written to file\n";
        WriteInputs();
    }
}

