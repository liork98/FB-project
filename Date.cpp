#pragma once
#include "Date.h"
using namespace std;
#define DEC 12
#define JAN 1
#define FEB 2
#define JUN 6
#define APR 4
#define SEP 9
#define NOV 11
#define EARLIEST_YEAR 1900
#define CURR_YEAR 2022

Date::Date(int day1, int month1, int year1) 
{
	isDateValid(day1, month1, year1);
	day = day1;
	month = month1;
	year = year1;
}

void Date::printDate() const
{
	cout << day << "/" << month << "/" << year << " " << endl;
}

void Date::isDateValid(int day_, int month_, int year_) noexcept(false)
{
	bool res = true;
	if (month_ < JAN || month_ > DEC)
	{
		throw "Month is not valid.";
	}
	else 
	{
		if (day_ >= 1 && day_ <= 31)
		{
			if ((month_ == FEB && day_ > 28) || (((month_ == APR) || (month_ == JUN) || (month_ == SEP) || (month_ == NOV)) && (day_ == 31)) || (year_ < EARLIEST_YEAR || year > CURR_YEAR))
				throw "Day is not valid.";
		}
	}
}

int Date::getDay()
{
	return day;
}
int Date::getMonth()
{
	return month;
}
int Date::getYear()
{
	return year;
}

