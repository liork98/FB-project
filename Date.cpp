#pragma once
#include "Date.h"
using namespace std;

#define EARLIEST_YEAR 1900
#define CURRENT_YEAR 2022

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
	if (!(day_ <= 31) || !(day_ >= 1) || !(month_>=1) || !(month_ <= 12) || !(year_ >= EARLIEST_YEAR) || !(year_ <= CURRENT_YEAR))
		throw "Date is not valid.";
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

