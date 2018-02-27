/*
 * LogViewSerial20.cpp
 *
 *  Created on: 5 aug. 2017
 *      Author: Ola Andersson
 */

#include "LogViewSerial20.hpp"

LogViewSerial::LogViewSerial(int BaudRate)
{
	RTP.seconds = 0;
}


// Suprutines to update values to send to logworks
void LogViewSerial::updateChargerState(int state)
{
  RTP.state = state;
}

void LogViewSerial::updateBatteryVolt(int volt)
{
  RTP.BatteryVolt = volt;
}
void LogViewSerial::updateBatteryCurrent(int current)
{
  RTP.BatteryCurrent = current;
}
void LogViewSerial::updateBatteryTemp(int temp)
{
  RTP.BatteryTemp = temp;
}
void LogViewSerial::updateInputVolt(int volt)
{
  RTP.InputVolt = volt;
}
void LogViewSerial::updatePWM(int pwm)
{
  RTP.Pwm = pwm;
}
void LogViewSerial::updatemAh(int mAh)
{
  RTP.mAh = mAh;
}


// Subrutine to send latest value to serialport/LogView.
// No parameters is needed, all valuse need to be updated before call
void LogViewSerial::sendSerial()
{
	// print all variables in Logview styel to serialport.
	// Need to mach Logview-ini-file.

	xSerialxPrintf_P(&xSerialPort, PSTR("$1;%u;%u;%u;%u;%u;%u;%u;%u;0\r\n"), RTP.state, RTP.seconds, RTP.BatteryVolt, RTP.BatteryCurrent, RTP.BatteryTemp, RTP.InputVolt, RTP.Pwm, RTP.mAh);
	RTP.seconds++;

 }

