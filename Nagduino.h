/*
	Nagduino.h - Library for communicating with Nagios via NRDP
	Created by Trevor McDonald tmcdonald@nagios.com, June 1, 2014.
	Released into the public domain.
*/

#ifndef Nagduino_h
#define Nagduino_h

#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>

// These need to be defined globally in the main Arduino code
extern byte mac[];
extern byte ip[];
extern byte nagios[];
extern char token[];

class Nagduino
{
	public:
		Nagduino();
		void sendNRDP(char* host, char* service, int serviceState, char* serviceMessage);
};

#endif