/*
    testGPIOPort.cpp - Test-Module for GPIO.h and GPIO.cpp
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
Connect a button between Pins PD3, PD2 and GND, and eight LEDs (with 
220Ohm-Series-resistors) on all Pins of port B. The two buttons
control the pattern, that is displayed on the LEDs.
*/

#include <stdint.h>
#include <util/delay.h>

#include "GPIO.h"

int main(void)
{
    
    GPIOPort ledPort = GPIOPort(port_B);
    //make all Pins PB7...PB0 to outputs (mask has its default-value of 0xFF)
    ledPort.setPortMode(0xFF);
    //set all Pins to high --> turn off LEDs. (mask has its
    //default-value of 0xFF)
    ledPort.writePort(0xFF);
        

    GPIOPort buttonPort = GPIOPort(port_D);
    //In the mask-argument 0x0C = 0b00001100 the bits number 2 and 3 are set,
    //so only Pins PD2 and PD3 are affected. In the mode-Argument these bits
    //are zero, so both GPIO-Pins are programmed as inputs
    buttonPort.setPortMode(0x00, 0x0C); 
    //activate pullup-Resistors on PD2 and PD3. Bits 2 and 3 in the mode- and
    //int the mask-Argument are 1, so only Pins PD2 amd PD3 are affected.
    //The 1-Bits in the mode-Argument turn on the internal pullup-Resistors.
    buttonPort.setPortPullup( 0x0C, 0x0C);
    
    
    while (1) 
    {
        //Are both buttons on pins PD3 and PD2 pressed? 
        // maks 0x0C = 0b00001100 --> read in voltage-levels of both pins
        // //low-levels means, that buttons are pressed
        if ( buttonPort.readPort(0x0C) == 0x00 )
        {
            //toggle all LEDs: No Argument for mask passed, so it gets the 
            //default-value of 0xFF --> voltage-levels of all 8 Pins of port B 
            //are toggled
            ledPort.togglePort();
        }
        //Is the button on Pin PD3 pressed?
        // mask 0x08 = 0b00001000 --> Just read in voltage-level of PD3
        else if ( buttonPort.readPort(0x08) == 0x00) 
        {
            //put out high-level on Pins PB7 and low-level on PB6
            //(mode = 0x80 = 0b10000000). LED on PB7 is off, LED on PB6 is on
            //leave the other pins unchanged (mask = 0xC0 = 0b11000000)
            ledPort.writePort(0x80, 0xC0);
        }

        //Is the button on Pin PD2 pressed?
        // mask 0x04 = 0b00000100 --> Just read in voltage-level of PD2
        else if (buttonPort.readPort(0x04) == 0x00)
        {
            //No argument for mask is passed, so default-value (0xFF) applies.
            //mode = 0xF8 = 0b11111000
            //Put out High-level on Pins PB7...PB3 and low-levels on PB2...PB0
            //--> LEDs on PB2...PB0 are on, others off.
            ledPort.writePort(0xF8);
        }            
        else //no button is pressed
        {
            ledPort.writePort(0x55);
        }
        
        _delay_ms(100);
    }
}

