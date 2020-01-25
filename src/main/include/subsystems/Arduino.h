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
	std::pair< SensorFrame, bool > readData();

	bool handshake();

private:
	// Raw data recieved from the Arduino
	struct RxFrame {
		static constexpr const uint32_t magic_number = 0x5FAF55AA;
		uint32_t verification = 0; // Recieved value should always be equal to 0x5FAF55AA, otherwise discard data
		uint16_t x = 0;
		uint16_t y = 0;
		uint16_t width = 0;
		uint16_t height = 0;
	};

	// Raw data sent to the Arduino
	struct TxFrame {
		static constexpr const uint32_t magic_number = 0xAA55FAF5;
		uint32_t verification = magic_number; // The Arduino should return an invalid RxFrame if this is not equal to 0xAA55FAF5
	};

	RxFrame readRawData();

	static constexpr const int address = 80;

	frc::I2C m_i2c{ frc::I2C::Port::kOnboard, address };
};



#endif /* SRC_SUBSYSTEMS_ARDUINO_H_ */