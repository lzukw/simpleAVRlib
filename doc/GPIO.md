# GPIO-Module #

This module consists of the files "GPIO.h" and "GPIO.c".

Both files can be compiled with the avrgcc-C-Compiler or the C++-Compiler. If 
the C++-Compiler is used, an object-oriented interface is available, which is 
easier to use. If a C-Compiler is used, then functions must be called.

## The AVR-GPIO-pins ##

GPIO means "General purpose input/output". Most pins of an AVR-Microcontroller
can be used as a GPIO-Pin.

A GPIO-pin can be programmed to be an input or an output. An output can put out 
a high- or a low-voltage-level. This can be used, to turn on/off motors, 
electromagnetic valves, LEDs, etc. Inputs can be used to read the state of
digital sensors (like an overtemperature-sensor, an overpressure-sensor, etc.)
or the state of a button or a switch.

### Ports ###

Eight GPIO-Pins together are a GPIO-port.  The GPIO-ports are named port A,
port B, ..., port K. Have a look at the datasheet of your AVR-microcontroller 
to find out, which pins and which ports actually exist your microconttoller.

The single GPIO-Pins are named for example PB3, this means that the Pin belongs 
to port B and is the third pin of this port. The number is in the range 0...7.
So for example port D conists of the pins PD0, PD1, ..., PD7.

### Alternative functions of GPIO-pins ###

After power on (reset), the pins are GPIO-Pins. But most Pins have one or more 
alternative functions. For example on an ATmega2560, Pins PE0 and PE1 have 
alternarive functions RXD0 and TXD1. If the serial interface USART0 is used in 
the program, then Pins PE0 and PE1 can't be used as GPIO-Pins any longer, but 
are used by the USART0-hardware to be a serial interface. Pin PE0 has a 
second alternative function: PCINT8 - pin change interrupt number 8.

If you have a microncontroller with a bootloader (all Arduino-Boards have one),
the the bootloader leaves the USART (USART0 on ATmega2560) turned on, so that
the normal GPIO-Pin-function is not available on the two pins used bei the 
serial interface.

## Using the GPIO-Module with C-function-syntax ##

There are two possible ways to use this module. You can use functions for
single GPIO-Pins, of for a whole GPIO-Port.

### Using Pin-Functions ###

First you have to make a pin an input or output. For inputs you have to
decide, wheter to activate or deactivate the internal-pullup-resistor (activate
it to prevent the pin from a floating voltage-potential, if you connect only
a button or switch to it). Then you can read in the voltage-level on the input.
For example:

```C
// ...
setPinMode( port_L, 3, MODE_INPUT );    //makes GPIO-Pin PL3 an input
setPinPullup ( port_L, 3, PULLUP_ON );  //acitvated the internal pullup-resistor
//...
uint8_t level = readPin( port_L, 3 );
```

After `level = readPin( port_L, 3 );` the variable `level` has a value of 
either `LOW_LEVEL` (0) or `HIGH_LEVEL` (1).

If you program a GPIO-pin to be an output, you can set the voltage-level of the
output to a high- or a low-voltage-level:

```C
// ...
setPinMode( port_B, 7, MODE_OUTPUT );    //makes GPIO-Pin PB7 an output
//...
writePin( port_B, 7, HIGH_LEVEL ); //puts out a high-level on PB7
```

The C-functions contained in GPIO.h for manipulationg single pins are:

- `setPinMode()`
- `setPinPullup()`
- `writePin()`
- `readPin()`
- `togglePin()`

### Using Port-Functions ###

TODO

## Using the GPIO-Module with C++-object-oriented-syntax ##

TODO

## Further information ##

The function-API is explainer very well in the header GPIO.h.
