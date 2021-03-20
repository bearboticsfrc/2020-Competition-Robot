
#include "Record.h"
#include <iostream>
#include <fstream>

Record::Record() { 
    inputs.clear(); 
}

void Record::SaveYZ(double y, double z) {
    this->SaveState(InputState(y,z));
}

void Record::SaveState(InputState state) {
    inputs.push_back(state);
}

void Record::WriteInputs( ) {
    // loop through inputs and write to a file
    std::ofstream output_file;
    output_file.open("track.txt");
    for(const auto& input: inputs) {
        output_file << input.y << "," << input.z << "\n";
    }
    output_file.close();
}

