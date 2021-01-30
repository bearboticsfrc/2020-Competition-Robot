#include "Util.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <rev/CANSparkMax.h>
#include "units_include.h"

const bool PID_TUNING = false;

void initDashboardValue(wpi::StringRef name, double defaultValue) {
    if (frc::SmartDashboard::GetNumber(name, 0.0) == 0.0) {
        frc::SmartDashboard::PutNumber(name, defaultValue);
    }
}

void temperatureCheck(rev::CANSparkMax &motor) {
    double temp = motor.GetMotorTemperature(); //Grabs temperature value as a double in Celcius
    //If temperature is over 80, calculate number of 0.5s over.
    if(temp >= 80.0){
        temp = (temp - 79.0) / 0.5;
    }else{
        temp = 0.0;
    }
    //Decrease voltage by 1 amp every 0.5 degrees.
    motor.SetSmartCurrentLimit(40 - temp);
}