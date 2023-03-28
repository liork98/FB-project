#pragma once
#ifndef _DATE_H
#define _DATE_H
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <iostream>



class Date
{
private:
	int day;
	int month;
	int year;
	
public:
	void printDate() const;
	Date()=default;
	Date(int day_, int month1_, int year_); // c'tor
	void isDateValid(int day_, int month_, int year_) noexcept(false);
	int getDay();
	int getMonth();
	int getYear();

};
#endif // !_DATE_H#pragma once
