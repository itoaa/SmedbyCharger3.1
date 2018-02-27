/*
 * ChargeDB11.cpp
 *
 *  Created on: 17 sep. 2017
 *      Author: Ola Andersson
 *      Version 1.0
 *      	See h-file for info
 *      Version 1.1
 *      	Standard C, and no DB-task
 */

#include "ChargeDB11.h"


void ChargeDBinit()
{
//	Global_vars.Charger_state = 0;
}


void Set_var(int ID, int Value)
{
	int * Temp_pointer;
	Temp_pointer = (int*)&Global_vars + (ID*2);
	*Temp_pointer = Value;
}

int Get_var(int ID)
{
	int * Temp_pointer;
	Temp_pointer = (int*)&Global_vars + (ID * 2);
	return(*Temp_pointer);

}

void Set_index(int Index, char Value)
{
	char * Temp_pointer;
	Temp_pointer = (char*)&Global_vars + (Index);
	*Temp_pointer = Value;
}

char Get_index(int Index)
{
	char * Temp_pointer;
	Temp_pointer = (char*)&Global_vars + (Index);

	return(*Temp_pointer);

}


