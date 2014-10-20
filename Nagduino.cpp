/*
	Nagduino.cpp - Library for communicating with Nagios via NRDP
	Created by Trevor McDonald tmcdonald@nagios.com, June 1, 2014.
	Released into the public domain.
*/

#include "Nagduino.h"

// Initializes Nagduino client
// Currently doesn't do anything - left it in for future use
Nagduino::Nagduino()
{
}

// Sends an arbitrary NRDP message
// Example:    sendNRDP("Nagduino", "Window Sensor", 2, "Window is open!");
void Nagduino::sendNRDP(char* host, char* service, int serviceState, char* serviceMessage)
{
	// 61 is the length of the NRDP command struct - the + 1 is the service state
	int postLength = 61 + strlen(host) + strlen(service) + 1 + strlen(serviceMessage) + strlen(token);
	EthernetClient client;
	if (Ethernet.begin(mac) == 0) {
		// Try to configure using IP address instead of DHCP:
		Ethernet.begin(mac, ip);
	} else {
		// Take appropriate actions here 
	}
	if (client.connect(nagios, 80)) {
		// Make a HTTP POST request:
		client.println("POST /nrdp/ HTTP/1.1");
		// Host section does not actually need to make sense, but needs to be present
		// TODO:  Find a way to cast the byte[4] host address to a char[4] array for printing (see below comment)
		client.print("Host: 192.168.1.1");
		// Try to get it to work like this:
		//client.print("Host: ");
		//client.println((char)nagios);
		client.println("Connection: keep-alive");
		client.println("Content-Type: application/x-www-form-urlencoded");
		client.print("Content-Length: ");
		client.println(postLength);
		client.println("");
		// Begin sending content of NRDP message
		client.print("cmd=submitcmd&token=");
		client.print(token);
		client.print("&command=PROCESS_SERVICE_CHECK_RESULT;");
		client.print(host);
		client.print(";");
		client.print(service);
		client.print(";");
		client.print(serviceState);
		client.print(";");
		client.println(serviceMessage);
	} else {
		// Take appropriate actions here
	}
}