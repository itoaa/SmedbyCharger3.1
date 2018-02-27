/*
 * Volt20.cpp
 *
 *  Created on: 5 aug. 2017
 *      Author: Ola Andersson
 *      Dokumentation in h-file
 */

#include "Volt20.h"
#include "stdlib.h"

Volt::Volt(int pin, int MaxVolt)
{
	_maxVolt = MaxVolt;
	_analogIn = pin;
	pinMode(_analogIn,INPUT);
}


// Subrutine to measure inputvoltagePin (multiple times for normalization)
unsigned int Volt::readVolt(void)
{
//    Filter volt(13);                                                    // Setuf filter with 13 positions
//    for(int i=0;i<13;i++)                                               // Fill Filter buffer with reads.
//    {
  //    volt.addValue(map(analogRead(_analogIn),0,1023,0,_maxVolt));      // Read ADC-Value, remap to 0 to _maxVolt and put in to filter buffer
//    }
 //   return (volt.getFilteredValue());                                   // Return average value


	//return(map(analogRead(_analogIn),0,1023,0,_maxVolt));
	unsigned int retur = 5 * _maxVolt / 1023;
	return (retur);
}
