
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
// SmedbyCharger ver 3.1 utvecklas i Eclipse, AVR plugin, FreeRTOS10
// Version 3.1 kommer att ta ett nytt grepp om globala variabler och
// ersätta dessa med en databas-process som övriga processer kan kommunisera
// med för att få tillgång till data i systemet.
// rev. För att spara minne  kommer bara två prosesser att användas.
// 1 "Real time" där laddare och DB ligger
// 2 "Interactive" där kommunikation till CAN och/eller Serieport ordnas.
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <avr/io.h>
#include <avr/interrupt.h>

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/* this is from avr/time.h, but it is not released into the main stream currently */
#include "time.h"

/* serial interface include file. */
#include <serial.h>

#include "ChargeDB11.h"
// #include "DBQuery.h"
#include "LogViewSerial20.hpp"
#include "Volt20.h"
#include "Current20.h"

/*-----------------------------------------------------------*/
/* Create reference to the handle for the serial port. */
extern xComPortHandle xSerialPort;

static void TaskCharger(void *pvParameters);  // Main Charger task

static void TaskSerialSend(void *pvParameters);
/*-----------------------------------------------------------*/

// Define for witch hardware to compile
 #define SmedbyCharger11
// #define SmedbyCharger11CAN

 #include "HW11.h"
//#include "HW11CAN.h"

GlobalVarStruct Global_vars;

Volt InVolt(InputVoltPin,6300);
Volt OutVolt(OutputVoltPin,6300);
Current OutCurrent(OutputCurrentPin,1); // 5A modell

/* Main program loop */
int main(void) __attribute__ ((OS_main));

int main(void)
{
	// Set Analog Ref to external
	ADMUX&=~(1<<REFS0);		// Clear bit
	ADMUX&=~(1<<REFS1);		// Clear bit

	// turn on the serial port for debugging or for other USART reasons.
	xSerialPort = xSerialPortInitMinimal( USART0, 38400, portSERIAL_BUFFER_TX, portSERIAL_BUFFER_RX); //  serial port: WantedBaud, TxQueueLength, RxQueueLength (8n1)

//	avrSerialxPrint_P(&xSerialPort, PSTR("\r\n\n\nHello World!\r\n")); // Ok, so we're alive...

    xTaskCreate(
		TaskCharger
		,  (const portCHAR *)"RedLED" // Main Arduino Mega 2560, Freetronics EtherMega (Red) LED Blink
		,  256				// Tested 9 free @ 208
		,  NULL
		,  3
		,  NULL ); // */

    xTaskCreate(
		TaskSerialSend
		,  (const portCHAR *)"serialSendFunction" // Task/function doing all serial communication
		,  256				// chack 9 free @ 208?
		,  NULL
		,  3
		,  NULL ); // */


//	avrSerialxPrintf_P(&xSerialPort, PSTR("Free Heap Size: %u\r\n"), xPortGetFreeHeapSize() ); // needs heap_1,  heap_2 or heap_4 for this function to succeed.
//	avrSerialxPrintf_P(&xSerialPort, PSTR("Minimum Free Heap Size: %u\r\n"), xPortGetMinimumEverFreeHeapSize() ); // needs heap_4 for this function to succeed.
//	avrSerialxPrintf_P(&xSerialPort, PSTR("Stack High Water Mark: %u\r\n"), uxTaskGetStackHighWaterMark( NULL ) ); // Check stack Margin.

	vTaskStartScheduler();

	avrSerialxPrint_P(&xSerialPort, PSTR("\r\n\n\nGoodbye... no space for idle task!\r\n")); // Doh, so we're dead...

}

/*-----------------------------------------------------------*/


static void TaskCharger(void *pvParameters) // Main charger task
{
    (void) pvParameters;
    TickType_t xLastWakeTime;
	/* The xLastWakeTime variable needs to be initialised with the current tick
	count.  Note that this is the only time we access this variable.  From this
	point on xLastWakeTime is managed automatically by the vTaskDelayUntil()
	API function. */
	xLastWakeTime = xTaskGetTickCount();
	DDRD |= _BV(DDB4);


    for(;;)
    {
    	PORTD |=  _BV(PORTD4);       // main (red IO_B7) LED on. EtherMega LED on
    	vTaskDelayUntil( &xLastWakeTime, ( 1100 / portTICK_PERIOD_MS ) );

    	PORTD &= ~_BV(PORTD4);       // main (red IO_B7) LED off. EtherMega LED off
    	vTaskDelayUntil( &xLastWakeTime, ( 1100 / portTICK_PERIOD_MS ) );

    	if (	Get_var(ChargerState) == 1)                                   // While charge status = Monitor
		{
			Set_var(ChargerInVolt,InVolt.readVolt());
			Set_var(ChargerOutVolt,OutVolt.readVolt());
			Set_var(ChargerOutAmp,OutCurrent.readCurrent());

			// Monitor
		}
		if (	Get_var(ChargerState) == 2)                                  // While charge status = FastCharge
		{
			// FastCharge
		}
		if (	Get_var(ChargerState) == 3)                                  // While charge status = Trickle Charge
		{
			// Trickle charge
		}


		vTaskDelayUntil( &xLastWakeTime, ( 1100 / portTICK_PERIOD_MS ) );

    }

}

/*-----------------------------------------------------------*/
static void TaskSerialSend(void *pvParameters)
{
    (void) pvParameters;
    TickType_t xLastWakeTime;
	/* The xLastWakeTime variable needs to be initialised with the current tick
	count.  Note that this is the only time we access this variable.  From this
	point on xLastWakeTime is managed automatically by the vTaskDelayUntil()
	API function. */
	xLastWakeTime = xTaskGetTickCount();

	LogViewSerial mySerial(9600);

	Set_var( ChargerOutVolt,3600 );
	Set_var( ChargerInVolt,4800);
	Set_var( ChargerInAmp,8);
	Set_var( ChargerState,1);


    for(;;)
    {
	//	xSerialxPrintf_P(&xSerialPort, PSTR("Green: Current Timestamp: %lu xTaskGetTickCount(): %u\r\n"), time(NULL), xTaskGetTickCount());
	//	xSerialxPrintf_P(&xSerialPort, PSTR("Green: Minimum Free Heap Size: %u\r\n"), xPortGetMinimumEverFreeHeapSize() ); // needs heap_4 for this function to succeed.
   // 	xSerialxPrintf_P(&xSerialPort, PSTR("SerialSend: Stack High Water Mark, serial task: %u\r\n"), uxTaskGetStackHighWaterMark( NULL ) ); // Check stack Margin.


		mySerial.updateChargerState ( Get_var( ChargerState ) );
		mySerial.updateBatteryVolt( Get_var( ChargerOutVolt ) );
        mySerial.updateBatteryCurrent( Get_var( ChargerOutAmp) );   // Update _BatteryCurrent private variable
        mySerial.updateBatteryTemp(25);                   // Update _BatteryTemp private variable
        mySerial.updateInputVolt(Get_var( ChargerInVolt ) );             // Update _InputVoltage private variable
        mySerial.updatePWM( Get_var( ChargerPWM ) );                         // Update _pwm private variable
        mySerial.updatemAh(2200);                         // Update _mAh private variable
        mySerial.sendSerial();

		vTaskDelayUntil( &xLastWakeTime, ( 1100 / portTICK_PERIOD_MS ) );

    }
}

/*---------------------------------------------------------------------------*/
