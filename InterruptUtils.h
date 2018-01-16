/*
 * InterruptUtils.h
 *
 * Created: 13.01.2018 07:20:31
 *  Author: lzukw
 */ 


#ifndef INTERRUPTUTILS_H_
#define INTERRUPTUTILS_H_


#include <avr/interrupt.h>


#ifdef __cplusplus
extern "C" {
#endif

/**
 * Makros used to individually enable or disalbe specific interrupts
 */
#define INT_ON      1
#define INT_OFF     0

/**
 * After a call to this function, no Interrupts will be executed, until the
 * function allowEnabledInterrupts() is called
 */
inline void blockAllInterrupts() { cli(); }
    
/**
 * After calling this function, in general Interrupts are allowed. But only 
 * those Interrupts will be executed, whose Enable-Flag has been set.
 */
inline void allowEnabledInterrupts() { sei(); }

#ifdef __cplusplus
}
#endif

#endif /* INTERRUPTUTILS_H_ */