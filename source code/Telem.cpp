#include "Telem.h"
Telem::Telem()
{
	Long = 0;
	Lat = 0;
	Temp = 0;
}

Telem::Telem(float Long, float Lat, float Temp) : Long(Long), Lat(Lat), Temp(Temp) 
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

float Telem::getTemp()
{
	return Temp;
}

void Telem::setTelem(float Lo, float La, float T)
{
	Long = Lo;
	Lat = La;
	Temp = T;
}