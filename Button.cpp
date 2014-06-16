/*
 * Button.cpp
 *
 * Created: 4/30/2014 9:11:02 AM
 *  Author: Ketil Wright
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Button.h"
#include "MessagePump.h"
#include "MessageHandler.h"
#include "ReadButtonState.h"
extern MessagePump g_pump;

Button::Button(ReadButtonState *buttonStateReader, int pin, MsgCode code, bool activeState)
    :
		m_buttonStateReader(buttonStateReader),
        m_activeState(activeState),         // HIGH or LOW, depending on HW impl
        m_mcuPin(pin),                      // arduino pin we're attached to
        m_code(code),                       // code which gets packed into m_msg
        m_logicState(!activeState),         // assume the button is unpressed.
        m_pressedTime(0),                   // milliseconds the button has been held
        m_msg(eButtonActionNone, code),     // dispatched to the message pump
		m_timeLastHold(0)					// throttles hold time messages
{
	m_buttonStateReader->setPinMode(m_mcuPin, INPUT);
}

// Returns true if the button is pressed.
bool Button::isPressed() const
{
    return m_logicState == m_activeState;
}
// Returns the time in milliseconds since the button
// was most recently pressed.
unsigned long Button::getPressedTime() const
{
    return isPressed() ? (millis() - m_pressedTime) : 0;
}

// Restarts the timer. Used to control
// frequency of hold message generation
void Button::resetPressTime()
{
    if(isPressed())
    {
        m_pressedTime = millis();
    }
}

// Returns information about the current
// state of the button.
Msg& Button::getMsg()
{
	m_msg.m_type = eButtonActionNone;
    unsigned long curState = m_buttonStateReader->isPressed(m_mcuPin);
    if(curState != m_logicState)
    {
        if(curState == m_activeState)
        {
            m_msg.m_type = eButtonActionPress;
            m_pressedTime = millis();
        }
        else
        {
            m_msg.m_type = eButtonActionRelease;
            m_pressedTime = 0;
        }
		m_timeLastHold = 0;
    }
	else if(m_logicState == m_activeState) 
	{
		// The button is held. Generate short/med/long message according
		// to how long it's been down
		unsigned long now = millis();
		unsigned long holdTime = now - m_pressedTime;
		if(0 == m_timeLastHold) m_timeLastHold = now;
		
		if(
			(holdTime >= kHoldLongThresholdDuration) && 
			((now % m_timeLastHold) >= kHoldLongMessageThrottleDuration)
		  )
		{
			m_msg.m_type = eButtonActionHoldLong;			  
		}
		else if(
			(holdTime >= kHoldMediumThresholdDuration) && 
			(holdTime < kHoldLongThresholdDuration) &&
			((now % m_timeLastHold) >= kHoldMediumMessageThrottleDuration)
		)
		{
			m_msg.m_type = eButtonActionHoldMedium;
			
		}
		else if(
			(holdTime >= kHoldShortThresholdDuration) && 
			(holdTime < kHoldMediumThresholdDuration) &&
			((now % m_timeLastHold) >= kHoldShortMessageThrottleDuration)
		)
		{
			m_msg.m_type = eButtonActionHoldShort;
		}
		
		if(m_msg.m_type != eButtonActionNone)
		{
			m_timeLastHold = now;
		}
	}
    m_logicState = curState;
    return m_msg;
}


