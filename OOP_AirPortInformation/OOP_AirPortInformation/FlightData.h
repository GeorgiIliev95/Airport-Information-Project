#pragma once
#ifndef FLIGHTDATA_H_
#define FLIGHTDATA_H_
#include <list>
#include <string>
#include "FlightInfo.h"
#include <iterator>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <map>

#include "AdjacencyMatrix.h"
using namespace std;
class FlightData
{
public:
	FlightData() {};
	~FlightData() {};
	FlightData(string fileName) ;//
	list<FlightInfo> GetFlightsFrom(string fromPort);//
	list<FlightInfo> GetFlightsTo(string toPort);//
	list <FlightInfo> GetFlights();//
	int HasFlight(int fromPort, int toPort, vector<string> nodes);//
	int FindFlight(string fromPort, string toPort, vector<string> &cities, AdjacencyMatrix &matrix);//
	int FindFlightPrice(string fromPort, string toPort, vector<string> &cities, AdjacencyMatrix& matrix);//
	void AddFlight(string flightid, string fromPort, string toPort, string timeaired, string timearrived, int bgn);//
	void AddFlight(FlightInfo &obj);//
	void PrintData();//
	bool HasCity(string city);//
	bool HasID(string id);//
	bool SatisfiesTime(string timeTakeoff, string fromPort, string timeLands, string toPort,AdjacencyMatrix &matrix,vector<string> &cities);//
	void CorrectDataByID(string id);//
	void MostFlightsFromCity();//
	void TakeOffFlightAfterTime(string time,string fromPort);//
	friend ostream &operator<<(ostream &toStream, list<FlightData> &obj);//
	
private:
	list <FlightInfo> flights;
};



#endif
