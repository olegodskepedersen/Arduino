// Scott Camarena
//
// February 2013
// GlobalResolve Weather Warning System
// - Arduino Sensor System Library
//============================================================

#ifndef ASSYS_H
#define ASSYS_H
#include <Arduino.h>
#include <SPI.h>

// Define which serial to use,
//  Change return values to SoftwareSerial "SerialBT"
//  Keep error returns to regular Serial
#define SERIALBT Serial
#define DELAYTIME 2000

#define DHT22_PIN 7

DHT22 humidSensor(DHT22_PIN);
DHT22_ERROR_t errorCode;
unsigned long lastReadTime = 0;
//SoftwareSerial SerialBT(3, 4);

// Returns whether or not new vals were grabbed
bool humid_grabNewVals( DHT22& hs, unsigned long& lastReadTime )
{
	// If at least DELAYTIME since last read
	//  grab new values, else return
	if( millis() > lastReadTime + DELAYTIME )
	{
		errorCode = hs.readData();
		lastReadTime = millis();
	}
	else return false;
	
	switch(errorCode)
	{
	case DHT_ERROR_NONE:
		Serial.println("Got Data");
		return true;
	case DHT_ERROR_CHECKSUM:
		Serial.println("Checksum Error");
		break;
	case DHT_BUS_HUNG:
		Serial.println("BUS Hung");
		break;
	case DHT_ERROR_NOT_PRESENT:
		Serial.println("Not Present");
		break;
	case DHT_ERROR_ACK_TOO_LONG:
		Serial.println("ACK Timeout");
		break;
	case DHT_ERROR_SYNC_TIMEOUT:
		Serial.println("Sync Timeout");
		break;
	case DHT_ERROR_DATA_TIMEOUT:
		Serial.println("Data Timeout");
		break;
	case DHT_ERROR_TOOQUICK:
		Serial.println("Data Timeout");
		break;
	}
	
	return false;
}


// Takes preference for celcius or farenheit
// Returns average temp from both sensors
short int getTemp( char cf )
{
	humid_grabNewVals( humidSensor, lastReadTime );
	short int hsTemp = humidSensor.getTemperatureCInt();

	short int psTemp = hsTemp; // Change
	return (hsTemp + psTemp)/2;
}

short int getPress()
{
	return 0;
}

short int getHumid()
{
	humid_grabNewVals( humidSensor, lastReadTime );
	return humidSensor.getHumidityInt();
}

String readInCommand()
{
	String comm = "";
	// Wait until input is available
	while( !SERIALBT.available() );
	// Grab until space or newline
	while( SERIALBT.available() )
	{
		char inChar = (char)SERIALBT.read();
		if( inChar == ' ' || inChar == '\n' )
			if( comm != "" ) return comm;
		else
			comm += inChar;	
	}
	return "";
}

bool execCommand( String comm )
{
	switch( comm.charAt(0) )
	{
	case 't':
	case 'T':
		SERIALBT.println( getTemp(comm.charAt(1)) );
		return 0;
	case 'p':
	case 'P':
		SERIALBT.println( getPress() );
		return 0;
	case 'h':
	case 'H':
		SERIALBT.println( getHumid() );
		return 0;
	
	default:
		return 1;
	}
}

























#endif
