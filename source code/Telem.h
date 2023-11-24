#pragma once
#include <iostream>
#include <ctime>
#include <iomanip>
#include <chrono>
/**
 * @brief Class for handling and managing telemetry data.
 *
 * This class is responsible for storing and providing access to telemetry data,
 * including longitude, latitude, and time. It offers methods to set and get
 * these values individually or collectively.
 */
class Telem
{
private:
	float Long; ///< Longitude value.
	float Lat; ///< Latitude value.
	std::string time; ///< Time value.

public:
	/**
	 * @brief Default constructor for the Telem class.
	 *
	 * Initializes longitude, latitude, and time to zero.
	 */
	Telem();
	/**
	 * @brief Constructor for the Telem class.
	 *
	 * Initializes longitude, latitude to set values and time to zero.
	 */
	Telem(float Long, float Lat);
	/**
	 * @brief Construct a new Telem object with specified values.
	 *
	 * @param Long Longitude value as a float.
	 * @param Lat Latitude value as a float.
	 * @param Time Time value as a string.
	 */
	Telem(float Long, float Lat, std::string Time);
	/**
	 * @brief Get the longitude value.
	 *
	 * @return float Current longitude value.
	 */
	float getLong();
	/**
	 * @brief Get the latitude value.
	 *
	 * @return float Current latitude value.
	 */
	float getLat();
	/**
	 * @brief Get the time value.
	 *
	 * @return string Current time value.
	 */
	std::string getTime();
	/**
	 * @brief Set all telemetry values at once.
	 *
	 * @param Lo Longitude value as a float.
	 * @param La Latitude value as a float.
	 * @param T Time value as a string.
	 */
	void setTelem(float Lo, float La, std::string T);
	/**
	 * @brief Set Long value.
	 *
	 * @param Lo Longitude value as a float.
	 */
	void setLong(float Lo);
	/**
	 * @brief Set Lat value.
	 *
	 * @param La Latitude value as a float.
	 */
	void setLat(float La);
	/**
	 * @brief Set time value.
	 *
	 * @param T Time value as a string.
	 */
	void setTime(std::string T);
};