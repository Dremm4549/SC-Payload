#pragma once

/**
 * @brief Class to handle the power state of a payload.
 *
 * This class provides functionality to manage and query the power state of a payload.
 * It allows setting and getting the power state represented as a boolean value.
 */
class Payload
{
private:
	bool powerState;


public:
	/**
	 * @brief Default constructor for the Payload class.
	 *
	 * Initializes the power state to false (off).
	 */
	Payload();
	/**
	 * @brief Construct a new Payload object with a specified power state.
	 *
	 * @param state Initial power state to set (true for on, false for off).
	 */
	Payload(bool state);
	/**
	 * @brief Get the current power state of the payload.
	 *
	 * @return bool Current power state (true for on, false for off).
	 */
	bool GetPowerState();
	/**
	 * @brief Set the power state of the payload.
	 *
	 * @param state Power state to set (true for on, false for off).
	 *              An invalid state prints an error message.
	 */
	void SetPowerState(bool state);
};