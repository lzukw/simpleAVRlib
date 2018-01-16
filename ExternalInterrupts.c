/*
    ExternalInterrupts.cpp - A Library for Interrupts caused by 
    voltage-level-changes on the INTx-Pins of AVR-Microcontrollers. 
    This is part of the simpleAVRLib-Library.
    Copyright (c) 2018 Wolfgang Zukrigl

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */ 

/*
Most GPIO-Pins of AVR-Microcontrollers have one or more alternative functions.
If the alternative function is used, then a Pin doesn't work as GPIO-Pin any
longer but has it's alternative function. One alternative function is
being an "external interrupt pin". 

The Pins PD2 and PD3 of an ATmega328p have the alternative function INT0 and 
INT1 (see section "pin description" in the datasheet. 

The Atmega2560 has Pins INT0, INT1, ...INT7 which are located at some pins from
port D and E. 
*/

#include "ExternalInterrupts.h"
#include <stddef.h>
#include <avr/io.h>

//////////////////////////////////////////////////////////////////////////
// Pointers to callback-Functions
//////////////////////////////////////////////////////////////////////////

//glboal pointers are always initialized with NULL
callbackFunction* callbacks[EXT_INT_COUNT]; 
    
//////////////////////////////////////////////////////////////////////////
// C-Functions-API
//////////////////////////////////////////////////////////////////////////

void setExtIntEventType( uint8_t extIntNumber, uint8_t extIntEventType )
{
    if (extIntNumber >= EXT_INT_COUNT) return;
    
    extIntEventType &= 0x03; //Only allow 0..3
    
    if (extIntNumber < 4)
    {
        //first clear Bits ISCn1 and ISCn0 in the EICRA-Register (n is the
        //number of the external Interrupt. Then set these Bits to:
        //  00 ... for low level active Interrupts
        //  01 ... for "any edge" (both edges causing Interrupt-Events)
        //  10 ... for falling edges causing Interrupt-Events
        //  11 ... for rising edges causing Interrupt-Events
        EICRA &= ~(0x03 << extIntNumber*2);  //clear bits ISCn[1..0]
        EICRA |= (extIntEventType << extIntNumber*2); //then write Bits
        return;
    }
    
    //for the ATmega2560 the ISCn[1..0]-Bits for the external Interrupts 4 to 7
    //are in special-function-register EICRB
    #ifdef EICRB
    if (extIntNumber <8)
    {
        extIntNumber -= 4; 
        EICRB &= ~(0x03 << extIntNumber*2); //clear bits ISCn[1..0]
        EICRB |= (extIntEventType << extIntNumber*2); //then set these Bits
        return;
    }
    #endif
}


void attachExtIntCallback( uint8_t extIntNumber, callbackFunction* callback )
{
    if (extIntNumber >= EXT_INT_COUNT) return;
    callbacks[extIntNumber] = callback;
}


void detachExtIntCallback( uint8_t extIntNumber )
{
    if (extIntNumber >= EXT_INT_COUNT) return;
    callbacks[extIntNumber] = NULL;
}


void enableExtInt( uint8_t extIntNumber )
{
    if (extIntNumber >= EXT_INT_COUNT) return;
    EIMSK |= (0x01<<extIntNumber);
}


void disableExtInt( uint8_t extIntNumber )
{
    if (extIntNumber >= EXT_INT_COUNT) return;
    EIMSK &=~ (0x01<<extIntNumber);
}

void clearPendingExtIntEvent( uint8_t extIntNumber )
{
    if (extIntNumber >= EXT_INT_COUNT) return;   
    //To clear a pending interrupt, must write 1 to the interrupt-flag
    //This is called "write 1 to clear"
    EIFR |= (0x01<<extIntNumber);
}

//////////////////////////////////////////////////////////////////////////
// C++ object-oriented API
//////////////////////////////////////////////////////////////////////////

ExtInt::ExtInt(uint8_t extIntNumber, uint8_t extIntEventType,
                callbackFunction* callback, bool enabled)
{
    if (extIntNumber>= EXT_INT_COUNT)
    {
        //This is an invalid object
        _extIntNumber = 0xFF;
        return;
    }
    
    _extIntNumber = extIntNumber;
    
    extIntEventType &= 0x03; //only allow modes between 0x00 and 0x03
    setExtIntEventType( extIntEventType );
    
    if (callback) 
        attachExtIntCallback(callback);
    else
        detachExtIntCallback();
    
    //Not sure, if this is useful or not.
    clearPendingExtIntEvent();
    
    if (enabled) 
        enableExtInt();
    else
        disableExtInt();
}

//////////////////////////////////////////////////////////////////////////
// The Interrupt-Service-Routines
//////////////////////////////////////////////////////////////////////////

#ifdef INT0_vect
ISR(INT0_vect)
{
    //call callback-Function, if it has been attached (if pointer is not NULL)
    if( callbacks[0]) callbacks[0]();
}
#endif

#ifdef INT1_vect
ISR(INT1_vect)
{
    //call callback-Function, if it has been attached (if pointer is not NULL)
    if( callbacks[1]) callbacks[1]();
}
#endif

#ifdef INT2_vect
ISR(INT2_vect)
{
    //call callback-Function, if it has been attached (if pointer is not NULL)
    if( callbacks[2]) callbacks[2]();
}
#endif

#ifdef INT3_vect
ISR(INT3_vect)
{
    //call callback-Function, if it has been attached (if pointer is not NULL)
    if( callbacks[3]) callbacks[3]();
}
#endif

#ifdef INT4_vect
ISR(INT4_vect)
{
    //call callback-Function, if it has been attached (if pointer is not NULL)
    if( callbacks[4]) callbacks[4]();
}
#endif

#ifdef INT5_vect
ISR(INT5_vect)
{
    //call callback-Function, if it has been attached (if pointer is not NULL)
    if( callbacks[5]) callbacks[5]();
}
#endif

#ifdef INT6_vect
ISR(INT6_vect)
{
    //call callback-Function, if it has been attached (if pointer is not NULL)
    if( callbacks[6]) callbacks[6]();
}
#endif

#ifdef INT7_vect
ISR(INT7_vect)
{
    //call callback-Function, if it has been attached (if pointer is not NULL)
    if( callbacks[7]) callbacks[7]();
}
#endif



