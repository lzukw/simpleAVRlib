/*
    GPIO.h - A Library for managing the GPIO-Pins (General Purpose
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


#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////
// Macros used as Arguments for the API-Functions
////////////////////////////////////////////////////////////////////////////

/** 
 * GPIO-Pins are grouped in in "ports". 8 pins together form a port.
 * These Macros should be used as parameters for Functions/Methods,
 * that receive a port as parameter.
 * In the datasheet, GPIO-Pins have names like PB3. In this case
 * this is the third pin of port B. The numbers for the 8 pins of
 * each port go from 0 to 7. So port B consists of the pins PB0 to PB7.
 */
#define        port_A         0
#define        port_B         1
#define        port_C         2
#define        port_D         3
#define        port_E         4
#define        port_F         5
#define        port_G         6
#define        port_H         7
#define        port_I         8 /* does not exist on any AVR */
#define        port_J         9
#define        port_K        10
#define        port_L        11

/**
 * There are three possible modes for a pin: 
 * - output,
 * - input without activated internal pullup-resitor, and
 * - input with activated internal pullup-resistor.
 */
#define MODE_INPUT      0
#define MODE_OUTPUT     1

/**
 * Pins that are inputs, can have an internal pullup-resistor activated, to
 * prevent an open input to have a floating voltage at its input.
 */
#define PULLUP_OFF      0
#define PULLUP_ON       1

/**
 * The voltage-levels for outputs and inputs. Low-Level is 0 volts, High-Level
 * is 5 volts (sometimes  3.3 volts ?)
 */
#define HIGH_LEVEL  1
#define LOW_LEVEL   0

////////////////////////////////////////////////////////////////////////////
// C-API-Functions for manipulating a single Pin
////////////////////////////////////////////////////////////////////////////

/**
 * Programs a single GPIO-Pin to be an output or an input. 
 * Example: Set Pin PL3 to be an input:
 * {@code 
        setPinMode( port_L, 3, MODE_INPUT ); 
   }
 *
 * @param port One of the Macros port_A to port_L should be used for this 
 *      parameter.
 * @param pinNumber The number of the Pin. Must be between 0 and 7. 
 * @param mode One of MODE_OUTPUT or MODE_INPUT
 */
void setPinMode( uint8_t port, uint8_t pinNumber, uint8_t mode );

/**
 * Activates or deactivates the internal-pullup-resistor of a pin, that has
 * formerly been programmed to be an input.
 *
 * @param port One of the Macros port_A to port_L should be used for this
 *      parameter.
 * @param pinNumber The number of the Pin. Must be between 0 and 7.
 * @param onOff 0 deactivates the pullup, 1 activates it. The Macros
 *      PULLUP_OFF and PULLUP_ON should be used for this parameter.
 *
 * @see setPinMode()
 */
void setPinPullup( uint8_t port, uint8_t pinNumber, uint8_t onOff);

/**
 * A GPIO-Pin which has formerly been programmed to be an output can be 
 * programmed to put out a High- or a Low-Voltage-Level.
 *
 * Example: Program GPIO-Pin PA2 as output, and put out a High-Level:
 * {@code 
 *      setPinMode( port_A, 2, OUTPUT );
 *      writeDigital( port_A, 2, HIGH_LEVEL );
 * }
 *
 * @param port One of the Macros `port_A` to `port_L` should be passed for this
 *      parameter.
 * @param pinNumber The number of the Pin. Must be between 0 and 7.
 * @param voltageLevel Zero means a low-level, non-zero a high-level. The 
 *      Macros `LOW_LEVEL` or `HIGH_LEVEL` can be used.
 *
 * @see setPinMode() 
 */
void writePin( uint8_t port, uint8_t pinNumber, uint8_t voltageLevel );

/**
 * Reads the voltage-level, that an external hardware feeds into a GPIO-Pin,
 * which has formerly been programmed to be an input (with or without 
 * activated internal pullup-resistor).
 *
 * @param port One of the Macros `port_A` to `port_L` should be passed for this
 *      parameter.
 * @param pinNumber The number of the Pin. Must be between 0 and 7.
 * @return 0 for a low-level, 1 for a high-level.
 *
 * @see setPinMode(), setPinPullup()
 */
uint8_t readPin( uint8_t port, uint8_t pinNumber );

/**
 * Toggles the voltage-level-state of an output-pin. (If the Level has been 
 * low it will change to high and vice versa).
 *
 * @param port One of the Macros `port_A` to `port_L` should be passed for this
 *      parameter.
 * @param pinNumber The number of the Pin. Must be between 0 and 7.
 *
 * @see setPinMode(), writePin()
 */
void togglePin( uint8_t port, uint8_t pinNumber );


//////////////////////////////////////////////////////////////////////////
// C-API-functions for manipulating a whole Port (all 8 Pins at once)
//////////////////////////////////////////////////////////////////////////

/**
 * Sets some (or all) of the eight GPIO-Pins of a port to outputs or inputs.
 *
 * Example: Set pins PD7...PD4 to outputs, and pins PD3...PD0 to inputs.
 * since all 8 pins of the port are programmed, the last parameter `mask` 
 * is 0xFF:
 * {@code 
 *      setPortMode( port_D, 0xF0, 0xFF ); 
 * }
 *
 * Example: Set Pins PL7 and PL6 to outputs, and PL5 and PL4 to inputs, and
 * leave PL3 to PL0 as they are. The `mask`-Parameter is 0xF0 = 0b11110000, so
 * only pins PL7 to PL4 are affected. The `mode`-Parameter is 0xC0 = 0b11000000,
 * so PL7 and PL6 become outputs, PL5 and PL4 become inputs.
 * {@code 
 *      setPortMode( port_L, 0xC0, 0xF0 ); 
 * }
 *
 * @param port One of the Macros port_A to port_L should be used for this
 *      parameter.
 * @param mode An 8-Bit-Pattern. If the corresponding Bit in mask is 1, a 
 *      0-Bit in mode makes the corresponding Pin an input, a 1-Bit makes 
 *      it an output.
 * @param mask An 8-Bit-Pattern. Only Pins whose corresponding Bit in mask
 *      is 1 will be affected, the other Pins remain unchanged. If all 8 pins
 *      have to be configured, pass 0xFF for mask.
 */
void setPortMode (uint8_t port, uint8_t mode, uint8_t mask );

/**
 * Activates/deactivates the internal pullup-Resistors of some of the eight 
 * GPIO-Pins of a port. Pins, whoose pullup-Resistors are turned on or off,
 * should already have been configured as inputs, when calling this function.
 *
 * Example: Program all pins PK7 to PK0 as inputs. Then activate the internal
 *      pullup-resistors of pins of PK7 and PK6, and deactivate them for 
 *      pins PK5 to PK0 (all 8 pins are configured:
 * {@code
 *      setPortMode( port_K, 0x00, 0xFF );
 *      setPortPullup( portK, 0xC0, 0xFF );
 * }
 *
 * @param port One of the Macros port_A to port_L should be used for this
 *      parameter.
 * @param pullup An 8-Bit-Pattern. If the corresponding Bit in `mask` is 1, a 
 *      0-Bit in `pullup`deactivates the pullup of the corresponding Pin, 
 *      a 1-Bit activates it.
 * @param mask An 8-Bit-Pattern. Only Pins whose corresponding Bit in `mask`
 *      is 1 will be affected, the other Pins remain unchanged. If all 8 pins
 *      have to be configured, pass 0xFF for mask.
 *
 * @see setPortMode()
 */
void setPortPullup( uint8_t port, uint8_t pullup, uint8_t mask );

/**
 * After programming some pins of a port to be outputs, with this
 * function the voltage-levels of these pins can be set.
 *
 * Example: Porgram Pins PC7...PC4 to outputs, and PC3...PC0 to inputs. Then
 * put out a low-level on Pins PC7 and PC5, a high-level on PC6 and PC4, and
 * don't touch Pins PC3..PC0, since they are inputs:
 * {@code
 *      setPortMode( port_C, 0xF0, 0xFF ); //0xF0=0b11110000, 0xFF=0b11111111
 *      writePort( port_C, 0x50, 0xF0 );   //0x50=0b01010000, 0xF0=0b11110000
 * }
 *
 * @param port One of the Macros `port_A` to `port_L` should be passed for this
 *      parameter.
 * @param voltageLevels An 8-Bit-pattern for the voltage-levels. If 
 *      the corresponding Bit in `mask` is 1, a 1-Bit in `voltageLevels` results
 *      in a High-Level on the corresponding pin, 0 produces a low-level.
 * @param mask An 8-Bit-Pattern. Only Pins whose corresponding Bit in `mask`
 *      is 1 will be affected, the other Pins remain unchanged. If all 8 pins
 *      have to be configured, pass 0xFF for `mask`.
 *
 * @see setPortMode()
 */
void writePort( uint8_t port, uint8_t voltageLevels, uint8_t mask );

/**
 * Returns the voltage-Levels of some pins of a port as an 8-Bit-Pattern. 
 *
 * Example: Program the pins PH7...PH4 as inputs, PH3...PH0 to outputs, and 
 *      read in the voltage-levels of Pins PH7 and PH6
 * voltage-levels:
 * {@code
        setPortMode( port_H, 0xF0,  0xFF ); //0xF0=0b11110000, 0xFF=0b11111111
        uint8_t levels = readPort( port_H, 0xC0 ); //0xC0=0b11000000
   }
 * For example, if `levels` contains a value of 0x80 (1000000 binary) 
 * after execution of this code, then there is a  high-Levels on pin PH7 and
 * a low-Levels on pin PH6. The other 0-Bits have no meaning, since they have
 * been masked out (Parameter `mask` was 0xC0=0b11000000).
 *
 * @param port One of the Macros `port_A` to `port_L` should be passed for this
 *      parameter.
 * @param mask The return-value of this function only contains 0/1-Bits 
 *      representing the voltage-level of a pin, if the corresponding bit
 *      in `mask` is 1. If a Bit in `mask` is 0, the corresponding Bit in the
 *      return-value is 0. In order to read the voltage-levels of all 8 pins 
 *      of a port, pass 0xFF to `mask`.
 * @return An 8-Bit-Value, representing the voltage-levels of those pins,
 *      whose corresponding `mask`-Bit is 1. A 1-Bit in the return-value
 *      represents a high-voltage-level, a 0-Bit represents a low-level
 *      or a masked out bit.
 *
 * @see setPortMode(), setPortPulup()
 */
uint8_t readPort( uint8_t port, uint8_t mask);

/**
 * After programming some pins of a port to be outputs, with this
 * function the voltage-levels of these pins can be toggled.
 *
 * Example: Toggle the Pins PE7, PE5, PE3 and PE1 (which are outputs), and 
 * don't touch Pins PE6, PE4, PE2 and PE0:
 * {@code
        togglePort( port_E, 0xAA );    //0xAA = 0b10101010
   }
 *
 * @param port One of the Macros `port_A` to `port_L` should be passed for this
 *      parameter.
 * @param mask An 8-Bit-Pattern. Only Pins whose corresponding Bit in mask
 *      is 1 will be toggled, the other Pins remain unchanged. 
 *
 * @see setPortMode(), writePort()
 */
void togglePort( uint8_t port, uint8_t mask );


#ifdef __cplusplus
}
#endif


#ifdef __cplusplus

//////////////////////////////////////////////////////////////////////////
// C++ Class (Wrapper) for a single GPIO-Pin
//////////////////////////////////////////////////////////////////////////

/**
 * class for a single GPIO-Pin. The pin can be programmed as input or output.
 * For Input-Pins an internal pullup-resistor can be activated, and their 
 * voltage-levels can be read in. For output-pins the voltage-level presented 
 * on the pin can be programmed.
 */
class GPIOPin
{
public:
    /**
     * A GPIOPin-Instance must be contructed with port an pinnumber.
     *
     * For example if you want to create an instance for pin PB6, use
     * {@code
     *     GPIOPin ledPin = GPIOPin( port_B, 6 );
     * }
     *
     * @param port One of the Makros `port_A` ... `port_K` should be used
     *      for this parameter.
     * @param pinNumber The number of the pin (between 0 and 7)
     * @param mode Use one of the macros `MODE_INPUT` (0) or `MODE_OUTPUT` (1)
     *      default-value is MODE_INPUT
     */
    GPIOPin( uint8_t port, uint8_t pinNumber, uint8_t mode = MODE_INPUT )
                : _port(port), _pinNumber(pinNumber)
    { setPinMode( mode ); }
    
    /**
     * Sets the GPIO-pin as input or output
     *
     * @param mode Use one of the macros `MODE_INPUT` (0) or `MODE_OUTPUT` (1)
     */
    void setPinMode( uint8_t mode ) 
    {
        ::setPinMode(_port,_pinNumber, mode);
    }

    /**
     * Activates or Deactivates the internal pullup-resistor for this pin. The
     * pin should have been configured as input, if this method is used.
     *
     * @param onOff: 0 or 1 to deactivate / activate the internal pullup-
     *      resistor. One of `PULLUP_OFF` or `PULLUP_ON` should be used.
     */
    void setPinPullup( uint8_t onOff)
    {
        ::setPinPullup(_port, _pinNumber, onOff);
    }
    
    /**
     * Puts out a high- or low-voltage-level at the GPIO-Pin. The pin should
     * be an output.
     *
     * @param voltageLevel: 0 or 1 (low- or high-level). Macros `LOW_LEVEL` and
     *      `HIGH_LEVEL` can be used for this parameter.
     */
    void writePin( uint8_t voltageLevel )
    {
        ::writePin(_port, _pinNumber, voltageLevel);
    }
    
    /**
     * Returns the voltage-Level of the GPIO-Pin
     *
     * @return `HIGH_LEVEL` (1) or `LOW_LEVEL` (0)
     */
    uint8_t readPin()
    {
        return ::readPin(_port, _pinNumber);
    }
    
    /**
     * Toggles the voltage-level of the GPIO-Pin. The pin should be an output.
     */
    void togglePin()
    {
        ::togglePin(_port, _pinNumber);
    }

private:
    uint8_t _port;
    uint8_t _pinNumber;
};

//////////////////////////////////////////////////////////////////////////
// C++ Class (Wrapper) for a GPIO-Port (8 pins)
//////////////////////////////////////////////////////////////////////////

 
/**
 * class for a GPIO-Port (all 8 Pins of one Port).
 */
class GPIOPort
{
public:

    /**
     * A GPIOPort-Instance must be contructed for a concrete port.
     *
     * @param port One of the Makros `port_A` ... `port_K` should be used
     *      for this parameter
     */
    GPIOPort(uint8_t port) : _port(port) { }
    
    /**
     * Sets some of the eight GPIO-Pins of the port to outputs or inputs.
     *
     * @param mode An 8-Bit-Pattern. If the corresponding Bit in `mask` is 1, a
     *      0-Bit in `mode` makes the corresponding Pin an input, a 1-Bit makes
     *      it an output.
     * @param mask An 8-Bit-Pattern. Only Pins whose corresponding Bit in `mask`
     *      is 1 will be affected, the other Pins remain unchanged. If all 8 
     *      pins have to be configured, don't pass a value for mask 
     *      (default-value=0xFF).
     *
     * @see setPortMode()
     */
    void setPortMode( uint8_t mode, uint8_t mask=0xFF)
    {
        ::setPortMode(_port, mode, mask);
    }
    
    /**
     * Activates/Deactivates some of the internal pullup-resistors of input-
     * port-Pins.
     *
     * @param pullup An 8-Bit-Pattern. If the corresponding Bit in `mask` is 1,
     *      a 0-Bit in `pullup` deactivates the internal pullup-resistor of the
     *      corresponding Pin, a 1-Bit activates it.
     * @param mask An 8-Bit-Pattern. Only Pins whose corresponding Bit in `mask`
     *      is 1 will be affected, the other Pins remain unchanged. If all 8 
     *      pins have to be configured, don't pass a value for mask 
     *      (default-value=0xFF).
     */
    void setPortPullup( uint8_t pullup, uint8_t mask=0xFF )
    {
        ::setPortPullup( _port, pullup, mask );
    }
    
    /**
     * After programming some pins of this port to be outputs, with this
     * method the voltage-levels of these pins can be set.
     * 
     * @param voltageLevels An 8-Bit-pattern for the voltage-levels. If the
     *      corresponding Bit in `mask` is 1, a 1-Bit in `voltageLevels` results
     *      in a High-Level on the corresponding pin, 0 produces a low-level.
     * @param mask An 8-Bit-Pattern. Only Pins whose corresponding Bit in `mask`
     *      is 1 will be affected, the other Pins remain unchanged. If all 8 
     *      pins have to be configured, don't pass a value for mask 
     *      (default-value=0xFF).
     */
    void writePort( uint8_t voltageLevels, uint8_t mask=0xFF )
    {
        ::writePort(_port, voltageLevels, mask );
    }
    
    /**
     * Returns the voltage-Levels of some pins of the port as an 8-Bit-Pattern.
     *
     * @param mask The return-value of this function only contains 0/1-Bits
     *      representing the voltage-level of a pin, if the corresponding bit
     *      in `mask` is 1. If a Bit in `mask` is 0, the corresponding Bit in
     *      the return-value will be 0. In order to read the voltage-levels of 
     *      all 8 pins of a port, don't pass a value for `mask`
     *      (default-value=0xFF).
     *
     * @return An 8-Bit-Value, representing the voltage-levels of those pins,
     *      whose corresponding `mask`-Bit is 1. A 1-Bit in the return-value
     *      represents a high-voltage-level, a 0-Bit represents a low-level
     *      or a masked out bit.
     */
    uint8_t readPort( uint8_t mask=0xFF )
    {
        return ::readPort( _port, mask );
    }

    /**
     * After programming some pins of the port to be outputs, with this
     * method the voltage-levels of these pins can be toggled.
     *
     * @param mask An 8-Bit-Pattern. Only Pins whose corresponding Bit in `mask`
     *      is 1 will be toggled, the other Pins remain unchanged. If all
     *      8 pins of a port have to be toggled, don't pass a value for mask
     *      (default-value=0xFF).
     */
    void togglePort( uint8_t mask=0xFF )
    {
        ::togglePort( _port, mask );
    }

private:
    uint8_t _port;
};

#endif

#endif /* GPIO_H_ */
