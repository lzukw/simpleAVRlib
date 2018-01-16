/*
    ExternalInterrupts.h - A Library for Interrupts caused by 
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


#ifndef EXTERNALINTERRUPTS_H_
#define EXTERNALINTERRUPTS_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <avr/interrupt.h>
#include "InterruptUtils.h"


#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////////////////////////
// Macros used as arguments for function-/method-calls
//////////////////////////////////////////////////////////////////////////

/**
 * These Macros are used as argument for the parameter extIntEventType
 * @see setExtIntEventType()
 */
#define EXTINT_LOW_LEVEL_ACTIVE         0x00
#define EXTINT_ANY_EDGE                 0x01
#define EXTINT_FALLING_EDGE             0x02
#define EXTINT_RISING_EDGE              0x03  

// Number of external Interrupts
#if defined(INT7_vect)
    #define EXT_INT_COUNT  8
#elif defined(INT6_vect)
    #define EXT_INT_COUNT  7
#elif defined(INT5_vect)
    #define EXT_INT_COUNT  6
#elif defined(INT4_vect)
    #define EXT_INT_COUNT  5
#elif defined(INT3_vect)
    #define EXT_INT_COUNT  4
#elif defined(INT2_vect)
    #define EXT_INT_COUNT  3
#elif defined(INT1_vect)
    #define EXT_INT_COUNT  2
#elif defined(INT0_vect)
    #define EXT_INT_COUNT  1
#else
    #error "There are no external Interrupts. Don't use this module"
#endif

//////////////////////////////////////////////////////////////////////////
// C-Function-API
//////////////////////////////////////////////////////////////////////////

/**
 * This function defines, which voltage-change-Events on an INTx-Pin actually
 * cause an Interrupt-Event. 
 * @param extIntNumber The Number of the external Interrupt
 * @param extIntEventType Use one of the four Macros for this parameter
 *      <ul>
 *      <li>EXTINT_LOW_LEVEL_ACTIVE ...A low-level on Pin INTx produces ongoing
            interrupt-events (mostly used with external chips, that have more 
            than one internal Interrupt-Source, in order to only use one
            Interrupt-Pin</li>
        <li>EXTINT_ANY_EDGE ...if both, rising and falling edges 
            (voltage-changes from high- to low-level and vice versa) shall 
            cause an Interrupt-Event</li>
        <li>EXTINT_FALLING_EDGE ...if only the falling edges (voltage-changes 
            from high- to low-level) shall cause an Interrupt-Event</li>
        <li>EXTINT_RISING_EDGE ...if only rising edges (voltage-changes from
            low- to high-level) shall cause an Interrupt-Event</li>
        </ul>
 */
void setExtIntEventType( uint8_t extIntNumber, uint8_t extIntEventType );


//used as Parameter for functionPointers to Interrupt-Service-Handler-Routines
typedef void (callbackFunction) (void);

/**
 * With attachExtIntCallback() you specify, which function is called when the 
 * Interrupt happens.
 * @param extIntNumber The Number of the external Interrupt (0 or 1 with the
 *      ATmega328p, 0..7 with the ATmega2560).
 * @param callbackFunction A pointer to your callback-Function (just write the
 *      name of your callback-Function). The callback-function has no return-
 *      type (void) and no parameters.
 * For Example: Writing an Interrupt-Handler for External Interrupt INT3
 * {@code
        #include "InterruptUtils.h"
        #include "ExternalInterrupts.h"
     
        void myInterruptHandler()
        {
            //...do here whatever is necessary when an Interrupt-Event occurs
        }
        
        int main() 
        {
            //...
            //...INT3-Pin must first be programmed as input
            //...
            attachExtIntCallback ( 3, myInterruptHandler );
            enableExtInt ( 3 );
            allowEnabledInterrupts(); //from InterruptUtils.h
            
            while(1)
            {
                //...
            }                
        }                        
   }
 */
void attachExtIntCallback( uint8_t extIntNumber, callbackFunction* callback );

/**
 * Detaches an existing callback-Function from the external Interrupt. After 
 * calling this function the Interrupt still occurs and calls the internal
 * Interrupt-Service-Routine, but this Interrupt-Service-Routine does not 
 * call a callback-function.
 * @param extIntNumber The Number of the external Interrupt
 */
void detachExtIntCallback( uint8_t extIntNumber );

/**
 * Enables an external Interrupt. If Interrupts are globally allowed 
 * (@see allowEnabledInterrupts() from InterruptUtils.h) then the internal
 * Interrupt-Service-Routine is executed, each time an external 
 * Interrupt-event happens. You also have to attach your callback-function
 * to the internal Interrupt-Service-Routine with attachExtIntCallback()
 * @param extIntNumber The Number of the external Interrupt
 * @see attachExtIntCallback() for more explanation
 */
void enableExtInt( uint8_t extIntNumber );


/**
 * Disables an external Interrupt. The internal Interrupt-Service-Routine is
 * not executed any longer, if an Interrupt-Event happens (and therefore no
 * callback-Function is called).
 * @param extIntNumber The Number of the external Interrupt
 * @see enableExtInt()
 * @see attachExtIntCallback() for more explanation
 */
void disableExtInt( uint8_t extIntNumber );


/**
 * If an Interrupt-Event happens, while the corresponding external Interrupt
 * is disabled, an internal Interrupt-Flag is set. This flag stores the 
 * information for the CPU, that an Interrupt-Event has happened. If later
 * the external Interrupt is enabled, the Interrupt-Service-Routine and the
 * attached callback-function is executed immediately.
 * If you want to prevent this, call clearPendingInterruptEvent() before
 * enabling the external Interrupt.
 * @param extIntNumber The Number of the external Interrupt
 */
void clearPendingExtIntEvent( uint8_t extIntNumber );

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus

//////////////////////////////////////////////////////////////////////////
// C++ object-oriented API
//////////////////////////////////////////////////////////////////////////

class ExtInt
{
public:
    /**
     * Constructor. Use one ExtInt-Instance for each external interrupt used
     * in your program. 
     * @param extIntNumber The Number of the external Interrupt
     * @param extIntEventType Use one of the Macros EXTINT_LOW_LEVEL_ACTIVE,
     *      EXTINT_ANY_EDGE, EXTINT_FALLING_EDGE or EXTINT_RISING_EDGE.
     *      @see setExtIntEventType()
     * @param callback Pointer to the callback-Function. This is function with
     *      no argumtents and no return type. Just fill in the name of this 
     *      function for this parameter. If NULL is passed, no callback occurs.
     *      Default-Value: NULL.
     * @param enabled Fill in true or false to enable/disable the external
     *      interrupt. Default-Value: true.
     */
     ExtInt(uint8_t extIntNumber, uint8_t extIntEventType,
                    callbackFunction* callback = NULL, bool enabled = true);
    
    /**
     * This method defines, which voltage-change-Events on an INTx-Pin actually
     * cause an Interrupt-Event.
     * @param extIntEventType Use one of the Macros EXTINT_LOW_LEVEL_ACTIVE,
     *      EXTINT_ANY_EDGE, EXTINT_FALLING_EDGE or EXTINT_RISING_EDGE.
     *      @see setExtIntEventType()
     */
    void setExtIntEventType( uint8_t extIntEventType ) 
    { ::setExtIntEventType( _extIntNumber, extIntEventType ); }

    /**
     * With attachCallback() you specify, which function is called when an 
     * Interrupt-Event occurs.
     * @param callbackFunction A pointer to your callback-function (just write 
     *      the name of your callback-function). The callback-function has no 
     *      return-type (void) and no parameters.
     * @see attachExtIntCallback()
     */
    void attachExtIntCallback( callbackFunction* callback )
    { ::attachExtIntCallback( _extIntNumber, callback ); }
        
    /**
     * Detaches an existing callback-Function from the external Interrupt. After 
     * calling this method the Interrupt still occurs and calls the internal
     * Interrupt-Service-Routine, but this Interrupt-Service-Routine does not 
     * call a callback-function.
     */
    void detachExtIntCallback()
    { ::detachExtIntCallback( _extIntNumber ); }

    /**
     * Enables an external Interrupt. If Interrupts are globally allowed 
     * (@see allowEnabledInterrupts() from InterruptUtils.h) then the internal
     * Interrupt-Service-Routine is executed, each time an external 
     * Interrupt-event happens. You also have to attach your callback-function
     * to the internal Interrupt-Service-Routine with attachCallback()
     * @see function attachExtIntCallback() for more explanation
     */
    void enableExtInt()
    { ::enableExtInt( _extIntNumber ); }

    /**
     * Disables an external Interrupt. The internal Interrupt-Service-Routine is
     * not executed any longer, if an Interrupt-Event happens (and therefore no
     * callback-Function is called).
     * @see enable()
     * @see attachExtIntCallback() for more explanation
     */
    void disableExtInt()
    { ::disableExtInt(_extIntNumber); }

    /**
     * Clears pending Interrupts (that occur, while Interrupts are
     * disabled).
     * @see clearPendingInterruptEvent() for explanation
     */
    void clearPendingExtIntEvent()
    {
        ::clearPendingExtIntEvent(_extIntNumber);
    }

     
private:
    uint8_t _extIntNumber;
};

#endif


#endif /* EXTERNALINTERRUPTS_H_ */