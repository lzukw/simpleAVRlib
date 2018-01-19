/*
GPIO.c - A Library for managing the GPIO-Pins (General Purpose
Input/Output) of AVR-Microcontrollers. This is part of the
simpleAVRLib-Library.
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

#include <avr/io.h>
#include "GPIO.h"

////////////////////////////////////////////////////////////////
//Forward-declaration of "private" helper Functions for manipulating
//bits in the Special-Function-Registers DDRx, PORTx and PINx:
////////////////////////////////////////////////////////////////
void _setDDRBitValue( uint8_t port, uint8_t bitNumber, uint8_t bitValue);
void _setPORTBitValue( uint8_t port, uint8_t bitNumber, uint8_t bitValue);
void _togglePORTBit( uint8_t port, uint8_t bitNumber );
uint8_t _getPINBit(uint8_t port, uint8_t bitNumber);


////////////////////////////////////////////////////////////////
// C-API Functions for single Pins
////////////////////////////////////////////////////////////////
void setPinMode( uint8_t port, uint8_t pinNumber, uint8_t mode )
{
    switch( mode )
    {
        case MODE_OUTPUT:
            _setDDRBitValue(port,pinNumber,1);
             return;
        case MODE_INPUT:
            _setDDRBitValue(port,pinNumber,0);
            return;
        default:
            break;
    }
}

void setPinPullup( uint8_t port, uint8_t pinNumber, uint8_t onOff)
{
    switch( onOff ) 
    {
        case PULLUP_ON:
            _setPORTBitValue(port,pinNumber,1);
            return;
        case PULLUP_OFF:
            _setPORTBitValue(port,pinNumber,0);
            return;
        default:
            break;
    }
}


void writePin( uint8_t port, uint8_t pinNumber, uint8_t voltageLevel )
{
    switch( voltageLevel )
    {
        case HIGH_LEVEL:
            _setPORTBitValue(port,pinNumber,1);
            return;
        case LOW_LEVEL:
            _setPORTBitValue(port,pinNumber,0);
            return;
        default:
            break;
    }
}


uint8_t readPin( uint8_t port, uint8_t pinNumber )
{
    return _getPINBit(port,pinNumber);
}


void togglePin( uint8_t port, uint8_t pinNumber )
{
    _togglePORTBit(port, pinNumber);
}


//////////////////////////////////////////////////////////////////////////
// C-API-functions for manipulating all 8 pins of a port
//////////////////////////////////////////////////////////////////////////

void setPortMode ( uint8_t port, uint8_t mode, uint8_t mask )
{

    //Ugly code, but macros must be avoided (beginners can't find the correct
    //location of syntax-errors, when macros are used.
    switch ( port )
    {
        case port_A:
            #ifdef DDRA
            DDRA |= mask & mode;
            DDRA &= ~(mask & ~mode);
            #endif
            return;

        case port_B:
            #ifdef DDRB
            DDRB |= mask & mode;
            DDRB &= ~(mask & ~mode);
            #endif
            return;

        case port_C:
            #ifdef DDRC
            DDRC |= mask & mode;
            DDRC &= ~(mask & ~mode);
            #endif
            return;

        case port_D:
            #ifdef DDRD
            DDRD |= mask & mode;
            DDRD &= ~(mask & ~mode);
            #endif
            return;

        case port_E:
            #ifdef DDRE
            DDRE |= mask & mode;
            DDRE &= ~(mask & ~mode);
            #endif
            return;

        case port_F:
            #ifdef DDRF
            DDRF |= mask & mode;
            DDRF &= ~(mask & ~mode);
            #endif
            return;

        case port_G:
            #ifdef DDRG
            DDRG |= mask & mode;
            DDRG &= ~(mask & ~mode);
            #endif
            return;

        case port_H:
            #ifdef DDRH
            DDRH |= mask & mode;
            DDRH &= ~(mask & ~mode);
            #endif
            return;

        case port_I: //I think, that port I does not exist on any AVR
            #ifdef DDRI
            DDRI |= mask & mode;
            DDRI &= ~(mask & ~mode);
            #endif
            return;

        case port_J:
            #ifdef DDRJ
            DDRJ |= mask & mode;
            DDRJ &= ~(mask & ~mode);
            #endif
            return;

        case port_K:
            #ifdef DDRK
            DDRK |= mask & mode;
            DDRK &= ~(mask & ~mode);
            #endif
            return;

        case port_L:
            #ifdef DDRL
            DDRL |= mask & mode;
            DDRL &= ~(mask & ~mode);
            #endif
            return;

        default:
            break;
    }
}


void setPortPullup( uint8_t port, uint8_t pullup, uint8_t mask )
{
    switch ( port )
    {
        case port_A:
            #ifdef PORTA
            PORTA |= mask & pullup;
            PORTA &= ~(mask & ~pullup);
            #endif
            return;

        case port_B:
            #ifdef PORTB
            PORTB |= mask & pullup;
            PORTB &= ~(mask & ~pullup);
            #endif
            return;

        case port_C:
            #ifdef PORTC
            PORTC |= mask & pullup;
            PORTC &= ~(mask & ~pullup);
            #endif
            return;

        case port_D:
            #ifdef PORTD
            PORTD |= mask & pullup;
            PORTD &= ~(mask & ~pullup);
            #endif
            return;

        case port_E:
            #ifdef PORTE
            PORTE |= mask & pullup;
            PORTE &= ~(mask & ~pullup);
            #endif
            return;

        case port_F:
            #ifdef PORTF
            PORTF |= mask & pullup;
            PORTF &= ~(mask & ~pullup);
            #endif
            return;

        case port_G:
            #ifdef PORTG
            PORTG |= mask & pullup;
            PORTG &= ~(mask & ~pullup);
            #endif
            return;

        case port_H:
            #ifdef PORTH
            PORTH |= mask & pullup;
            PORTH &= ~(mask & ~pullup);
            #endif
            return;

        case port_I: //I think, that port I does not exist on any AVR
             #ifdef PORTI
            PORTI|= mask & pullup;
            PORTI &= ~(mask & ~pullup);
            #endif
            return;
 
        case port_J:
            #ifdef PORTJ
            PORTJ |= mask & pullup;
            PORTJ &= ~(mask & ~pullup);
            #endif
            return;

        case port_K:
            #ifdef PORTK
            PORTK |= mask & pullup;
            PORTK &= ~(mask & ~pullup);
            #endif
            return;

        case port_L:
            #ifdef PORTL
            PORTL |= mask & pullup;
            PORTL &= ~(mask & ~pullup);
            #endif
            return;

        default:
            break;
    }
}



void writePort( uint8_t port, uint8_t voltageLevels, uint8_t mask )
{
    switch ( port )
    {
        case port_A:
            #ifdef PORTA
            PORTA |= mask & voltageLevels;
            PORTA &= ~(mask & ~voltageLevels);
            #endif
            return;

        case port_B:
            #ifdef PORTB
            PORTB |= mask & voltageLevels;
            PORTB &= ~(mask & ~voltageLevels);
            #endif
            return;

        case port_C:
            #ifdef PORTC
            PORTC |= mask & voltageLevels;
            PORTC &= ~(mask & ~voltageLevels);
            #endif
            return;

        case port_D:
            #ifdef PORTD
            PORTD |= mask & voltageLevels;
            PORTD &= ~(mask & ~voltageLevels);
            #endif
            return;

        case port_E:
            #ifdef PORTE
            PORTE |= mask & voltageLevels;
            PORTE &= ~(mask & ~voltageLevels);
            #endif
            return;

        case port_F:
            #ifdef PORTF
            PORTF |= mask & voltageLevels;
            PORTF &= ~(mask & ~voltageLevels);
            #endif
            return;

        case port_G:
            #ifdef PORTG
            PORTG |= mask & voltageLevels;
            PORTG &= ~(mask & ~voltageLevels);
            #endif
            return;

        case port_H:
            #ifdef PORTH
            PORTH |= mask & voltageLevels;
            PORTH &= ~(mask & ~voltageLevels);
            #endif
            return;

        case port_I: //I think, that port I does not exist on any AVR
            #ifdef PORTI
            PORTI |= mask & voltageLevels;
            PORTI &= ~(mask & ~voltageLevels);
            #endif
            return;

        case port_J:
            #ifdef PORTJ
            PORTJ |= mask & voltageLevels;
            PORTJ &= ~(mask & ~voltageLevels);
            #endif
            return;

        case port_K:
            #ifdef PORTK
            PORTK |= mask & voltageLevels;
            PORTK &= ~(mask & ~voltageLevels);
            #endif
            return;

        case port_L:
            #ifdef PORTL
            PORTL |= mask & voltageLevels;
            PORTL &= ~(mask & ~voltageLevels);
            #endif
            return;

        default:
            break;
    }

}


void togglePort( uint8_t port, uint8_t mask )
{
    switch ( port )
    {
        case port_A:
            #ifdef PORTA
            PORTA ^= mask;
            #endif
            return;

        case port_B:
            #ifdef PORTB
            PORTB ^= mask;
            #endif
            return;

        case port_C:
            #ifdef PORTC
            PORTC ^= mask;
            #endif
            return;

        case port_D:
            #ifdef PORTD
            PORTD ^= mask;
            #endif
            return;

        case port_E:
            #ifdef PORTE
            PORTE ^= mask;
            #endif
            return;

        case port_F:
            #ifdef PORTF
            PORTF ^= mask;
            #endif
            return;

        case port_G:
            #ifdef PORTG
            PORTG ^= mask;
            #endif
            return;

        case port_H:
            #ifdef PORTH
            PORTH ^= mask;
            #endif
            return;

        case port_I: //I think, that port I does not exist on any AVR
            #ifdef PORTI
            PORTI ^= mask;
            #endif
            return;

        case port_J:
            #ifdef PORTJ
            PORTJ ^= mask;
            #endif
            return;

        case port_K:
            #ifdef PORTK
            PORTK ^= mask;
            #endif
            return;

        case port_L:
            #ifdef PORTL
            PORTL ^= mask;
            #endif
            return;

        default:
            break;
    }
}


uint8_t readPort( uint8_t port, uint8_t mask)
{
    switch ( port )
    {
        case port_A:
            #ifdef PINA
            return PINA & mask;
            #endif
            break;

        case port_B:
            #ifdef PINB
            return PINB & mask;
            #endif
            break;

        case port_C:
            #ifdef PINC
            return PINC & mask;
            #endif
            break;

        case port_D:
            #ifdef PIND
            return PIND & mask;
            #endif
            break;

        case port_E:
            #ifdef PINE
            return PINE & mask;
            #endif
            break;

        case port_F:
            #ifdef PINF
            return PINF & mask;
            #endif
            break;

        case port_G:
            #ifdef PING
            return PING & mask;
            #endif
            break;

        case port_H:
            #ifdef PINH
            return PINH & mask;
            #endif
            break;

        case port_I: //I think, that port I does not exist on any AVR
            #ifdef PINI
            return PINI & mask;
            #endif
            break;

        case port_J:
            #ifdef PINJ
            return PINJ & mask;
            #endif
            break;

        case port_K:
            #ifdef PINK
            return PINK & mask;
            #endif
            break;

        case port_L:
            #ifdef PINL
            return PINL & mask;
            #endif
            break;

        default:
            break;
    }
    return 0;
}


////////////////////////////////////////////////////////////////
// "private" helper-Functions
////////////////////////////////////////////////////////////////

//Sets or clears a Bit in a DDRx-Register
//Writing a 1 for example to Bit 6 of Register DDRB, makes pin PB7 to an 
//output. Writing a 0 to this Bit makes PB7 to an input
void _setDDRBitValue( uint8_t port, uint8_t bitNumber, uint8_t bitValue)
{
    switch (port)
    {
        case port_A:
            #ifdef DDRA
            if (bitValue)  DDRA |=  (0x01<< bitNumber);
            else           DDRA &= ~(0x01<< bitNumber);
            #endif
            return;

        case port_B:
            #ifdef DDRB
            if (bitValue)  DDRB |=  (0x01<< bitNumber);
            else           DDRB &= ~(0x01<< bitNumber);
            #endif
            return;

        case port_C:
            #ifdef DDRA
            if (bitValue)  DDRC |=  (0x01<< bitNumber);
            else           DDRC &= ~(0x01<< bitNumber);
            #endif
            return;

        case port_D:
            #ifdef DDRD
            if (bitValue)  DDRD |=  (0x01<< bitNumber);
            else           DDRD &= ~(0x01<< bitNumber);
            #endif
            return;

        case port_E:
            #ifdef DDRE
            if (bitValue)  DDRE |=  (0x01<< bitNumber);
            else           DDRE &= ~(0x01<< bitNumber);
            #endif
            return;

        case port_F:
            #ifdef DDRF
            if (bitValue)  DDRF |=  (0x01<< bitNumber);
            else           DDRF &= ~(0x01<< bitNumber);
            #endif
            return;

        case port_G:
            #ifdef DDRG
            if (bitValue)  DDRG |=  (0x01<< bitNumber);
            else           DDRG &= ~(0x01<< bitNumber);
            #endif
            return;

        case port_H:
            #ifdef DDRH
            if (bitValue)  DDRH |=  (0x01<< bitNumber);
            else           DDRH &= ~(0x01<< bitNumber);
            #endif
            return;

        case port_I: //I think, Port I does not exist on any AVR
            #ifdef DDRI
            if (bitValue)  DDRI |=  (0x01<< bitNumber);
            else           DDRI &= ~(0x01<< bitNumber);
            #endif
            return;

        case port_J:
            #ifdef DDRJ
            if (bitValue)  DDRJ |=  (0x01<< bitNumber);
            else           DDRJ &= ~(0x01<< bitNumber);
            #endif
            return;

        case port_K:
            #ifdef DDRK
            if (bitValue)  DDRK |=  (0x01<< bitNumber);
            else           DDRK &= ~(0x01<< bitNumber);
            #endif
            return;

        case port_L:
            #ifdef DDRL
            if (bitValue)  DDRL |=  (0x01<< bitNumber);
            else           DDRL &= ~(0x01<< bitNumber);
            #endif
            return;

        default:
            break;
    }
}

//Sets or clears a Bit in a PORTx-Register
//The Bits in the PORTx-Registers have a double meaning.
//For example Bit 3 in Register PORTC:
// - If Pin PC3 is an output, a 0 in Bit 3 of PORTC puts out a 
//   low-voltage-level on Pin PC3. While a 1 in this Bit puts out a High-Level
// - But if Pin PC3 is an input, Bit 3 in Register PORTC controls the
//   activation of the internal pullup-resistor: A 0 in this Bit deactivates
//   the internal pullup-resistor, while a 1 activates it.
void _setPORTBitValue( uint8_t port, uint8_t bitNumber, uint8_t bitValue)
{
    switch (port)
    {
        case port_A:
            #ifdef PORTA
            if (bitValue)  PORTA |=  (0x01<< bitNumber);
            else           PORTA &= ~(0x01<< bitNumber);
            #endif
            return;

        case port_B:
            #ifdef PORTB
            if (bitValue)  PORTB |=  (0x01<< bitNumber);
            else           PORTB &= ~(0x01<< bitNumber);
            #endif
            return;

        case port_C:
            #ifdef PORTA
            if (bitValue)  PORTC |=  (0x01<< bitNumber);
            else           PORTC &= ~(0x01<< bitNumber);
            #endif
            return;

        case port_D:
            #ifdef PORTD
            if (bitValue)  PORTD |=  (0x01<< bitNumber);
            else           PORTD &= ~(0x01<< bitNumber);
            #endif
            return;

        case port_E:
            #ifdef PORTE
            if (bitValue)  PORTE |=  (0x01<< bitNumber);
            else           PORTE &= ~(0x01<< bitNumber);
            #endif
            return;

        case port_F:
            #ifdef PORTF
            if (bitValue)  PORTF |=  (0x01<< bitNumber);
            else           PORTF &= ~(0x01<< bitNumber);
            #endif
            return;

        case port_G:
            #ifdef PORTG
            if (bitValue)  PORTG |=  (0x01<< bitNumber);
            else           PORTG &= ~(0x01<< bitNumber);
            #endif
            return;

        case port_H:
            #ifdef PORTH
            if (bitValue)  PORTH |=  (0x01<< bitNumber);
            else           PORTH &= ~(0x01<< bitNumber);
            #endif
            return;

        case port_I: //I think, Port I does not exist on any AVR
            #ifdef PORTI
            if (bitValue)  PORTI |=  (0x01<< bitNumber);
            else           PORTI &= ~(0x01<< bitNumber);
            #endif
            return;

        case port_J:
            #ifdef PORTJ
            if (bitValue)  PORTJ |=  (0x01<< bitNumber);
            else           PORTJ &= ~(0x01<< bitNumber);
            #endif
            return;

        case port_K:
            #ifdef PORTK
            if (bitValue)  PORTK |=  (0x01<< bitNumber);
            else           PORTK &= ~(0x01<< bitNumber);
            #endif
            return;

        case port_L:
            #ifdef PORTL
            if (bitValue)  PORTL |=  (0x01<< bitNumber);
            else           PORTL &= ~(0x01<< bitNumber);
            #endif
            return;

        default:
            break;
    }
}

//Toggles Bit <bitNumber> of the PORTx-Register specified by <port>
void _togglePORTBit( uint8_t port, uint8_t bitNumber )
{
    switch ( port )
    {
        case port_A:
            #ifdef PORTA
            PORTA ^= (0x01<<bitNumber);
            #endif
            return;

        case port_B:
            #ifdef PORTB
            PORTB ^= (0x01<<bitNumber);
            #endif
            return;

        case port_C:
            #ifdef PORTC
            PORTC ^= (0x01<<bitNumber);
            #endif
            return;

        case port_D:
            #ifdef PORTD
            PORTD ^= (0x01<<bitNumber);
            #endif
            return;

        case port_E:
            #ifdef PORTE
            PORTE ^= (0x01<<bitNumber);
            #endif
            return;

        case port_F:
            #ifdef PORTF
            PORTF ^= (0x01<<bitNumber);
            #endif
            return;

        case port_G:
            #ifdef PORTG
            PORTG ^= (0x01<<bitNumber);
            #endif
            return;

        case port_H:
            #ifdef PORTH
            PORTH ^= (0x01<<bitNumber);
            #endif
            return;

        case port_I: //Port I doesn't exist on any AVR
            #ifdef PORTI
            PORTI ^= (0x01<<bitNumber);
            #endif
            return;

        case port_J:
            #ifdef PORTJ
            PORTJ ^= (0x01<<bitNumber);
            #endif
            return;

        case port_K:
            #ifdef PORTK
            PORTK ^= (0x01<<bitNumber);
            #endif
            return;

        default:
            break;
    }
}

//returns the Bit-value (0 or 1) of a Bit of the PINx-Register
//This Bit represents the actual voltage-level of the corresponding GPIO-Pin
uint8_t _getPINBit(uint8_t port, uint8_t bitNumber)
{
    switch(port)
    {
        case port_A:
            #ifdef PINA
            if (PINA & (0x01<<bitNumber)) return 1;
            else                          return 0;
            #endif
            break;

        case port_B:
            #ifdef PINB
            if (PINB & (0x01<<bitNumber)) return 1;
            else                          return 0;
            #endif
            break;

        case port_C:
            #ifdef PINC
            if (PINC & (0x01<<bitNumber)) return 1;
            else                          return 0;
            #endif
            break;

        case port_D:
            #ifdef PIND
                if (PIND & (0x01<<bitNumber)) return 1;
                else                          return 0;
            #endif
            break;

        case port_E:
            #ifdef PINE
            if (PINE & (0x01<<bitNumber)) return 1;
            else                          return 0;
            #endif 
            break;

        case port_F:
            #ifdef PINF
            if (PINF & (0x01<<bitNumber)) return 1;
            else                          return 0;
            #endif
            break;

        case port_G:
            #ifdef PING
            if (PING & (0x01<<bitNumber)) return 1;
            else                          return 0;
            #endif
            break;

        case port_H:
            #ifdef PINH
            if (PINH & (0x01<<bitNumber)) return 1;
            else                          return 0;
            #endif
            break;

        case port_I: //I think, Port I does not exist on any AVR
            #ifdef PINI
            if (PINI & (0x01<<bitNumber)) return 1;
            else                          return 0;
            #endif
            break;

        case port_J:
            #ifdef PINJ
            if (PINJ & (0x01<<bitNumber)) return 1;
            else                          return 0;
            #endif
            break;

        case port_K:
            #ifdef PINK
            if (PINK & (0x01<<bitNumber)) return 1;
            else                          return 0;
            #endif
            break;
        
        case port_L:
            #ifdef PINL
            if (PINL & (0x01<<bitNumber)) return 1;
            else                          return 0;
            #endif
            break;
        
        default:
            break;
    }

    //only reached for wrong argument or non existing port
    return 0;
}
