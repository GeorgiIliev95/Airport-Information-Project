#include "UserRequest.h"

bool DateCheck(string time)
{
	if ((time.substr(0, 4).size() == 4) &&							// Check YYYY
		(time.substr(5, 2) > "00"&&time.substr(5, 2) < "13") &&		//Check MM
		(time.substr(8, 2) > "00"&&time.substr(8, 2) <= "31") &&	//Check DD 
		(time.substr(11, 2) > "0"&&time.substr(11, 2) <= "24") &&	//Check HH
		(time.substr(14, 2) >= "00"&&time.substr(14, 2) < "60") &&	//Check Minutes
		(time.size() == 16))
	{
		return true;
	}
	else
	{
		return false;
	}
}
UserRequest::UserRequest(string id, string fromPort, string toPort, string timeaired, string timearrived)
{
	requestID = id;
	fliesFrom = fromPort;
	fliesTo = toPort;
	timeAired = timeaired;
	timeArrived = timearrived;
}

void UserRequest::SetRequesttID(string id) { requestID = id; }
void UserRequest::SetFliesTo(string flight) { fliesFrom = flight; }
void UserRequest::SetFliesFrom(string flight) { fliesTo = flight; }
void UserRequest::SetTimeAired(string time) 
{ 
	if (DateCheck(time))
	{
		timeAired = time;
	}
	else
	{
		throw;
	}
}
void UserRequest::SetTimeArrived(string &time){
	if (DateCheck(time))
	{
		timeArrived = time;
	}
	else
	{
		throw;
	}
}
string UserRequest::GetFlightID() { return requestID; }
string UserRequest::GetFliesTo() { return fliesTo; }
string UserRequest::GetFliesFrom() { return fliesFrom; }
string UserRequest::GetTimeAired() { return timeAired; }
string UserRequest::GetTimeArrived() { return timeArrived; }
istream &operator>>(istream &fromStream, UserRequest &obj) 
{
	fromStream >> obj.requestID >> obj.fliesFrom >> obj.fliesTo >> obj.timeAired >> obj.timeArrived;
	obj.SetTimeAired(obj.timeAired);
	obj.SetTimeArrived(obj.timeArrived);
	return fromStream;
}
ostream &operator<<(ostream &toStream, list<UserRequest> &obj)
{
	list<UserRequest>::iterator it;
	for (it = obj.begin(); it != obj.end(); it++)
	{
		toStream << it->GetFlightID() << " " << it->GetFliesFrom() << " " << it->GetFliesTo() << " " << it->GetTimeAired() << " " << it->GetTimeArrived() << endl;
	}

	return toStream;
}