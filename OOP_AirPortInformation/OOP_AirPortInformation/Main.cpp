#include <iostream>
#include <fstream>
#include <time.h>
#include "AdjacencyMatrix.h"
#include "FlightInfo.h"
#include "FlightData.h"
#include "UserRequest.h"
#include "Users.h"
#include <map>
#include <vector>
#include <set>
using namespace std; 
bool CheckDateTime(string time)
{
	int size = time.size();
	if (size == 16)
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
	else if (size==4)
	{
		if ((time.substr(0, 4).size() == 4) && (time.substr(0, 4)>="1999"&& time.substr(0, 4)<="2020"))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (size < 8)
	{
		if ((time.substr(0, 4).size() == 4) && (time.substr(0, 4) >= "1999"&& time.substr(0, 4) <= "2020")&& (time.substr(5, 2) > "00"&&time.substr(5, 2) < "13"))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (size>=8 && size <12)
	{
		if ((time.substr(0, 4).size() == 4) && 
			(time.substr(0, 4) >= "1999"&& time.substr(0, 4) <= "2020") && 
			(time.substr(5, 2) > "00"&&time.substr(5, 2) < "13")&& 
			(time.substr(8, 2) > "00"&&time.substr(8, 2) <= "31"))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return true;
}
void Menu();
void SubMenu(list<FlightData>::iterator itFlight, list<FlightData> flights,vector<string> &cities,AdjacencyMatrix &matrix);

int main()
{
	
	Menu();

	
}

void Menu()
{

	int choice = 0;
	list<FlightData> flights;
	list<Users> users;
	flights.push_back(FlightData("Flights.txt"));
	users.push_back(Users("Users.txt"));
	list<FlightData>::iterator itFlight=flights.begin();
	list<Users>::iterator itUser = users.begin();
	vector<string> cities;
	list<FlightInfo> flightInfo=itFlight->GetFlights();
	list<FlightInfo>::iterator it;
	for (it = flightInfo.begin(); it != flightInfo.end();it++ )
	{

		cities.push_back(it->GetFliesFrom());
		cities.push_back(it->GetFliesTo());
	}

	sort(cities.begin(), cities.end());
	cities.erase(unique(cities.begin(), cities.end()), cities.end());
	//leaving only our unique nodes



	AdjacencyMatrix matrix = AdjacencyMatrix(cities.size());


	cout << endl;

	for (int i = 0; i < cities.size(); i++)
	{
		for (int j = 0; j < cities.size(); j++)
		{
			if (itFlight->HasFlight(i, j, cities)>0)
			{
				matrix.AddEdge(i, j,itFlight->HasFlight(i, j, cities));
			}
		}
	}
	do
	{
		cout << "\n\n*		MENU		*" << endl;
		cout << "1.Add new Flight." << endl;
		cout << "2.Add new User Request." << endl;
		cout << "3.Change data by ID." << endl;
		cout << "4.Print information about all flights." << endl;
		cout << "5.Print information about all user request." << endl;
		cout << "6.Find and print information about flights from city after specified time." << endl;
		cout << "7.Find from which city has most flights." << endl;
		cout << "8.Find to which city there are most requested flights." << endl;
		cout << "9.Display cheapest flight via user's request ID." << endl;
		cout << "10.Display cheapest flights for all user requests." << endl;
		cout << "11.Enter Submenu of class FlightData" << endl;
		cout << "12.Save updated data in file." << endl;
	
		cout << "\n Your choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			cout << "\n**********" << endl;
			cout << "Enter Flight ID:";
			string info;
			cin >> info;
			cout << "\nEnter taking off city:";
			string fromTown;
			cin >> fromTown;
			cout << "\nEnter arrival city:";
			string toTown;
			cin >> toTown;
			cout << "\nEnter aired date and time {ONLY IN FORMAT YYYY/MM/DD-HH:MM}:";
			string timeAired;
			cin >> timeAired;
			cout << "\nEnter arrival date and time {ONLY IN FORMAT YYYY/MM/DD-HH:MM}:";
			string timeArrived;
			cin >> timeArrived;
			cout << "\nEnter price of the flight:";
			int price;
			cin >> price;
			itFlight = flights.begin();
			itFlight->AddFlight(info,fromTown,toTown,timeAired,timeArrived,price);
			
			
		}
			//flights.push_back("","","","","",5);
			break;
		case 2: 
		{
			cout << "\n**********" << endl;
			cout << "Enter User Request ID: ";
			string info;
			cin >> info;
			cout << "\nEnter taking off city: ";
			string fromTown;
			cin >> fromTown;
			cout << "\nEnter arrival city: ";
			string toTown;
			cin >> toTown;
			cout << "\nEnter aired date and time {ONLY IN FORMAT YYYY/MM/DD-HH:MM}: ";
			string timeAired;
			cin >> timeAired;
			cout << "\nEnter arrival date and time {ONLY IN FORMAT YYYY/MM/DD-HH:MM}: ";
			string timeArrived;
			cin >> timeArrived;
			
			itUser =users.begin();
			itUser->AddUserRequest(info, fromTown, toTown, timeAired, timeArrived);
		}
			break;
		case 3:
		{
			itFlight = flights.begin();
			string id;
			cout << "\nEnter ID of a flight: ";
			cin >> id;
			if (!itFlight->HasID(id))
			{
				cout << "No such flight id was found!" << endl << endl;
				break;
			}
			itFlight->CorrectDataByID(id);
		}
			break;
		case 4:
		{
			for (itFlight = flights.begin(); itFlight != flights.end(); itFlight++)
			{
				itFlight->PrintData();
			}
		}
			break;
		case 5:
		{
			for (itUser = users.begin(); itUser != users.end();itUser++)
			{
				itUser->PrintData();
			}
		}
			break;
		case 6:
		{
			itFlight = flights.begin();
			cout << "\n\nEnter city: ";
			string city;
			cin >> city;
			if (!itFlight->HasCity(city))
			{
				cout << "\n\t\tThere is no such city!"<<endl;
				break;
			}
			cout << "\nEnter aired date and time {ONLY IN FORMAT YYYY/MM/DD-HH:MM}: ";
			string time;
			cin >> time;
			if (!CheckDateTime(time))
			{
				cout << "\n\nIncorrect time!" << endl;
				break;
			}
			
			itFlight->TakeOffFlightAfterTime(time,city);
		}
			
			break;
		case 7:
		{
			itFlight = flights.begin();
			itFlight->MostFlightsFromCity();
		}
			break;
		case 8:
		{
			itUser = users.begin();
			itUser->MostRequestsToCity();
		}
			break;
		case 9: 
		{
			itUser = users.begin();
			cout << "\nEnter user ID:";
			string id;
			cin >> id;
			if (!itUser->HasID(id))
			{
				cout << "No such flight id was found!" << endl << endl;
				break;
			}
			itUser->CheapestFlightById(id, flights,matrix,cities);
			break;
		}
		case 10:
		{
			itUser = users.begin();
			itUser->CheapestFlightForAllReq(flights,matrix,cities);
			break;
		}
		case 11:
			SubMenu(itFlight,flights,cities,matrix);
			break;
		case 12:
		{
			
			ofstream fileWriter;
			fileWriter.open("Flights.txt");
			fileWriter << flights;
			fileWriter.close();

			fileWriter.open("Users.txt");
			fileWriter << users;
			fileWriter.close();
			for each (auto var in cities)
			{
				cout << var<<" ";
			}
			cout << endl;
			cout << "\n\n\n\tUploaded data saved!" << endl << endl << endl;

			

			break;
		}
		
			break;
		default:
			cout << "\n\n\tWrong input!\n\n" << endl;
			break;
		}

	} while (choice>0 && choice<13);
}

void SubMenu(list<FlightData>::iterator itFlight,list<FlightData> flights, vector<string> &cities, AdjacencyMatrix &matrix)
{

	int choice = 0;
	do
	{
		cout << "\n*		SUBMENU			*" << endl;
		cout << "1.Find all flights airing from a given port."<<endl;
		cout << "2.Find all flights traveling to a given port." << endl;
		cout << "3. Check if there is flight between two given cities." << endl;
		cout << "4. Print Graph." << endl;
		cout << "5.Go back to main menu." << endl;
		cout << "Enter your choice:";
		cin >> choice;

		switch (choice)
		{
		case 1:
			{
				itFlight = flights.begin();
				string port;
				cout << "Enter port:";
				cin >> port;
				if (!itFlight->HasCity(port))
				{
					cout << "City doesn't exist!" << endl << endl;
					break;
				}
				list<FlightInfo>listPtr= itFlight->GetFlightsFrom(port);
				cout << "Flights Info:"<<endl;
//				
				for each (auto var in listPtr)
				{
					cout<<var.GetFlightID() <<" "<< var.GetFliesFrom()<<" "<<var.GetFliesTo()<<" "<<var.GetTimeAired()<<" "<<var.GetTimeArrived()<<" "<<var.GetPrice()<<endl;
				}
			}
			break;
		case 2:
		{
			itFlight = flights.begin();
			string port;
			cout << "Enter port:";
			cin >> port;
			if (itFlight->HasCity(port))
			{


				list<FlightInfo>listPtr = itFlight->GetFlightsTo(port);
				cout << "Flights Info:" << endl;

				for each (auto var in listPtr)
				{
					cout << var.GetFlightID() << " " << var.GetFliesFrom() << " " << var.GetFliesTo() << " " << var.GetTimeAired() << " " << var.GetTimeArrived() << " " << var.GetPrice() << endl;
				}
			}
			else
			{
				cout << "City doesn't exist!" << endl << endl;
			}
		}
			break;
		case 3: {
			itFlight = flights.begin();
			cout << "\nEnter airing port:";
			string portOne = "";
			cin >> portOne;
			if (!itFlight->HasCity(portOne))
			{
				cout << "City doesn't exist!" << endl << endl;
				break;
			}
			cout << "\nEnter decending port:";
			string portTwo = "";
			cin >> portTwo;
			if (!itFlight->HasCity(portTwo))
			{
				cout << "City doesn't exist!" << endl << endl;
				break;
			}
			cout << endl << endl;
			int result=itFlight->FindFlight(portOne, portTwo,cities,matrix);
			itFlight = flights.begin();
			itFlight->FindFlightPrice(portOne, portTwo, cities, matrix);
			switch (result)
			{
			case 1:
			{
				cout << "\n\tThis flight is a stopover!" << endl<<endl<<endl;
				break;
			}
			case 0:
			{
				cout << "\n\tDirect flight!" << endl;
				break;
			}
			case -1: 
			{
				cout << "\n\tThis flight path doesn't exist!" << endl;
				break;
			}
			case -2: 
			{
				cout << "\n\tCannot fly to the same city!" << endl;
				break;
			}
			default:
				break;
			}
		
			break;
			
		}
		case 4:
			matrix.PrintGraph(cities.size(),cities);
			break;
		default:
		{ }
			break;
		}
	} while (choice>0&&choice<5);
}