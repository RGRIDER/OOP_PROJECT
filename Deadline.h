#pragma once
#include <iostream>
#include <string>
using namespace std;
class Deadline
{
	int day;
	int month;
	int year;

public:
	Deadline(int x, int y, int z) :day(x), month(y), year(z) {};
	bool is_PastDeadLine(string deadline)
	{
		int day;
		int month;
		int year;

		day = (deadline[0] - '0') * 10 + (deadline[1] - '0');
		month = (deadline[3] - '0') * 10 + (deadline[4] - '0');
		year = (deadline[6] - '0') * 1000 + (deadline[7] - '0')*100 + (deadline[8] - '0') * 10 + (deadline[9] - '0');
	}

};




/////////////////////////////////

