#include "Telem.h"
#include <sstream>

Telem::Telem()
{
	Long = 0;
	Lat = 0;
	time = std::time(nullptr);
}

Telem::Telem(float Long, float Lat, std::time_t Time) : Long(Long), Lat(Lat), time(Time) 
{

}

float Telem::getLong()
{
	return Long;
}

float Telem::getLat()
{
	return Lat;
}

std::time_t Telem::getTime()
{
	return time;
}

void Telem::setLong(float Lo){
	Long = Lo;
}

void Telem::setLat(float La){
	Lat = La;
}

void Telem::setTime(std::time_t T){
	time = T;
}

void Telem::setTelem(float Lo, float La, std::time_t T)
{
	Long = Lo;
	Lat = La;
	time = T;
}

bool Telem::isValid()
{
	if (Long < -180 || Long > 180)
	{
		return false;
	}
	if (Lat < -90 || Lat > 90)
	{
		return false;
	}
	auto validTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	if (time > validTime)
	{
		return false;
	}
	return true;
}

std::string Telem::errorResponse(const string& errorCode, const string& errorMsg)
{
	std::stringstream err;
	err << "Error: " << errorCode << ", Message: " << errorMsg;
	return err.str();
}

void Telem::updateTelem(float newLong, float newLat, std::time_t newTime)
{
	Long = newLong;
	Lat = newLat;
	time = newTime;
}