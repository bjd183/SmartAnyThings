#include "InterruptSensor2.h"

#include "Constants.h"
#include "Everything.h"

namespace st
{
//private

	//Checks to see if the pin has changed state.  If so calls appropriate function.
	void InterruptSensor2::checkIfTriggered()
	{
			bool pinValue = digitalRead(m_nInterruptPin);
			if (pinValue == m_bInterruptState) //last time in interrupt state
			{
				m_interruptMillis = millis();
			}
			if (pinValue == m_bInterruptState && !m_bStatus) //new interrupt
			{
				m_nCurrentDownCount = m_nRequiredCounts;
				m_nCurrentUpCount++;
				if (m_nCurrentUpCount >= m_nRequiredCounts)
				{
					m_bStatus = true;
					m_bInitRequired = false;
					runInterrupt();
				}
			}
			else if ((pinValue != m_bInterruptState && m_bStatus) || m_bInitRequired) //interrupt has ended OR Init called us
			{
				m_nCurrentUpCount = 0;
				m_nCurrentDownCount--;
				if (m_nCurrentDownCount <= 0 && millis() - m_interruptMillis >= m_inactiveDelay)
				{
					m_bStatus = false;
					m_bInitRequired = false;
					runInterruptEnded();
				}
			}
	}

//public
	//constructor
	InterruptSensor2::InterruptSensor2(const __FlashStringHelper *name, byte pin, bool iState, bool pullup, long numReqCounts, long inactiveDelay) :
		Sensor(name),
		m_bInterruptState(iState),
		m_bStatus(false),
		m_bPullup(pullup),
		m_bInitRequired(true),
		m_nRequiredCounts(numReqCounts),
		m_nCurrentUpCount(0),
		m_nCurrentDownCount(numReqCounts),
		m_inactiveDelay(inactiveDelay)
		{
			setInterruptPin(pin);
		}
	
	//destructor
	InterruptSensor2::~InterruptSensor2()
	{
	
	}
	
	//initialization function
	void InterruptSensor2::init()
	{
		checkIfTriggered();
	}
	
	//update function 
	void InterruptSensor2::update()
	{
		checkIfTriggered();
	}

	//handles start of an interrupt - all derived classes should implement this virtual function
	void InterruptSensor2::runInterrupt()
	{
		if(debug)
		{
			Everything::sendSmartString(getName()+F(" triggered ") + (m_bInterruptState?F("HIGH"):F("LOW)")));
		}
	}
	
	//handles the end of an interrupt - all derived classes should implement this virtual function
	void InterruptSensor2::runInterruptEnded()
	{
		if(debug)
		{
			Everything::sendSmartString(getName()+F(" ended ") + (m_bInterruptState?F("LOW)"):F("HIGH)")));
		}
	}
	
	//sets the pin to be monitored, and set the Arduino pinMode based on constructor data
	void InterruptSensor2::setInterruptPin(byte pin)
	{
		m_nInterruptPin=pin;
		if(!m_bPullup)
		{
			pinMode(m_nInterruptPin, INPUT);
		}
		else
		{
			pinMode(m_nInterruptPin, INPUT_PULLUP);
		}
	}
	
	//debug flag to determine if debug print statements are executed (set value in your sketch)
	bool InterruptSensor2::debug=false;
}