#pragma once
#ifndef _STATUS_H
#define _STATUS_H
#define _CRT_SECURE_NO_WARNINGS
#include "Date.h"
#include <string>
#include "Time.h"
#include "Friend.h"

class Friend;

class Status
{
private:
	Date date;
	Time time;
	Friend* author = nullptr;

protected:
	std::string textData;

public:
	Friend* getAuthor();
	enum class mediaType { Text, Picture, Video };
	Status(Date date,  Time time, const std::string& textData, Friend* author);
	const void getStatus();
	Date getStatusDate();
	void setStatus(const std::string& status);
	virtual void printColorAndProgram()=0;
	bool operator==(Status* statusToCompare);
	bool operator!=(Status* statusToCompare);
	std::string getStatusData();
	Time getStatusTime();
	virtual ~Status();
	void PrintStatus();
	
};

#endif // !_STATUS_H
