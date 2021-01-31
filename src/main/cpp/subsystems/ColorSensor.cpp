/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/util/Color.h>
#include <string>
#include <frc/DriverStation.h>
#include "subsystems/ColorSensor.h"
#include "units_include.h"

static constexpr auto i2cPort = frc::I2C::Port::kOnboard;

static constexpr frc::Color kBlueTarget = frc::Color(0.143, 0.427, 0.429);
        // GREEN: R: 0.14, G: 0.6, B: 0.25
static constexpr frc::Color kGreenTarget = frc::Color(0.197, 0.6, 0.240);
        // RED: R: 0.55, G: 0.33, B: 0.11
static constexpr frc::Color kRedTarget = frc::Color(0.561, 0.33, 0.114);
        // YELLOW: R: 0.31, G: 0.57, B: 0.1
static constexpr frc::Color kYellowTarget = frc::Color(0.361, 0.524, 0.113);

ColorSensor::ColorSensor() :
    m_colorSensor(i2cPort)
{
    m_colorMatcher.AddColorMatch(kBlueTarget);
    m_colorMatcher.AddColorMatch(kGreenTarget);
    m_colorMatcher.AddColorMatch(kRedTarget);
    m_colorMatcher.AddColorMatch(kYellowTarget);
}

enum WheelColor {
    Red,
    Blue,
    Green,
    Yellow,
    Unknown,
};

std::string color_to_string(WheelColor color) {
    switch (color) {
        case WheelColor::Red: return "Red";
        case WheelColor::Blue: return "Blue";
        case WheelColor::Green: return "Green";
        case WheelColor::Yellow: return "Yellow";
        case WheelColor::Unknown: return "Unknown";
        default: return "INVALID COLOR ENUM";
    }
}

WheelColor get_target_color(){
    std::string gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
    if(gameData.length() > 0)
    {
        switch (gameData[0])
        {
            case 'B' :
                return WheelColor::Blue;
            case 'G' :
                return WheelColor::Green;
            case 'R' :
                return WheelColor::Red;
            case 'Y' :
                return WheelColor::Yellow;
            default :
                return WheelColor::Unknown;
        }
    } else {
        return WheelColor::Unknown;
    }
}

// This method will be called once per scheduler run
void ColorSensor::Periodic() {
    /* GetColor() returns a normal color, instead of a raw color
    * Needs to be within a few inches and well light
    */
    frc::Color detectedColor = m_colorSensor.GetColor();

    double confidence = 0.0;
    frc::Color matchedColor = m_colorMatcher.MatchClosestColor(detectedColor, confidence);

    WheelColor wheelColor;

    if (matchedColor == kBlueTarget) {
        wheelColor = WheelColor::Blue;
    } else if (matchedColor == kRedTarget) {
        wheelColor = WheelColor::Red;
    } else if (matchedColor == kGreenTarget) {
        wheelColor = WheelColor::Green;
    } else if (matchedColor == kYellowTarget) {
        wheelColor = WheelColor::Yellow;
    } else  {
        wheelColor = WheelColor::Unknown;
    }

    // outputs color into shuffleboard

    /*frc::SmartDashboard::PutNumber("Red", detectedColor.red);
    frc::SmartDashboard::PutNumber("Green", detectedColor.green);
    frc::SmartDashboard::PutNumber("Blue", detectedColor.blue);
    frc::SmartDashboard::PutNumber("Confidence", confidence);*/
    frc::SmartDashboard::PutString("Detected Color", color_to_string(wheelColor));
}