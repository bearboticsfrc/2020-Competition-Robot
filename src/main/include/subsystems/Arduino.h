/*
 * Arduino.h
 *
 *  Created on: Jan 11, 2019
 *      Author: super-tails
 */

#ifndef SRC_SUBSYSTEMS_ARDUINO_H_
#define SRC_SUBSYSTEMS_ARDUINO_H_

#include <frc/I2C.h>
#include <stdint.h>
#include <tuple>

struct SensorFrame {
	double x;
	double y;
	double width;
	double height;
};

class Arduino {
public:
	Arduino() = default;
	Arduino(const Arduino&) = delete;
	Arduino(Arduino&&) = default;

	// If the boolean value is false, the data is invalid
	std::pair< std::vector<SensorFrame>, bool > readData();

private:
	// Raw data recieved from the Arduino
	struct RxFrame {
		uint16_t x = 0;
		uint16_t width = 0;
		uint8_t y = 0;
		uint8_t height = 0;
	};

	std::vector<RxFrame> readRawData();

	static constexpr const int address = 80;

	frc::I2C m_i2c{ frc::I2C::Port::kOnboard, address };
};



#endif /* SRC_SUBSYSTEMS_ARDUINO_H_ */