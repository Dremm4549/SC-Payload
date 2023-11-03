#pragma once

/// <summary>
/// this class handles and changes or requests for data of the telemarty
/// </summary>
class Telem
{
private:
	float Long;
	float Lat;
	float Temp;

public:
	/// <summary>
	/// Default constructor for the telem object
	/// </summary>
	Telem()
	{
		Long = 0;
		Lat = 0;
		Temp = 0;
	}
	/// <summary>
	/// Constructor to set Telem object to values
	/// </summary>
	/// <param name="Long">Longitude as a float</param>
	/// <param name="Lat">Latitude as a float</param>
	/// <param name="Temp">Temperature as a float</param>
	Telem(float Long, float Lat, float Temp) : Long(Long), Lat(Lat), Temp(Temp) {};
	/// <summary>
	/// Get longitude value
	/// </summary>
	/// <returns>Longitude as a float</returns>
	float getLong()
	{
		return Long;
	}
	/// <summary>
	/// Get latitude value
	/// </summary>
	/// <returns>Latitude value as a float</returns>
	float getLat()
	{
		return Lat;
	}
	/// <summary>
	/// Get temperature value
	/// </summary>
	/// <returns>Temperature value as a float</returns>
	float getTemp()
	{
		return Temp;
	}
	/// <summary>
	/// Set all telemetry values
	/// </summary>
	/// <param name="Lo">Longitude as a float</param>
	/// <param name="La">Latitude as a float</param>
	/// <param name="T">Temperature as a float</param>
	void setTelem(float Lo, float La, float T)
	{
		Long = Lo;
		Lat = La;
		Temp = T;
	}
};