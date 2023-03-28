using namespace std;
#include "Time.h"
#define NUM_MINUTES 59
#define NUM_HOURS 24
#define ZERO 0

Time::Time(int hour_, int min_) 
{
	isTimeValid(hour_, min_);
	hour = hour_;
	minutes = min_;
}

void Time::isTimeValid(int hour_, int minutes_) noexcept(false)
{
	if (!((hour_ >= ZERO) && (hour_ <= NUM_HOURS) && (minutes_ >= ZERO) && (minutes_ <= NUM_MINUTES)))
		throw "Time is not valid.";
}

void Time::printTime() const
{
	cout << hour << ":" << minutes;
}
int Time::getHour()
{
	return hour;
}
int Time::getMin()
{
	return minutes;
}

