#include "Payload.h"
#include <iostream>

using namespace std;
Payload::Payload()
{
	powerState = false;
}

Payload::Payload(bool state)
{
	
	if(state == 0 || state == 1)
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
	if (state == 1 || state == 0)
	{
		powerState = state;
	}
	else
	{
		cout << "ERROR: not a valid state" << endl;
	}
}