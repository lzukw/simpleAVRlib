/*
    testGPIOPin.cpp - Test-Module for GPIO.h and GPIO.c using the C++-Compiler
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
Connect a button between Pin PD2 and GND, and two LEDs (with 220Ohm-Series-
resistors) between VCC and Pins PB0, PB1. 
Each Time the button is pressed, the two LEDs toggle. More exactly the LEDs
toggle on releasing the button. 
*/

#include <stdint.h>
#include <util/delay.h>

#include "GPIO.h"

int main(void)
{
    //configure Button: Pin PD2 is an input with activated pullup-resistor
    //The button is connected between PD2 and GND
    GPIOPin pd2 = GPIOPin(port_D,2, MODE_INPUT);
    pd2.setPinPullup(PULLUP_ON);

    //configure Pin PB0 (connected to LED0) as output. Turn on this LED by 
    //putting out a Low-Voltage-Level (The LED is connected in series with a
    //220 Ohm-resistor between VCC and PB0).
    GPIOPin pb0 = GPIOPin(port_B,0, MODE_OUTPUT);
    pb0.writePin(LOW_LEVEL);
    
    //configure Pin PB1 (connected to LED1) as output. Turn off this LED by
    //putting out a High-Voltage-Level
    GPIOPin pb1 = GPIOPin(port_B,1);
    pb1.setPinMode(MODE_OUTPUT);
    pb1.writePin(HIGH_LEVEL);
    
    uint8_t oldbuttonState = LOW_LEVEL;
    
    while (1) 
    {
        //check for rising edges on input-pin pd2 (these occur on releasing
        //the button):
        uint8_t buttonState = pd2.readPin();
        if (oldbuttonState == LOW_LEVEL && buttonState == HIGH_LEVEL) 
        {
            pb0.togglePin();
            pb1.togglePin();
        }
        
        oldbuttonState = buttonState;        
        _delay_ms(100);
    }
}


