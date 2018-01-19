/*
    testExtInts.cpp - Test-Module for ExternalInterrupts.h/.cpp and for
    InterruptUtils.h
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
The ATmega2560 has its INT2 Pin located at Pin PD2. This will be used as 
external Interrupts. Pin PD3 will be used as ordinary input. Both pins 
are connected to a button (buttons connected between their pin and GND).

All port B - pins are connected to LEDs (low-level turns on the LEDs).
These LEDs display the value of a global variable `counter` (as a
bitpattern). counter is increased every time an INT2-event happens
(every times the button on PD2 is pushed). 

But the interrupt is only enabled, while the button at pin PD3 is not
pressed.
Since buttons are bouncing, pushing the button at pin PD2 may
increase `counter` more than once.
*/

#include <avr/interrupt.h>

#include <stdint.h>
#include <util/delay.h>

#include "GPIO.h"
#include "ExternalInterrupts.h"


//The global variable. If a variable is changed within an 
//Interrupt-Service-Routine, it must be declared as volatile
volatile uint8_t counter = 2; 


//This is the Interrupt-Service-Routine for INT2-Events. The correct
//Interrupt-vector must be passed to the ISR-macro
ISR(INT2_vect)
{
    counter++;
}


int main()
{
    
    //make Pins PD3 and PD2 inputs with activated internal pullup-resistors
	//Pins uses as external Interrupts, still must be programmed to be
	//inputs first!
    GPIOPin pd2 = GPIOPin(port_D, 2, MODE_INPUT);
    pd2.setPinPullup(PULLUP_ON);
    GPIOPin pd3 = GPIOPin(port_D, 3, MODE_INPUT);
    pd3.setPinPullup(PULLUP_ON);
    
    //All 8 pins of Port B are connected to LEDs (low-level turns an LED on)
    GPIOPort ledPort = GPIOPort(port_B);
    ledPort.setPortMode(0xFF); //PB7...PB0 are outputs
    ledPort.writePort(0xFF); //put out a high-level on all pins (LEDs off)

    //Falling edges occur on pushing the button (rising edges occur on 
    //releasing it).
    ExtInt int2 = ExtInt( 2, EXTINT_FALLING_EDGE);
    
    //globally enable interrupts
    sei();
    
    uint8_t lastButtonState = HIGH_LEVEL;
    
    while(1)
    {
        //look for changes of the state of the button on PD3:
        uint8_t actualButtonState = pd3.readPin();
        if ( actualButtonState != lastButtonState )
        {
            //Button on pd3 has been pressed or released
            if (actualButtonState == LOW_LEVEL)
            {
                //button has been pressed -> disable INT2-Interrupt
                int2.disableExtInt(); 
            }                
            else
            {
                //button has been released -> enable INT2-Interrupt
                //
                //But first clear a pending interrupt: If button on PD2 has
                //been pushed, while Interrupts were disabled, then the
                //interrupt-event is stored in the CPU in an internal
                //interrupt-Flag. Not clearing the pending interrupt and
                //just enabling interrupts would immediately execute the
                //Interrupt-Service-Routine and therefore increase `counter`.
                //
                //Try the difference by commenting out  the
                //clearPendingExtIntEvent()-method-call
                int2.clearPendingExtIntEvent();
                int2.enableExtInt(); 
            }                
        }
        lastButtonState = actualButtonState;
        
        //display the value of the global variable counter on the LEDs as a
        //bit-pattern
        ledPort.writePort( ~counter );
         
        _delay_ms(100);
    }        
}
