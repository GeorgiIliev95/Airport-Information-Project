#pragma once
#ifndef USERS_H_
#define USERS_H_
#include <list>
#include "UserRequest.h"
#include <fstream>
#include <iterator>
#include <string>
#include <iostream>
#include "FlightData.h"
#include "AdjacencyMatrix.h"
#include <ctime>
class Users
{
public:
	Users() {};
	~Users() {};
	Users(string fileName);
	void AddUserRequest(string flightid, string fromPort, string toPort, string timeaired, string timearrived);
	void MostRequestsToCity();
	void PrintData();
	void CheapestFlightById(string id, list<FlightData> flights,AdjacencyMatrix &matrix,vector<string> cities);
	void CheapestFlightForAllReq( list<FlightData> flights,AdjacencyMatrix &matrix,vector<string> cities);
	bool HasID(string id);
	friend ostream &operator<<(ostream &toStream, list<Users> &obj);
private:
	list<UserRequest> users;
};


#endif
