/*
 * Arduino.c
 *
 *  Created on: Jan 11, 2019
 *      Author: super-tails
 */

#include "subsystems/Arduino.h"
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>

// "Sending _"
// "_"

// "Sending 5"
// "6"

template< typename T >
T correctEndianness(T value) {
	unsigned char *data = reinterpret_cast< unsigned char* >(&value);
	
	std::reverse(data, data + sizeof(T));

	return *reinterpret_cast< T* >(data);
}

// TODO: Check endianness here too
std::pair< std::vector<SensorFrame>, bool > Arduino::readData() {
	std::vector<RxFrame> rawFrames = readRawData();

	if (rawFrames.size() == 0) {
		return {
			std::vector<SensorFrame>(),
			false
		};
	}

	std::vector<SensorFrame> result;

	for (auto rawFrame : rawFrames) {
		result.push_back({
			static_cast<double>(rawFrame.x),
			static_cast<double>(rawFrame.y),
			static_cast<double>(rawFrame.width),
			static_cast<double>(rawFrame.height)
		});
	}

	return {
		result,
		true
	};
}

// TODO: Check endianness
// RoboRio is likely big endian and Arduinos are little endian
std::vector<Arduino::RxFrame> Arduino::readRawData() {
	uint8_t len = 0;
	m_i2c.ReadOnly(1, &len);

	std::vector<RxFrame> buffer(len, RxFrame{ 0, 0, 0, 0 });
	m_i2c.ReadOnly(6 * len, reinterpret_cast< uint8_t* >(buffer.data()));

	return buffer;
}