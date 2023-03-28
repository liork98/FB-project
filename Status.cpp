using namespace std;
#include "Status.h"

Status::Status(Date date, Time time, const string& textData)
{
	setStatus(textData);
	this->date = date;
	this->time = time;
}

void Status::setStatus(const string& status)
{
	textData = status;
}

const void Status::getStatus()
{
	printColorAndProgram();
	//return textData;
}

Date Status::getStatusDate()
{
	return date;
}
Time Status::getStatusTime()
{
	return time;
}
string Status::getStatusData() 
{
	return textData;
}

bool Status::operator==(Status* statusToCompare) 
{
	if (statusToCompare->textData == this->textData)
	{
		return true;
	}
	return false;
}

bool Status::operator!=(Status* statusToCompare)
{
	if (statusToCompare->textData != this->textData)
	{
		return true;
	}
	return false;
}

Status::~Status()
{

}