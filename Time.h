#pragma once
#ifndef _TIME_H
#define _TIME_H
#define _CRT_SECURE_NO_WARNINGS
#include "Time.h"
#include <string.h>
#include <iostream>
#define MAX_LEN_STATUS 100


class Time {
	int hour;
	int minutes;

public:
	Time(int hour_ = 0, int minutes_ = 0) ;
	void isTimeValid(int hour_, int minutes_) noexcept(false);
	void printTime() const;
	int getHour();
	int getMin();
};

#endif // !_TIME_H

