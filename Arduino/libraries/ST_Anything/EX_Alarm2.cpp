#include "EX_Alarm2.h"

#include "Constants.h"
#include "Everything.h"

namespace st
{
	//private
	void EX_Alarm2::writeStateToPin()
	{
		digitalWrite(m_nPin, m_bInvertLogic ? !m_bCurrentState : m_bCurrentState);
	}

	//public
	//constructor
	EX_Alarm2::EX_Alarm2(const __FlashStringHelper *name, byte pin, bool startingState, bool invertLogic, unsigned long delayTime) :
		Executor(name),
		m_bCurrentState(startingState),
		m_bInvertLogic(invertLogic),
		m_lDelayTime(delayTime),
		m_lTimeTurnedOn(0),
		m_bTimerPending(false)
	{
		setPin(pin);
	}

	//destructor
	EX_Alarm2::~EX_Alarm2()
	{

	}

	//initialization routine
	void EX_Alarm2::init()
	{
		refresh();	//update ST Cloud with initial data
	}
	
	void EX_Alarm2::update()
	{
		//Turn off digital output if timer has expired
		if ((m_bCurrentState == HIGH) && (millis() - m_lTimeTurnedOn >= m_lDelayTime * 1000))
		{	
			m_bCurrentState = LOW;
			writeStateToPin();
			//Decrement number of active timers
			if (st::Everything::bTimersPending > 0) st::Everything::bTimersPending--;
			m_bTimerPending = false;
			refresh();
		}
	}

	//called periodically to ensure state of the Alarm Siren is up to date in the SmartThings Cloud (in case an event is missed)
	void EX_Alarm2::refresh()
	{
		Everything::sendSmartString(getName() + (m_bCurrentState == HIGH ? F(" siren") : F(" off")));
	}

	//SmartThings Shield data handler (receives command to turn "both" or "off" the Alarm (digital output)
	void EX_Alarm2::beSmart(const String &str)
	{
		String s = str.substring(str.indexOf(' ') + 1);
		if (debug) {
			Serial.print(F("EX_Alarm2::beSmart s = "));
			Serial.println(s);
		}
		if ((s == F("both")) || (s == F("siren")))
		{
			m_bCurrentState = HIGH;
			m_lTimeTurnedOn = millis();
			if (!m_bTimerPending)
			{
				st::Everything::bTimersPending++;
				m_bTimerPending = true;
			}
		}
		else if (s == F("off"))
		{
			m_bCurrentState = LOW;
			
			//Decrement number of active timers
			if (st::Everything::bTimersPending > 0) st::Everything::bTimersPending--;
			m_bTimerPending = false;
		}

		writeStateToPin();

		refresh();
	}

	void EX_Alarm2::setPin(byte pin)
	{
		m_nPin = pin;
		pinMode(m_nPin, OUTPUT);
		writeStateToPin();
	}
}