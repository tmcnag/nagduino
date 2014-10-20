/*
    A sample NRDP client for arduino
	
	Sends a single NRDP packet when a window is detected as open
	using a simple magnetic switch
	
	The packet says that the "Living Room Window" service on
	the "Nagduino" host is in a Critical state with the status
	of "Window is open!"
	
	The mac, ip, nagios, and token variables need to be set
	to values that make sense in your environment
*/

#include <SPI.h>
#include <Ethernet.h>
#include <Nagduino.h>

/* The following four variables are required */

byte mac[6]    = { 0x4E, 0x61, 0x67, 0x69, 0x6F, 0x73 };	// MAC address of Arduino
byte ip[4]     = { 192,168,1,17 };	// Arduino IP
byte nagios[4] = { 192,168,1,29 };	// Nagios IP
char token[]   = "sometoken";		// NRDP token

int winClosed = 1;     // State of window (1 = closed, 0 = open)
int passiveSent = 0;   // Whether NRDP result has been sent

Nagduino nagduino;     // Nagduino object for sending NRDP

void setup()
{
  Serial.begin(9600);
  pinMode(7, INPUT_PULLUP); // Attach magnetic sensor (or button, switch, etc) to pin 7
}

void loop()
{
  winClosed = digitalRead(7); // Read state of pin/switch
  
  if (!winClosed) {
    if (!passiveSent) {
      passiveSent = 1;
      nagduino.sendNRDP("Nagduino", "Living Room Window", 2, "Window is open!");
    }
  } else {
    passiveSent = 0;
  }
  delay(100);
}
