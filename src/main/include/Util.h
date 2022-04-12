#include <fmt/core.h>
#include "units_include.h"

namespace rev {
    class CANSparkMax;
}

extern const bool PID_TUNING;


// Creates a smart dashboard entry with the given name and value
// if it does not already exist.
void initDashboardValue(std::string_view name, double defaultValue);

void temperatureCheck(rev::CANSparkMax &motor);