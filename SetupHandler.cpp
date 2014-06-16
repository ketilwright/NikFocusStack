/*
 * SetupHandler.cpp
 *
 * Created: 4/29/2014 11:35:56 AM
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

#include "SetupHandler.h"
#include "LcdImpl.h"
#include <avr/eeprom.h>

extern uint16_t g_savedFocusAmount;
extern uint8_t g_savedNumFrames;

extern uint16_t EEMEM ePromFocusAmount;
extern uint16_t EEMEM ePromFrameDelay;
extern uint8_t  EEMEM ePromNumFrames;
extern uint8_t  EEMEM ePromRestoreFocus;

extern IMessageHandler *g_pMain;

// the caret position when up/down keys adjust
// m_driveAmount & m_numFrames
#define AmntMenuPos   0
#define FramesMenuPos 5
#define DelayMenuPos  10
#define RestoreFocusPos 13


SetupHandler::SetupHandler(MessagePump *_pump, uint32_t driveAmount, uint32_t frames)
    :
    IMessageHandler(_pump),
    m_driveAmount(driveAmount),
    m_numFrames(frames),
	m_frameDelayMilliseconds(0),
	m_restoreFocus(false)
{
    menu[0] = "Amt";
    menu[1] = "Frm";
	menu[2] = "Dly";
	menu[3] = "Rst";
};
SetupHandler::~SetupHandler()
{}


MsgResp SetupHandler::processMessage(Msg& msg)
{
    MsgResp rsp = eFail;
	// the amount up or down some parameter will be changed
	int change = 0;
    // which button?
    switch(msg.m_code)
    {
        case eDown:
        {
            switch(getCaretCol())
            {
                case AmntMenuPos: 
                {
                    switch(msg.m_type)
                    {
                        case eButtonActionPress: change			= -1;	 break;
						case eButtonActionHoldShort: change		= -10;	 break;
						case eButtonActionHoldMedium: change	= -100;	 break;
						case eButtonActionHoldLong: change		= -1000; break;
                        default: break;
                    }
                    if(change != 0) updateDriveAmountUI(change);
                    break;
                }
                case FramesMenuPos: 
                {
                    switch(msg.m_type)
                    {
                        case eButtonActionPress: change = -1; break;
						case eButtonActionHoldShort: 
						case eButtonActionHoldMedium:
						case eButtonActionHoldLong: change = -10; break;
                        default: break;
                    }
                    if(change != 0) updateFramesUI(change);
                    break;
                }
				case DelayMenuPos:
				{
					switch(msg.m_type)
					{
						case eButtonActionPress: change = -1000; break;
						default: break;
					}
					if(change != 0) updateFrameDelayUI(change);
					break;
				}
				case RestoreFocusPos:
				{
					switch(msg.m_type)
					{
						case eButtonActionPress: change = -1; break;
						default: break;
					}
					if(change != 0) updateRestoreFocusUI(change);
					break;
				}
            }
            break;
        }
        case eUp:
        {
            switch(getCaretCol())
            {
                case AmntMenuPos: // drive amount
                {
                    switch(msg.m_type)
                    {
						case eButtonActionPress: change			= 1;	 break;
						case eButtonActionHoldShort: change		= 10;	 break;
						case eButtonActionHoldMedium: change	= 100;	 break;
						case eButtonActionHoldLong: change		= 1000; break;
                        default: break;
                    }
                    if(change != 0) updateDriveAmountUI(change);
                    break;
                }
                case FramesMenuPos: // frame count
                {
                    switch(msg.m_type)
                    {
                        case eButtonActionPress: change = 1; break;
						case eButtonActionHoldShort:
						case eButtonActionHoldMedium:
						case eButtonActionHoldLong: change = 10; break;
	                    default: break;
                    }
                    if(change != 0) updateFramesUI(change);
                    break;
                }
				case DelayMenuPos:
				{
					switch(msg.m_type)
					{
						case eButtonActionPress: change = 1000; break;
						default: break;
					}
					if(change != 0) updateFrameDelayUI(change);
					break;
				}
				case RestoreFocusPos:
				{
					switch(msg.m_type)
					{
						case eButtonActionPress: change = 1; break;
						default: break;
					}
					if(change != 0) updateRestoreFocusUI(change);
					break;
				}
            }
            break;
        }
        case eLeft:
        {
            if(eButtonActionPress == msg.m_type) 
			{
				switch(getCaretCol())
				{
					case AmntMenuPos:		{ moveCaret(RestoreFocusPos, 1); break; }
					case FramesMenuPos:		{ moveCaret(AmntMenuPos, 1); break; }
					case DelayMenuPos:		{ moveCaret(FramesMenuPos, 1); break; }
					case RestoreFocusPos:	{ moveCaret(DelayMenuPos, 1); break; }
					default: break; // should never hit here						
				}
				break;
			}
			break;
        }
        case eRight:
        {
            if(eButtonActionPress == msg.m_type)
			{
				switch(getCaretCol())
				{
					case AmntMenuPos:		{ moveCaret(FramesMenuPos, 1); break; }
					case FramesMenuPos:		{ moveCaret(DelayMenuPos, 1); break; }
					case DelayMenuPos:		{ moveCaret(RestoreFocusPos, 1); break; }
					case RestoreFocusPos:	{ moveCaret(AmntMenuPos, 1); break; }
					default: break; // should never hit here
				}
			}
			break;
        }
        case eSelect:
        {
            if(eButtonActionPress == msg.m_type)
            {
	            // write any settings to the eprom that have changed.
	            uint16_t savedFocusAmt = eeprom_read_word(&ePromFocusAmount);
	            if(savedFocusAmt != m_driveAmount)
	            {
		            eeprom_write_word(&ePromFocusAmount, m_driveAmount);
	            }
				uint16_t savedFrameDelay = eeprom_read_word(&ePromFrameDelay);
				if(savedFrameDelay != m_frameDelayMilliseconds)
				{
					eeprom_write_word(&ePromFrameDelay, m_frameDelayMilliseconds);
				}
	            uint8_t savedNumFrames = eeprom_read_byte(&ePromNumFrames);
	            if(savedNumFrames != m_numFrames)
	            {
		            eeprom_write_byte(&ePromNumFrames, m_numFrames);
	            }
				uint8_t savedRestoreFocus = eeprom_read_byte(&ePromRestoreFocus);
				if(savedRestoreFocus != m_restoreFocus)
				{
					eeprom_write_byte(&ePromRestoreFocus, m_restoreFocus);
				}
	            msg.m_nextHandler = g_pMain;
	            rsp = eSuccess;
            }
            break;
        } // eSelect handler
        default: break;
    }
    return rsp;
}

void SetupHandler::show()
{
	g_print->clear();
	g_print->setCursor(AmntMenuPos, 0);
	g_print->print(menu[0]);
	g_print->setCursor(FramesMenuPos, 0);
	g_print->print(menu[1]);
	g_print->setCursor(DelayMenuPos, 0);
	g_print->print(menu[2]);
	g_print->setCursor(RestoreFocusPos, 0);
	g_print->print(menu[3]);
	m_caretCol = 0;
    updateDriveAmountUI(0); // 0: don't change, just show the current value
    updateFramesUI(0);      // 0: don't change, just show the current value
	updateFrameDelayUI(0);  // 0: don't change, just show the current value
	updateRestoreFocusUI(0);
    setCaretCol(0);
    showCaret(true);
}
void SetupHandler::updateDriveAmountUI(int change)
{
	// dampen change as we approach the limits
	if(((m_driveAmount + change) > 9999) || ((m_driveAmount + change) < 0))
	{
		change /= 10;
		if(0 == change) change = 1;
	}
	
	m_driveAmount += change;
	// round off to 10/100/1000 depending on change magnitude
	if((change > 1) || (change < -1))
	{
		m_driveAmount -= m_driveAmount % change;
	}
    if(m_driveAmount < 1 ) m_driveAmount = 1;
    if(m_driveAmount > 9999) m_driveAmount = 9999;
    g_print->setCursor(AmntMenuPos + 1, 1);
    g_print->print(F("     "));
    g_print->setCursor(AmntMenuPos + 1, 1);
    g_print->print(m_driveAmount);
}
void SetupHandler::updateFramesUI(int change)
{
    m_numFrames += change;
    if(m_numFrames < 1 ) m_numFrames = 1;
    if(m_numFrames > 100) m_numFrames = 100;
    g_print->setCursor( FramesMenuPos + 1, 1);
    g_print->print(F("   "));
    g_print->setCursor( FramesMenuPos + 1, 1);
    g_print->print(m_numFrames);
}

void SetupHandler::updateFrameDelayUI(int change)
{
	// dampen change as we approach the limits
	if(((m_frameDelayMilliseconds + change) > 9999) || ((m_frameDelayMilliseconds + change) < 0))
	{
		change /= 10;
		if(0 == change) change = 1;
	}
	
	m_frameDelayMilliseconds += change;
	// round off to 10/100/1000 depending on change magnitude
	if((change > 1) || (change < -1))
	{
		m_frameDelayMilliseconds -= m_frameDelayMilliseconds % change;
	}
    if(m_frameDelayMilliseconds < 0 ) m_frameDelayMilliseconds = 0;
    if(m_frameDelayMilliseconds > 9999) m_frameDelayMilliseconds = 9999;
    g_print->setCursor(DelayMenuPos + 1, 1);
    g_print->print(F("   "));
    g_print->setCursor(DelayMenuPos + 1, 1);
    g_print->print(m_frameDelayMilliseconds/1000);
}

void SetupHandler::updateRestoreFocusUI(int change)
{
	g_print->setCursor(RestoreFocusPos + 1, 1);
	g_print->print(F("   "));		
	g_print->setCursor(RestoreFocusPos + 1, 1);
	if(0 != change) m_restoreFocus = !m_restoreFocus;
	g_print->print( m_restoreFocus ? F("Y") : F("N"));
}
