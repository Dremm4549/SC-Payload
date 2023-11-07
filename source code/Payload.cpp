#include "Payload.h"
#include <iostream>

using namespace std;
Payload::Payload()
{
	powerState = false;
}

Payload::Payload(bool state)
{
	
	if(state == true || state == false)
	{
		powerState = state;
	}
	else
	{
		powerState = false;
	}
}

bool Payload::GetPowerState()
{
	return powerState;
}

void Payload::SetPowerState(bool state)
{
	if (state == true || state == false)
	{
		powerState = state;
	}
	else
	{
		cout << "ERROR: not a valid state" << endl;
	}
}