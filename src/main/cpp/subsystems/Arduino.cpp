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

bool Arduino::handshake() {
	// Generate a random digit to send, we should recieve that digit + 1
	srand(time(0));

	int value = rand() % 9; // Value between 0 and 8, to make sure it fits in one digit

	unsigned char send_buffer[] = "Sending _";
	send_buffer[sizeof(send_buffer) - 2] = value + '0';

	unsigned char recieve_buffer[100] = { 0xFF, 0xFF }; // Digit and terminating zero

	std::cout << "Sending the string:\n" << send_buffer << '\n';

	m_i2c.WriteBulk(send_buffer, sizeof(send_buffer));
	m_i2c.ReadOnly(2, recieve_buffer);

	std::cout << "Recieved: 0x" << std::hex << int(recieve_buffer[0]) << "\n";
	std::cout << "Recieved: 0x" << std::hex << int(recieve_buffer[1]) << "\n";

	return (recieve_buffer[0] - '0' == value + 1);
}

template< typename T >
T correctEndianness(T value) {
	unsigned char *data = reinterpret_cast< unsigned char* >(&value);
	
	std::reverse(data, data + sizeof(T));

	return *reinterpret_cast< T* >(data);
}

// TODO: Check endianness here too
std::pair< SensorFrame, bool > Arduino::readData() {
	RxFrame rawFrame = readRawData();

	// Check for basic transmission errors
	if (rawFrame.verification != RxFrame::magic_number) {
		std::cout << "Received incorrect verification 0x" << std::hex << rawFrame.verification << "\n";
		return { {}, false };
	}

	return {
		{ 
			static_cast<double>(rawFrame.x),
			static_cast<double>(rawFrame.y),
			static_cast<double>(rawFrame.width),
			static_cast<double>(rawFrame.height)
		},
		true
	};
}

// TODO: Check endianness
// RoboRio is likely big endian and Arduinos are little endian
Arduino::RxFrame Arduino::readRawData() {
	TxFrame txFrame{ TxFrame::magic_number };
	RxFrame rxFrame{ 0, 0, 0 };

	m_i2c.WriteBulk(reinterpret_cast< uint8_t* >(&txFrame), sizeof(txFrame));
	m_i2c.ReadOnly(sizeof(RxFrame), reinterpret_cast< uint8_t* >(&rxFrame));

	return rxFrame;
}