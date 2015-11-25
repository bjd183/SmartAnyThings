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
				m_lInterruptMillis = millis();
			}
			if (pinValue == m_bInterruptState && !m_bStatus) //new interrupt
			{
				m_lCurrentDownCount = m_lRequiredCounts;
				m_lCurrentUpCount++;
				if (m_lCurrentUpCount >= m_lRequiredCounts)
				{
					m_bStatus = true;
					m_bInitRequired = false;
					runInterrupt();
				}
			}
			else if ((pinValue != m_bInterruptState && m_bStatus) || m_bInitRequired) //interrupt has ended OR Init called us
			{
				m_lCurrentUpCount = 0;
				m_lCurrentDownCount--;
				if (m_bInitRequired || m_lCurrentDownCount <= 0 && millis() - m_lInterruptMillis >= m_lInactiveDelay * 1000)
				{
					m_bStatus = false;
					m_bInitRequired = false;
					runInterruptEnded();
				}
			}
	}

//public
	//constructor
	InterruptSensor2::InterruptSensor2(const __FlashStringHelper *name, byte pin, bool iState, bool pullup, long numReqCounts, unsigned long inactiveDelay) :
		Sensor(name),
		m_bInterruptState(iState),
		m_bStatus(false),
		m_bPullup(pullup),
		m_bInitRequired(true),
		m_lRequiredCounts(numReqCounts),
		m_lCurrentUpCount(0),
		m_lCurrentDownCount(numReqCounts),
		m_lInactiveDelay(inactiveDelay)
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