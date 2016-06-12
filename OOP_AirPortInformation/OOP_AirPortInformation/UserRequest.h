#pragma once
#ifndef USERREQUEST_H_
#define USERREQUEST_H_
#include <string>
#include <fstream>
#include <list>
#include <iterator>
using namespace std;
class UserRequest
{
public:
	UserRequest() {};
	~UserRequest() {};
	UserRequest(string id,string fromPort,string toPort,string timeaired,string timearrived);
	void SetRequesttID(string id);
	void SetFliesTo(string flight);
	void SetFliesFrom(string flight);
	void SetTimeAired(string time);
	void SetTimeArrived(string &time);
	string GetFlightID();
	string GetFliesTo();
	string GetFliesFrom();
	string GetTimeAired();
	string GetTimeArrived();
	friend istream &operator>>(istream &fromStream,UserRequest &obj);
	friend ostream &operator<<(ostream &toStream, list<UserRequest> &obj);
private:
	string requestID;
	string fliesFrom;
	string fliesTo;
	string timeAired;
	string timeArrived;
};


#endif