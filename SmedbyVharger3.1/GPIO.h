/*
 * GPIO.h
 *
 *  Created on: 8 feb. 2018
 *      Author: Ola Andersson
 *
 *      Ver 1.0 is ported to Arduino
 *
 *      Converterar lite Aruino syntax för ex pinmode, digitalwrite mm
 *
 *
 */

#ifndef GPIO_H_
#define GPIO_H_
#include <avr/io.h>
#include "Filter10.h"
#include "avr/pgmspace.h"
// #include "avr/iom328p.h"
#include "digitalAnalog.h"
#include "util/delay.h"



#define INPUT 0
#define OUTPUT 1
// #define _BV(n) (1 << n)
/*
const int PROGMEM digital_pin_to_port_PGM[]= {
	PORTD, // 0
	PORTD,
	PORTD,
	PORTD,
	PORTD,
	PORTD,
	PORTD,
	PORTD,
	PORTB, // 8
	PORTB,
	PORTB,
	PORTB,
	PORTB,
	PORTB,
	PORTC, // 14
	PORTC,
	PORTC,
	PORTC,
	PORTC,
	PORTC,
};
*/
const int PROGMEM digital_pin_to_bit_mask_PGM[] = {
	_BV(0), /* 0, port D */
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(6),
	_BV(7),
	_BV(0), /* 8, port B */
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(0), /* 14, port C */
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
};
#define digitalPinToPort(P) ( pgm_read_byte( digital_pin_to_port_PGM + (P) ) )
#define digitalPinToBitMask(P) ( pgm_read_byte( digital_pin_to_bit_mask_PGM + (P) ) )

void	pinMode(int pin, int Mode);
int 	analogRead(int pin);                     // Performe a measurement

#endif /* GPIO_H_ */
