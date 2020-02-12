#include "Util.h"
#include <frc/smartdashboard/SmartDashboard.h>

const bool PID_TUNING = false;

void initDashboardValue(wpi::StringRef name, double defaultValue) {
    if (frc::SmartDashboard::GetNumber(name, 0.0) == 0.0) {
        frc::SmartDashboard::PutNumber(name, defaultValue);
    }
}