#include "Telem.h"
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