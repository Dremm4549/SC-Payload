#include "Telem.h"
Telem::Telem()
{
	Long = 0;
	Lat = 0;
	time = std::time(nullptr);
}

Telem::Telem(float Long, float Lat, std::string Time) : Long(Long), Lat(Lat), time(Time) 
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

std::string Telem::getTime()
{
	return time;
}

void Telem::setLong(float Lo){
	Long = Lo;
}

void Telem::setLat(float La){
	Lat = La;
}

void Telem::setTime(std::string T){
	time = T;
}

void Telem::setTelem(float Lo, float La, std::string T)
{
	Long = Lo;
	Lat = La;
	time = T;
}