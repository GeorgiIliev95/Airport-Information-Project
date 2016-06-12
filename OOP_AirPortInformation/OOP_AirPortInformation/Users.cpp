#include "Users.h"

Users::Users(string fileName)
{
	ifstream file(fileName.data());
	if (file.good())
		copy(istream_iterator<UserRequest>(file), istream_iterator<UserRequest>(), back_inserter(users));
	else throw;
}
void Users::AddUserRequest(string requestId, string fromPort, string toPort, string timeaired, string timearrived)
{
	UserRequest request;
	request.SetRequesttID(requestId);
	request.SetFliesFrom(fromPort);
	request.SetFliesTo(toPort);
	request.SetTimeAired(timeaired);
	request.SetTimeArrived(timearrived);
	users.push_back(request);
}
void Users::MostRequestsToCity()
{
	string *stringOfCities;
	stringOfCities = new string[users.size()];
	list<UserRequest>::iterator it;
	int i = 0;
	for (it = users.begin(); it != users.end(); it++)
	{
		stringOfCities[i] = it->GetFliesTo();
		i++;
	}
	int counter = 1;
	int len = INT32_MIN;
	string mostCommon;
	for (i = 0; i<users.size() - 1; i++)
	{
		counter = 1;
		for (int j = i + 1; j < users.size(); j++)
		{
			if (stringOfCities[i] == stringOfCities[j])
			{
				counter++;
			}
		}
		if (len<counter)
		{
			len = counter;
			mostCommon = stringOfCities[i];
		}
	}
	cout << "\n\nMost Common City is " << mostCommon << " and occured " << len << " times." << endl << endl;
}
void Users::PrintData()
{
	cout << users;
}
void Users::CheapestFlightById(string id, list<FlightData> flights,AdjacencyMatrix &matrix,vector<string> cities)
{
	list<UserRequest>::iterator itUsers;
	list<FlightData>::iterator itFlights=flights.begin();
	FlightData flightData("Flights.txt");
	UserRequest specifiedUser;
	int price=0;
	for (itUsers = users.begin(); itUsers != users.end(); itUsers++)
	{
		if (itUsers->GetFlightID() == id)
		{
			specifiedUser = UserRequest(itUsers->GetFlightID(), itUsers->GetFliesFrom(), itUsers->GetFliesTo(), itUsers->GetTimeAired(), itUsers->GetTimeArrived());
		}

	}
	
	
	if (!(flightData.HasCity(specifiedUser.GetFliesFrom())&&flightData.HasCity(specifiedUser.GetFliesTo())))
	{
		cout << "\tThis User Request ( "<<specifiedUser.GetFliesFrom()<<" to "<<specifiedUser.GetFliesTo()<<" ) doesn't meet actual flights!" << endl<<endl<<endl;
		return;
	}
	if (flightData.FindFlight(specifiedUser.GetFliesFrom(),specifiedUser.GetFliesTo(),cities,matrix)>=0)
	{
		if (flightData.SatisfiesTime(specifiedUser.GetTimeAired(), specifiedUser.GetFliesFrom(), specifiedUser.GetTimeArrived(), specifiedUser.GetFliesTo(), matrix, cities))
		{
			price = flightData.FindFlightPrice(specifiedUser.GetFliesFrom(), specifiedUser.GetFliesTo(), cities, matrix);
			cout << "\n\n\tPrice between " << specifiedUser.GetFliesFrom() << " and " << specifiedUser.GetFliesTo() << " is:" << price << endl << endl << endl << endl << endl << endl;
		}
		else
		{
			cout << "\t\tYour flight request don't meet any current flights!" << endl<<endl<<endl;
		}
	}
	else
	{
		cout << "\t\tThis User Request doesn't meet actual flights!" << endl;
	}
}
ostream &operator<<(ostream &toStream, list<Users> &obj)
{
	list<Users>::iterator it;
	for (it = obj.begin(); it != obj.end(); it++)
	{
		toStream << it->users;
	}

	//toStream << obj.flights;
	return toStream;
}
bool  Users::HasID(string id)
{
	for each (auto var in users)
	{
		if (id==var.GetFlightID())
		{
			return true;
		}
	}
	return false;
}
void Users::CheapestFlightForAllReq(list<FlightData> flights,AdjacencyMatrix &matrix,vector<string> cities)
{
	clock_t begin = clock();
	list<FlightData>::iterator itFlights;
	list<UserRequest>::iterator itUsers;
	FlightData flightData("Flights.txt");

	for (itUsers = users.begin(); itUsers != users.end();itUsers++)
	{
		cout << "For User Request:\n\t"<<itUsers->GetFlightID()<<" from "<< itUsers->GetFliesFrom()<<" to "<<itUsers->GetFliesTo()<<" sets off "<<itUsers->GetTimeAired()<<" lands "<<itUsers->GetTimeArrived();
		CheapestFlightById(itUsers->GetFlightID(), flights,matrix,cities);
		
	}
	clock_t end = clock();
	double elapsedtime = double(end - begin) / CLOCKS_PER_SEC;
	cout << elapsedtime;

	
	
}

