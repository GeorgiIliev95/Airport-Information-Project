#include "FlightData.h"


FlightData::FlightData(string fileName)
{
	ifstream file(fileName.data());
	if (file.good())
		copy(istream_iterator<FlightInfo>(file), istream_iterator<FlightInfo>(), back_inserter(flights));
	else throw ;
}
void FlightData::PrintData()
{
	list<FlightInfo>::iterator it;
	for (it = flights.begin(); it != flights.end();it++)
	{
		cout << it->GetFlightID() << " "
			<< it->GetFliesFrom() << " "
			<< it->GetFliesTo() << " "
			<< it->GetTimeAired() << " "
			<< it->GetTimeArrived() << " "
			<< it->GetPrice() << endl;
	}
}

list<FlightInfo> FlightData::GetFlightsFrom(string fromPort)
{
	list<FlightInfo> flightsFromPort;	
	for each (auto var in flights)
	{
		if (var.GetFliesFrom()==fromPort)
		{
			FlightInfo st(var.GetFlightID(),var.GetFliesFrom(),var.GetFliesTo(),var.GetTimeAired(),var.GetTimeArrived(),var.GetPrice());
			flightsFromPort.push_back(st);
		}
	}
	return flightsFromPort;
}
list<FlightInfo>  FlightData::GetFlightsTo(string toPort)
{
	list<FlightInfo> flightsToPort;
	list<FlightInfo>::iterator it;
	for (it = flights.begin(); it != flights.end(); it++)
	{
		if (it->GetFliesTo() == toPort)
		{
			FlightInfo st(it->GetFlightID(), it->GetFliesFrom(), it->GetFliesTo(), it->GetTimeAired(), it->GetTimeArrived(), it->GetPrice());
			flightsToPort.push_back(st);
		}
	}
	return flightsToPort;
}
void  FlightData::AddFlight(string flightid, string fromPort, string toPort, string timeaired, string timearrived, int bgn)
{

	FlightInfo info;
	info.SetFlightID(flightid);
	info.SetFliesFrom(fromPort);
	info.SetFliesTo(toPort);
	info.SetTimeAired(timeaired);
	info.SetTimeArrived(timearrived);
	info.SetPrice(bgn);
	flights.push_back(info);
	
	
}
void FlightData::CorrectDataByID(string id)
{
	list<FlightInfo>::iterator it;
	for (it=flights.begin(); it!=flights.end(); it++)
	{
		if (id==it->GetFlightID())
		{
			string inputInfo;
			int currency;

			cout << "\nEnter taking off city: ";
			cin >> inputInfo;
			it->SetFliesFrom(inputInfo);

			cout << "\nEnter arrival city: ";
			cin >> inputInfo;
			it->SetFliesTo(inputInfo);

			cout << "\nEnter aired date and time {ONLY IN FORMAT YYYY/MM/DD-HH:MM}: ";
			cin >> inputInfo;
			it->SetTimeAired(inputInfo);
			cout << "\nEnter arrival date and time {ONLY IN FORMAT YYYY/MM/DD-HH:MM}: ";
			cin >> inputInfo;
			it->SetTimeArrived(inputInfo);

			cout << "\nEnter price of the flight: ";
			cin >> currency;
			it->SetPrice(currency);
		}
	}
}

void FlightData::MostFlightsFromCity()
{
	string *stringOfCities;
	stringOfCities = new string[flights.size()];
	list<FlightInfo>::iterator it;
	int i = 0;
	for (it = flights.begin(); it != flights.end(); it++)
	{
		stringOfCities[i] = it->GetFliesFrom();
		i++;
	}
	int counter = 1;
	int len = INT32_MIN;
	string mostCommon;
	for (i=0;i<flights.size()-1;i++)
	{
		counter = 1;
		for (int j = i+1; j < flights.size(); j++)
		{
			if (stringOfCities[i]==stringOfCities[j])
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
	cout << "\n\nMost Common City is " << mostCommon << " and occured " << len << " times." << endl<<endl;
}
void FlightData::TakeOffFlightAfterTime(string time,string fromPort)
{
	list<FlightInfo>::iterator it;
	bool flag = false;
	for (it = flights.begin(); it != flights.end();it++)
	{
		if (it->GetTimeAired()>time && it->GetFliesFrom()==fromPort)
		{
			flag = true;
			cout << it->GetFlightID() << " "
				<< it->GetFliesFrom() << " "
				<< it->GetFliesTo() << " "
				<< it->GetTimeAired() << " "
				<< it->GetTimeArrived() << " "
				<< it->GetPrice() << endl;
		}
		
	}
	if (!flag)
	{
		cout << "\n\t\tNo flights found" << endl;
	}
}
ostream &operator<<(ostream &toStream, list<FlightData> &obj)
{
	list<FlightData>::iterator it;
	for (it = obj.begin(); it!=obj.end(); it++)
	{
		toStream << it->flights;
	}
	
	//toStream << obj.flights;
	return toStream;
}


int FlightData::FindFlight(string fromPort, string toPort,vector<string> &cities,AdjacencyMatrix& matrix)
{
	
	
	int from;
	int to;
	for (int i = 0; i < cities.size(); i++)
	{

		if (cities[i] == fromPort)
		{
			from = i;
		}
		if (cities[i] == toPort)
		{
			to = i;
		}

	}
	if (matrix.HasEdge(from, to))
	{
		return 0;
	}
	cout << endl << endl;
	
	int n= matrix.DepthFirstSearch(from,to,cities.size());
	
	
	return n;
}

int FlightData::FindFlightPrice(string fromPort, string toPort, vector<string> &cities, AdjacencyMatrix &matrix)
{
	
	
	int from;
	int to;
	for (int i = 0; i < cities.size(); i++)
	{

		if (cities[i] == fromPort)
		{
			from = i;
		}
		if (cities[i] == toPort)
		{
			to = i;
		}

	}

	
	return matrix.Dijkstra(from, to,cities);
}
int FlightData::HasFlight(int fromPort, int toPort,vector<string> nodes)
{
	for each (auto var in flights)
	{
		if ((nodes[fromPort]==var.GetFliesFrom() && nodes[toPort]==var.GetFliesTo())||(nodes[fromPort]==var.GetFliesTo() && nodes[toPort]==var.GetFliesFrom()))
		{
			return var.GetPrice();
		}
	}
	return -1;
}
void FlightData::AddFlight(FlightInfo &obj)
{
	flights.push_back(obj);
}
bool FlightData::HasCity(string city)
{
	for each (auto var in flights)
	{
		if (city==var.GetFliesFrom()||city==var.GetFliesTo())
		{
			return true;
		}
	}
	return false;
}
bool FlightData::HasID(string id)
{
	for each (auto var in flights)
	{
		if (id == var.GetFlightID() )
		{
			return true;
		}
	}
	return false;
}
bool FlightData::SatisfiesTime(string timeTakeoff,string fromPort,string timeLands,string toPort, AdjacencyMatrix &matrix, vector<string> &cities)
{
	list<FlightInfo>::iterator itFlight;
	bool flag=false;
	vector<int> path;
	int from;
	int to;
	for (int i = 0; i < cities.size(); i++)
	{

		if (cities[i] == fromPort)
		{
			from = i;
		}
		if (cities[i] == toPort)
		{
			to = i;
		}

	}
	path=matrix.ShortestPath(from, to, cities);
	int idx=0;
	cout << "\tAvailable flights: " << endl;
	for (itFlight = flights.begin(); itFlight != flights.end();itFlight++)
	{

	
		if (idx < path.size() - 1)
		{

			
			if ((itFlight->GetFliesFrom() == cities[path[idx]] && itFlight->GetFliesTo() == cities[path[idx + 1]]))
			{
				//cout << "MATCH";
				if (timeTakeoff<=itFlight->GetTimeAired() && itFlight->GetTimeArrived()<=timeLands)
				{
					cout << "\t\t"<< itFlight->GetFliesFrom() << " to " << itFlight->GetFliesTo() << " takes off " << itFlight->GetTimeAired() << " arrives at " << itFlight->GetTimeArrived() << " price: " << itFlight->GetPrice()<<endl;
					flag = true;
					itFlight = flights.begin();
					idx++;
				}
				else
				{
					flag = false;
				}
				
			}
		}
	}
	
	
	return flag;
}
list<FlightInfo> FlightData::GetFlights()
{
	return flights;
}