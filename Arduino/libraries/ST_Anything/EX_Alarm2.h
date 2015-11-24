#ifndef ST_EX_ALARM2_H
#define ST_EX_ALARM2_H

#include "Executor.h"

namespace st
{
	class EX_Alarm2 : public Executor
	{

	private:
		
		bool m_bCurrentState; //HIGH or LOW
		bool m_bInvertLogic;
		byte m_nPin;
		unsigned long m_lTimeTurnedOn;
		unsigned long m_lDelayTime;
		bool m_bTimerPending;


		void writeStateToPin();

	public:
		//constructor
		EX_Alarm2(const __FlashStringHelper *name, byte Pin, bool startingState = LOW, bool invertLogic = false, unsigned long delayTime = 0);

		//destructor
		virtual ~EX_Alarm2();

		//initialization function
		virtual void init();

		//called periodically to ensure state of the Alarm Siren is up to date in the SmartThings Cloud (in case an event is missed)
		virtual void refresh();
		
		virtual void update();

		//SmartThings Shield data handler (receives command to turn "both" or "off" the Alarm (digital output)
		virtual void beSmart(const String &str);

		//gets
		virtual byte getPin() const { return m_nPin; }

		//sets
		virtual void setPin(byte pin);

	
	};
}



#endif