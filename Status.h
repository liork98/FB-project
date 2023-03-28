#pragma once
#ifndef _STATUS_H
#define _STATUS_H
#define _CRT_SECURE_NO_WARNINGS
#include "Date.h"
#include <string>
#include "Time.h"

class Status
{
private:
	Date date;
	Time time;
protected:
	std::string textData;
public:
	enum class mediaType { Text, Picture, Video };
	Status(Date date,  Time time, const std::string& textData);
	const void getStatus();
	Date getStatusDate();
	void setStatus(const std::string& status);
	virtual void printColorAndProgram()=0;
	bool operator==(Status* statusToCompare);
	bool operator!=(Status* statusToCompare);
	std::string getStatusData();
	Time getStatusTime();
	virtual ~Status();
	//virtual std::string getStatusData()= 0;
};

#endif // !_STATUS_H
