#pragma once
#ifndef FLIGHTINFO_H_
#define FLIGHTINFO_H_
//Define class
#include <string>
#include <fstream>
#include <list>
using namespace std;
//A class to define flight information
class FlightInfo
{
public:
	FlightInfo() { flightID = ""; fliesTo = ""; fliesFrom = ""; timeAired="YYYY/MM/DD HH:MM"; timeArrived = "YYYY/MM/DD HH:MM:SS"; price = 0.0; };
	FlightInfo(string flightid,string fromPort,string toPort,string timeaired,string timearrived,int bgn);
	~FlightInfo() {};
	void SetFlightID(string id);
	void SetFliesTo(string flight);
	void SetFliesFrom(string flight);
	void SetTimeAired(string time);
	void SetTimeArrived(string &time);
	void SetPrice(int bgn);
	string GetFlightID();
	string GetFliesTo();
	string GetFliesFrom();
	string GetTimeAired();
	string GetTimeArrived();
	int GetPrice();
	friend istream &operator>>(istream &fromStream, FlightInfo &obj);
	friend ostream &operator<<(ostream &toStream, list<FlightInfo> &obj);
private:
	string flightID;
	string fliesTo;
	string fliesFrom;
	string timeAired;
	string timeArrived;
	int price;
	
};


#endif