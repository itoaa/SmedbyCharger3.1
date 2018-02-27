/*
 * HW11.h
 *
 *  Created on: 7 aug. 2017
 *      Author: Ola Andersson
 *
 *      All definitions spesific to Smedbycharger ver 1.1 PCB
 */

#ifndef HW11_H_
#define HW11_H_


// Setup Hardware constatns for SmedbyCharger PCB Ver 1.1 without CAN-Bus
// *************************************************************************************************
#ifdef  SmedbyCharger11					// Parameter definition for SmedbyCharger 1.1 without CAN buss.
  #define     SerialEnabled				// Enable serial ouput on this hardware.
  #define     BaudRate 115200			// Sepeed for cerial comunication
  int  InputVoltPin  = PC2;				// Pin used to measure Battery-volt PC2 = A2
  int  OutputCurrentPin = PC0;			// Pin used to measure Motor-volt PC0 = A2
  int  OutputVoltPin = PC1;				// Try to measure output-volt PC1 = A1
  int  Pin12V = PC3;						// Pin used to measure 12 volt rail PC3 = A3
  int  TemperaturPin = 7;				// Pin used to measure mosfet-temperatur
  int  pwmPin = 9;						// Pin used for PWM-charge-output
  int  Temp_Measure_type = 2;			// Type 1 = NTC-resistor, 2 = DS1820 temp sensor.
  int  Current_Measure_type = 3;		// Type 1 = 5A, 2 = 20A, 3 = 30A              ( Defines witch type of current sense sensor is used.
  int  ChargeLed1 = 5;					// Red LED
  int  ChargeLed2 = 4;					// Yelow LED
  int  ChargeLed3 = 3;					// Green LED
  int  ButtonPin = 02;


 #endif




#endif /* HW11_H_ */
