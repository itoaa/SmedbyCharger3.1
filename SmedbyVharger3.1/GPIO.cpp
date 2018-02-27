/*
 * Volt20.cpp
 *
 *  Created on: 5 aug. 2017
 *      Author: Ola Andersson
 *      Dokumentation in h-file
 */

#include "GPIO.h"

void	pinMode(int pin, int Mode)

{
}

int 	analogRead(int pin)                     // Performe a measurement
{
	startAnalogConversion(pin,0);
	while( analogIsConverting() )
					_delay_us(25);     // yield until conversion ready

	return (analogConversionResult());
}
