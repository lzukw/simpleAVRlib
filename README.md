# simpleAVRlib - Library for AVR-Microncontrollers #

## Overview ##

This library provides simple access to 

- GPIO-Pins, 
- External Interrupts, 
- Timers and 
- USART-interfaces 

of AVR-Microcontrollers. It is intended to work
for the ATmega2560 and the ATmega328p. Main focus is on the ATmega2560.
Probably many things in this library also work for other AVR-microcontrollers.

By using this library you don't have to manipulate bits in 
Special-Function-Registers, but you can use functions or classes with 
descriptive names.

For examle - make Pin PD3 (the third GPIO-Pin of Port D) an input:

Instead of:

```C
DDRD |= (0x01<<3);
```

you can write (in C)

```C
setPinMode( port_D, 3, MODE_INPUT );
```

or (in C++)

```C
GPIOPin pd3 = GPIOPin( port_D, 3, MODE_INPUT );
```

## Audience ##

This library is intended for two types of programmers: 
- Programmers using the Arduino-IDE, who want to learn more about AVR-
  Microcontrollers
- Programmers using the avrgcc-toolset (for example with Atmel-Studio) 
  who want to make their code more readable.

If you have programmed Arduino Uno (with the ATmega328p) or Arduino Mega (with
the Atmega2560) with the Arduino-IDE, and want to learn more about the internals
of AVR-Microcontrollers, this library is a good intermediate step, before 
directly manipulating bits in Special-Function-Registers.

In contrast to the core library of the Arduino-IDE, this library doesn't hide 
hardware-specific things to the programmer. For example without knowing how 
Hardware-PWM works using the Timers, you won't be able to get a PWM-Signal 
p and running. The necessary information can be found in the relevant section 
(for example 8-Bit-Timer/Counters) of datasheet of the Micronconctroller, easier 
to read.

## Code-Example ##

### Code-Example using C ###

The following code-example is also included in the examples-directory
(File testGPIOPin.c)

Connect a button between Pin PD2 and GND, and two LEDs (with 220Ohm-Series-
resistors) between VCC and Pins PB0, PB1. 

Each Time the button is pressed, the two LEDs toggle. (More exactly the LEDs
toggle on releasing the button). 

```C
#include <stdint.h>
#include <util/delay.h>

#include "GPIO.h"

int main(void)
{
    //configure Button: Pin PD2 is an input with activated pullup-resistor
    //The button is connected between PD2 and GND
    setPinMode( port_D, 2, MODE_INPUT );
    setPinPullup( port_D, 2, PULLUP_ON );

    //configure Pin PB0 (connected to LED0) as output. Turn on this LED by 
    //putting out a Low-Voltage-Level (The LED is connected in series with a
    //220 Ohm-resistor between VCC and PB0).
    setPinMode( port_B, 0, MODE_OUTPUT );
    writePin( port_B, 0, LOW_LEVEL );
    
    //configure Pin PB1 (connected to LED1) as output. Turn off this LED by
    //putting out a High-Voltage-Level
    setPinMode( port_B, 1, MODE_OUTPUT );
    writePin( port_B, 1, HIGH_LEVEL );
    
    uint8_t oldbuttonState = LOW_LEVEL;
    
    while (1) 
    {
        //check for rising edges on input-pin pd2 (these occur on releasing
        //the button):
        uint8_t buttonState = readPin( port_D, 2 );
        if (oldbuttonState == LOW_LEVEL && buttonState == HIGH_LEVEL) 
        {
            togglePin( port_B, 0 );
            togglePin( port_B, 1 );
        }
        
        oldbuttonState = buttonState;        
        _delay_ms(100);
    }
}
```

### Code-Example using C++ ###

The following code-example is also included in the examples-directory
(File testGPIOPin.cpp)

Same program as above, but now using C++-objects.

```C
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
```

## Further information ##

Further documentation can be found in the comments in the header-Files, and in 
the directory named "doc". At least for using Timers with Hardware-PWM you 
should refer to the relevant sections of the datasheet of the microcontroller 
(or similar sources of information).

