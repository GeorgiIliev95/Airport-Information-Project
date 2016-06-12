#include "FlightInfo.h"

//implement funcion
#define FormatException -1

bool CheckDate(string time)
{
	if ((time.substr(0, 4).size() == 4) &&							// Check YYYY
		(time.substr(5, 2) > "00"&&time.substr(5, 2) < "13") &&		//Check MM
		(time.substr(8, 2) > "00"&&time.substr(8, 2) <= "31") &&	//Check DD 
		(time.substr(11, 2) > "0"&&time.substr(11, 2) <= "24") &&	//Check HH
		(time.substr(14, 2) >= "00"&&time.substr(14, 2) <= "60") &&	//Check Minutes
		(time.size() == 16))
	{
		return true;
	}
	else
	{
		return false;
	}
}
istream &operator>>(istream &fromStream, FlightInfo &obj)
{
	fromStream >> obj.flightID >> obj.fliesFrom >> obj.fliesTo >> obj.timeAired >> obj.timeArrived >> obj.price;
	obj.SetTimeAired(obj.timeAired);
	obj.SetTimeArrived(obj.timeArrived);
	return fromStream;
}

FlightInfo::FlightInfo(string flightid, string fromPort, string toPort, string timeaired, string timearrived, int bgn)
{
	flightID = flightid;
	fliesFrom = fromPort;
	fliesTo = toPort;
	if (CheckDate(timeaired))
	
	{
		timeAired = timeaired;
	}
	else
	{
		throw FormatException;
	}
	if (CheckDate(timearrived))
	{
		timeArrived = timearrived;
	}
	else
	{
		throw FormatException;
	}
	
	price = bgn;
}
void FlightInfo::SetFlightID(string id)
{
	flightID = id;
}
void FlightInfo::SetFliesTo(string flight)
{
	fliesTo = flight;
}
void FlightInfo::SetFliesFrom(string flight)
{
	fliesFrom = flight;
}
void FlightInfo::SetTimeAired(string time)
{
	if (CheckDate(time))
	{
		timeAired = time;
	}
	else
	{
		throw;
	}
}
void FlightInfo::SetTimeArrived(string &time)
{
	if (CheckDate(time))
	{
		timeArrived = time;
	}
	else
	{
		throw;
	}
}
void FlightInfo::SetPrice(int bgn)
{
	price = bgn;
}
string FlightInfo::GetFlightID()
{
	return flightID;
}
string FlightInfo::GetFliesTo()
{
	return fliesTo;
}
string FlightInfo::GetFliesFrom()
{
	return fliesFrom; 
}
string FlightInfo::GetTimeAired()
{
	return timeAired;
}
string FlightInfo::GetTimeArrived()
{
	return this->timeArrived;
}
int FlightInfo::GetPrice()
{
	return price;
}
ostream &operator<<(ostream &toStream, list<FlightInfo> &obj)
{
	list<FlightInfo>::iterator it;
	for (it = obj.begin(); it != obj.end(); it++)
	{
		toStream<<it->GetFlightID() << " " << it->GetFliesFrom() << " " << it->GetFliesTo() << " " << it->GetTimeAired() << " " << it->GetTimeArrived() << " " << it->GetPrice() << endl;
	}
	
	return toStream;
}