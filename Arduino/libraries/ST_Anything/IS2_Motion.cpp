#include "IS2_Motion.h"

#include "Constants.h"
#include "Everything.h"

namespace st
{
//private

//public
	//constructor
	IS2_Motion::IS2_Motion(const __FlashStringHelper *name, byte pin, bool iState, bool pullup, long numReqCounts, long inactiveDelay) :
		InterruptSensor2(name, pin, iState, pullup, numReqCounts, inactiveDelay)  //use parent class' constructor
		{
		}
	
	//destructor
	IS2_Motion::~IS2_Motion()
	{
	}
	
// 	void IS2_Motion::init()
// 	{
// 		//get current status of motion sensor by calling parent class's init() routine - no need to duplicate it here!
// 		InterruptSensor2::init();
// 	}

	//called periodically by Everything class to ensure ST Cloud is kept consistent with the state of the motion sensor
	void IS2_Motion::refresh()
	{
		Everything::sendSmartString(getName() + (getStatus() ? F(" active") : F(" inactive")));
	}

	void IS2_Motion::runInterrupt()
	{
		//add the "active" event to the buffer to be queued for transfer to the ST Shield
		Everything::sendSmartString(getName() + F(" active"));
	}
	
	void IS2_Motion::runInterruptEnded()
	{
		//add the "inactive" event to the buffer to be queued for transfer to the ST Shield
		Everything::sendSmartString(getName() + F(" inactive"));
	}

}