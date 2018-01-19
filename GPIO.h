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
// Macros used as Arguments for the API-functions/methods
////////////////////////////////////////////////////////////////////////////

/** 
 * GPIO-Pins are grouped in in "ports". 8 pins together form a port.
 * These Macros should be used as arguments for functions/methods,
 * that receive a port as parameter.
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
 * Argument for function `setPinMode`, constructor of `GPIOPin` and method
 * `GPIOPin::setPinMode`
 */
#define MODE_INPUT      0
#define MODE_OUTPUT     1

/**
 * Argument for function `setPinPullup` and method `GPIOPin::setPinPullup`
 */
#define PULLUP_OFF      0
#define PULLUP_ON       1

/**
 * Argument for function `writePin` and method `GPIOPin::writePin`. Return
 * value for function `readPin` and method `GPIOPin::readPin`.
 */
#define HIGH_LEVEL  1
#define LOW_LEVEL   0

////////////////////////////////////////////////////////////////////////////
// C-API-Functions for manipulating a single Pin
////////////////////////////////////////////////////////////////////////////

/**
 * Programs a single GPIO-Pin to be an output or an input. 
 *
 * @param port A number between 0 (port A) and up to 11 (port L). One of the 
 *      Macros port_A to port_L should be used for this parameter.
 * @param pinNumber The number of the Pin. Must be between 0 and 7. 
 * @param mode `MODE_OUTPUT` or 1 to make the pin an output, `MODE_INPUT` or 0
 *      to make it an input.
 */
void setPinMode( uint8_t port, uint8_t pinNumber, uint8_t mode );

/**
 * Activates or deactivates the internal-pullup-resistor of a pin, that has
 * formerly been programmed to be an input.
 *
 * @param port A number between 0 (port A) and up to 11 (port L). One of the 
 *      Macros port_A to port_L should be used for this parameter.
 * @param pinNumber The number of the Pin. Must be between 0 and 7.
 * @param onOff `PULLUP_OFF` or 0 deactivates the pullup-resistor, `PULLUP_ON`
 *      or 1 activates it.
 */
void setPinPullup( uint8_t port, uint8_t pinNumber, uint8_t onOff);

/**
 * A GPIO-Pin which has formerly been programmed to be an output can be 
 * programmed to put out a High- or a Low-Voltage-Level.
 *
 * @param port A number between 0 (port A) and up to 11 (port L). One of the 
 *      Macros port_A to port_L should be used for this parameter.
 * @param pinNumber The number of the Pin. Must be between 0 and 7.
 * @param voltageLevel `LOW_LEVEL` or 0 to put out a low-voltage-level. 
 *      `HIGH_LEVEL` or 1 to put out a high-level.
 */
void writePin( uint8_t port, uint8_t pinNumber, uint8_t voltageLevel );

/**
 * Reads the voltage-level, that an external hardware feeds into a 
 * GPIO-input-pin.
 *
 * @param port A number between 0 (port A) and up to 11 (port L). One of the 
 *      Macros port_A to port_L should be used for this parameter.
 * @param pinNumber The number of the Pin. Must be between 0 and 7.
 * @return `LOW_LEVEL` or 0 for a low-level, `HIGH_LEVEL` or 1 for a high-level.
 */
uint8_t readPin( uint8_t port, uint8_t pinNumber );

/**
 * Toggles the voltage-level-state of an output-pin. (If the Level has been 
 * low it will change to high and vice versa).
 *
 * @param port A number between 0 (port A) and up to 11 (port L). One of the 
 *      Macros port_A to port_L should be used for this parameter.
 * @param pinNumber The number of the Pin. Must be between 0 and 7.
 */
void togglePin( uint8_t port, uint8_t pinNumber );


//////////////////////////////////////////////////////////////////////////
// C-API-functions for manipulating a whole Port (all 8 Pins at once)
//////////////////////////////////////////////////////////////////////////

/**
 * Sets some (or all) of the eight GPIO-Pins of a port to outputs or inputs.
 *
 * @param port A number between 0 (port A) and up to 11 (port L). One of the 
 *      Macros port_A to port_L should be used for this parameter.
 * @param mode An 8-Bit-Pattern. If the corresponding Bit in `mask` is 1, a 
 *      0-Bit in mode makes the corresponding pin an input, a 1-Bit makes 
 *      it an output.
 * @param mask An 8-Bit-Pattern. Only Pins whose corresponding Bit in `mask`
 *      is 1 will be affected, the other Pins remain unchanged.
 */
void setPortMode (uint8_t port, uint8_t mode, uint8_t mask );

/**
 * Activates/deactivates the internal pullup-Resistors of some (or all) of the
 * GPIO-Pins of one port. Pins, whoose pullup-Resistors are turned on or off,
 * should already have been configured as inputs before calling this function.
 *
 * @param port A number between 0 (port A) and up to 11 (port L). One of the 
 *      Macros port_A to port_L should be used for this parameter.
 * @param pullup An 8-Bit-Pattern. If the corresponding Bit in `mask` is 1, a 
 *      0-Bit in `pullup` deactivates the pullup of the corresponding Pin, 
 *      a 1-Bit activates it.
 * @param mask An 8-Bit-Pattern. Only Pins whose corresponding Bit in `mask`
 *      is 1 will be affected, the other Pins remain unchanged.
 */
void setPortPullup( uint8_t port, uint8_t pullup, uint8_t mask );

/**
 * After programming some pins of a port to be outputs, with this
 * function the voltage-levels of these pins can be set.
 *
 * @param port A number between 0 (port A) and up to 11 (port L). One of the 
 *      Macros port_A to port_L should be used for this parameter.
 * @param voltageLevels An 8-Bit-pattern for the voltage-levels. If 
 *      the corresponding Bit in `mask` is 1, a 1-Bit in `voltageLevels` results
 *      in a High-Level on the corresponding pin, a 0-Bit produces a low-level.
 * @param mask An 8-Bit-Pattern. Only Pins whose corresponding Bit in `mask`
 *      is 1 will be affected, the other Pins remain unchanged.
 */
void writePort( uint8_t port, uint8_t voltageLevels, uint8_t mask );

/**
 * Returns the voltage-Levels of some (or all) pins of a port as an 
 * 8-Bit-Pattern. 
 *
 * @param port A number between 0 (port A) and up to 11 (port L). One of the 
 *      Macros port_A to port_L should be used for this parameter.
 * @param mask The return-value of this function only contains 0/1-Bits 
 *      representing the voltage-level of a pin, if the corresponding bit
 *      in `mask` is 1. If a Bit in `mask` is 0, the corresponding Bit in the
 *      return-value is 0.
 * @return An 8-Bit-Value, representing the voltage-levels of those pins,
 *      whose corresponding `mask`-Bit is 1. A 1-Bit in the return-value
 *      represents a high-voltage-level, a 0-Bit represents a low-level
 *      or a masked out bit.
 */
uint8_t readPort( uint8_t port, uint8_t mask);

/**
 * After programming some pins of a port to be outputs, with this
 * function the voltage-levels of these pins can be toggled.
 *
 * @param port A number between 0 (port A) and up to 11 (port L). One of the 
 *      Macros port_A to port_L should be used for this parameter.
 * @param mask An 8-Bit-Pattern. Only Pins whose corresponding Bit in `mask`
 *      is 1 will be toggled, the other Pins remain unchanged. 
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
     * For example if you want to create an instance for pin PB6 (the sixth pin
     * or port B), use
     * {@code
     *     GPIOPin ledPin = GPIOPin( port_B, 6 );
     * }
     *
     * @param port A number between 0 (port A) and up to 11 (port L). One of the 
     *      Macros port_A to port_L should be used for this parameter.
     * @param pinNumber The number of the pin (between 0 and 7)
     * @param mode `MODE_OUTPUT` or 1 to make the pin an output, `MODE_INPUT` 
     *      or 0 to make it an input. Default-value is `MODE_INPUT`
     */
    GPIOPin( uint8_t port, uint8_t pinNumber, uint8_t mode = MODE_INPUT )
                : _port(port), _pinNumber(pinNumber)
    { setPinMode( mode ); }
    
    /**
     * Turns the GPIO-pin into an input or an output
     *
     * @param mode `MODE_OUTPUT` or 1 to make the pin an output, `MODE_INPUT` 
     *      or 0 to make it an input. Default-value is `MODE_INPUT`
     */
    void setPinMode( uint8_t mode ) 
    {
        ::setPinMode(_port,_pinNumber, mode);
    }

    /**
     * Activates or Deactivates the internal pullup-resistor for this pin. The
     * pin should have been configured as input, if this method is used.
     *
     * @param onOff `PULLUP_OFF` or 0 deactivates the pullup-resistor, 
     *      `PULLUP_ON` or 1 activates it.
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
 * class for a GPIO-Port (all 8 pins of one Port).
 */
class GPIOPort
{
public:

    /**
     * Constructor
     *
     * @param port A number between 0 (port A) and up to 11 (port L). One of the
     *      Macros port_A to port_L should be used for this parameter.
     */
    GPIOPort(uint8_t port) : _port(port) { }
    
    /**
     * Sets some of the eight GPIO-Pins of the port to outputs or inputs.
     *
     * @param mode An 8-Bit-Pattern. If the corresponding Bit in `mask` is 1, a
     *      0-Bit in `mode` makes the corresponding Pin an input, a 1-Bit makes
     *      it an output.
     * @param mask An 8-Bit-Pattern. Only Pins whose corresponding Bit in `mask`
     *      is 1 will be affected, the other Pins remain unchanged.
     *      (default-value=0xFF, all 8 pins of the port are changed).
     *
     * @see setPortMode()
     */
    void setPortMode( uint8_t mode, uint8_t mask=0xFF)
    {
        ::setPortMode(_port, mode, mask);
    }
    
    /**
     * Activates/Deactivates some of the internal pullup-resistors of input-
     * port-Pins. These pins should already be inputs.
     *
     * @param pullup An 8-Bit-Pattern. If the corresponding Bit in `mask` is 1,
     *      a 0-Bit in `pullup` deactivates the internal pullup-resistor of the
     *      corresponding Pin, a 1-Bit activates it.
     * @param mask An 8-Bit-Pattern. Only Pins whose corresponding Bit in `mask`
     *      is 1 will be affected, the other Pins remain unchanged.
     *      (default-value=0xFF, all 8 pins of the port are changed, all 8 pins
     *      should be inputs).
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
     *      in a High-Level on the corresponding pin, a 0-Bit produces a
     *      low-level.
     * @param mask An 8-Bit-Pattern. Only Pins whose corresponding Bit in `mask`
     *      is 1 will be affected, the other Pins remain unchanged.
     *      (default-value=0xFF, all 8 pins of the port are changed, all 8 pins
     *      should be outputs).
     */
    void writePort( uint8_t voltageLevels, uint8_t mask=0xFF )
    {
        ::writePort(_port, voltageLevels, mask );
    }
    
    /**
     * Returns the voltage-Levels of some pins of the port as an 8-Bit-Pattern.
     * Note: Voltage-levels are returned correctly for inputs as well as for
     * outputs.
     *
     * @param mask The return-value of this function only contains 0/1-Bits
     *      representing the voltage-level of a pin, if the corresponding bit
     *      in `mask` is 1. If a Bit in `mask` is 0, the corresponding Bit in
     *      the return-value will be 0.
     *      (default-value=0xFF, all eight voltage-levels are returned).
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
     *      is 1 will be toggled, the other Pins remain unchanged.
     *      (default-value=0xFF, all 8 pins are toggled, all 8 pins should be
     *      outputs).
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
