//******************************************************************************************
//  File: IS_Motion2.cpp
//  Authors: Dan G Ogorchock & Daniel J Ogorchock (Father and Son)
//  Author: Bryce Durham
//
//  Summary:  IS_Motion2 is a class which implements the SmartThings "Motion Sensor" device capability.
//			  It inherits from the st::InterruptSensor class.
//
//			  Create an instance of this class in your sketch's global variable section
//			  For Example:  st::IS_Motion2 sensor6("motion", PIN_CONTACT, HIGH);
//
//			  st::IS_Motion2() constructor requires the following arguments
//				- String &name - REQUIRED - the name of the object - must match the Groovy ST_Anything DeviceType tile name
//				- byte pin - REQUIRED - the Arduino Pin to be used as a digital input
//				- bool iState - REQUIRED - LOW or HIGH - determines which value indicates the interrupt is true
//				- bool internalPullup - OPTIONAL - true == INTERNAL_PULLUP
//				- long numReqCounts - OPTIONAL - number of counts before changing state of input (prevent false alarms)
//
//  Change History:
//
//    Date        Who            What
//    ----        ---            ----
//    2015-01-03  Dan & Daniel   Original Creation
//	  2015-03-17  Dan			 Added optional "numReqCounts" constructor argument/capability
//    2015-11-15  Bryce Durham   Adapted IS_Contact as IS_Motion2
//
//
//******************************************************************************************

#include "IS_Motion2.h"

#include "Constants.h"
#include "Everything.h"

namespace st
{
//private

//public
	//constructor
	IS_Motion2::IS_Motion2(const __FlashStringHelper *name, byte pin, bool iState, bool pullup, long numReqCounts) :
		InterruptSensor(name, pin, iState, pullup, numReqCounts)  //use parent class' constructor
		{
		}
	
	//destructor
	IS_Motion2::~IS_Motion2()
	{
	}
	
	void IS_Motion2::init()
	{
		//get current status of motion sensor by calling parent class's init() routine - no need to duplicate it here!
		InterruptSensor::init();
	}

	//called periodically by Everything class to ensure ST Cloud is kept consistent with the state of the motion sensor
	void IS_Motion2::refresh()
	{
		Everything::sendSmartString(getName() + (getStatus() ? F(" active") : F(" inactive")));
	}

	void IS_Motion2::runInterrupt()
	{
		//add the "closed" event to the buffer to be queued for transfer to the ST Shield
		Everything::sendSmartString(getName() + F(" active"));
	}
	
	void IS_Motion2::runInterruptEnded()
	{
		//add the "open" event to the buffer to be queued for transfer to the ST Shield
		Everything::sendSmartString(getName() + F(" inactive"));
		//TODO wait for 1 minute (make it configurable)
	}

}