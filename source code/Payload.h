#pragma once

/// <summary>
/// this class will handle the power state
/// </summary>
class Payload
{
private:
	bool powerState;


public:
	/// <summary>
	/// Default constructor for the payload object
	/// </summary>
	Payload()
	{
        powerState = false;
	}
	/// <summary>
	/// Constructor to set power state
	/// </summary>
	/// <param name="state">Powerstate as a bool</param>
	Payload(bool state) : powerState(state) {};
	/// <summary>
	/// Get the current powerState
	/// </summary>
	/// <returns>power state as a bool</returns>
	bool GetPowerState()
	{
		return powerState;
	}

	/// <summary>
	/// Set power state
	/// </summary>
	/// <param name="state">Powerstate as a bool</param>

	void SetPowerState(bool state)	{
        powerState = state;
	}
};