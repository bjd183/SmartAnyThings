
#ifndef ST_INTERRUPTSENSOR2_H
#define ST_INTERRUPTSENSOR2_H

#include "Sensor.h"

namespace st
{
	class InterruptSensor2: public Sensor
	{
		private:
			byte m_nInterruptPin;	//pin that will be monitored for change of state
			bool m_bInterruptState; //LOW or HIGH - determines which value indicates the interrupt is true (i.e. LOW=Falling Edge, HIGH=Rising Edge)
			bool m_bStatus;			//true == interrupted
			bool m_bPullup;			//true == Internal Pullup resistor required, set in constructor call in your sketch
			bool m_bInitRequired;	//
			long m_nRequiredCounts;	//Number of required counts (checks of the pin) before believing the pin is high/low
			long m_nCurrentUpCount;
			long m_nCurrentDownCount;
			unsigned long m_interruptMillis; //time of most recent interrupt state
			long m_inactiveDelay;  //delay before sending inactive

			void checkIfTriggered(); 
			
		public:
			//constructor
			InterruptSensor2(const __FlashStringHelper *name, byte pin, bool iState, bool internalPullup=false, long numReqCounts=0, long inactiveDelay); //(defaults to NOT using internal pullup resistors, and required counts = 0)
			
			//destructor
			virtual ~InterruptSensor2();
			
			//initialization function
			virtual void init();

			//update function 
			virtual void update();

			//handles what to do when interrupt is triggered - all derived classes should implement this virtual function
			virtual void runInterrupt();

			//handles what to do when interrupt is ended - all derived classes should implement this virtual function
			virtual void runInterruptEnded();
			
			//gets
			inline byte getInterruptPin() const {return m_nInterruptPin;}
			inline bool getInterruptState() const {return m_bInterruptState;}
			inline bool getStatus() const {return m_bStatus;}	//whether or not the device is currently interrupted
			
			
			//sets
			void setInterruptPin(byte pin);
			void setInterruptState(bool b) {m_bInterruptState=b;}
	
			//debug flag to determine if debug print statements are executed (set value in your sketch)
			static bool debug;
	
	};
}


#endif