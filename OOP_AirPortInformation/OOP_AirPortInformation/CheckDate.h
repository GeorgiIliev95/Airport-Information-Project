#pragma once
#ifndef CHECKDATE_H_
#define CHECKDATE_H_
#include <string>
using namespace std;
 bool CheckDate(string time)
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

#endif