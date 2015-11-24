#ifndef ST_IS2_MOTION_H
#define ST_IS2_MOTION_H

#include "InterruptSensor2.h"

namespace st
{
	class IS2_Motion: public InterruptSensor2
	{
		private:
			//inherits everything necessary from parent InterruptSensor Class
			
		public:
			//constructor - called in your sketch's global variable declaration section
			IS2_Motion(const __FlashStringHelper *name, byte pin, bool iState, bool internalPullup = false, long numReqCounts = 0, long inactiveDelay = 0); //(defaults to NOT using internal pullup resistors, and required counts = 0)
			
			//destructor
			virtual ~IS2_Motion();
			
			//initialization function
// 			virtual void init();

			//called periodically by Everything class to ensure ST Cloud is kept consistent with the state of the contact sensor
			virtual void refresh();

			//handles what to do when interrupt is triggered 
			virtual void runInterrupt();

			//handles what to do when interrupt is ended 
			virtual void runInterruptEnded();
	
	};
}


#endif