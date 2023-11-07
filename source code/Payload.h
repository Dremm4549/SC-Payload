#pragma once

/// <summary>
/// this class will handle the power state and be responsible for holding the image data
/// </summary>
class Payload
{
private:
	bool powerState;


public:
	/// <summary>
	/// Default constructor for the payload object
	/// </summary>
	Payload();
	/// <summary>
	/// Constructor to set power state
	/// </summary>
	/// <param name="state">Powerstate as a bool</param>
	Payload(bool state);
	/// <summary>
	/// Get the current powerState
	/// </summary>
	/// <returns>power state as a bool</returns>
	bool GetPowerState();

	/// <summary>
	/// Set power state
	/// </summary>
	/// <param name="state">Powerstate as a bool</param>

	void SetPowerState(bool state);
};