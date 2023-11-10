#pragma once

/**
 * @brief Class for handling and managing telemetry data.
 *
 * This class is responsible for storing and providing access to telemetry data,
 * including longitude, latitude, and temperature. It offers methods to set and get
 * these values individually or collectively.
 */
class Telem
{
private:
	float Long; ///< Longitude value.
	float Lat; ///< Latitude value.
	float Temp; ///< Temperature value.

public:
	/**
	 * @brief Default constructor for the Telem class.
	 *
	 * Initializes longitude, latitude, and temperature to zero.
	 */
	Telem()
	{
		Long = 0;
		Lat = 0;
		Temp = 0;
	}
	/**
	 * @brief Construct a new Telem object with specified values.
	 *
	 * @param Long Longitude value as a float.
	 * @param Lat Latitude value as a float.
	 * @param Temp Temperature value as a float.
	 */
	Telem(float Long, float Lat, float Temp) : Long(Long), Lat(Lat), Temp(Temp) {};
	/**
	 * @brief Get the longitude value.
	 *
	 * @return float Current longitude value.
	 */
	float getLong()
	{
		return Long;
	}
	/**
	 * @brief Get the latitude value.
	 *
	 * @return float Current latitude value.
	 */
	float getLat()
	{
		return Lat;
	}
	/**
	 * @brief Get the temperature value.
	 *
	 * @return float Current temperature value.
	 */
	float getTemp()
	{
		return Temp;
	}
	/**
	 * @brief Set all telemetry values at once.
	 *
	 * @param Lo Longitude value as a float.
	 * @param La Latitude value as a float.
	 * @param T Temperature value as a float.
	 */
	void setTelem(float Lo, float La, float T)
	{
		Long = Lo;
		Lat = La;
		Temp = T;
	}
};