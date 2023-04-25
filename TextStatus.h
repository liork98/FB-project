#pragma once
#include "Status.h"
#include "Date.h"
#include "Time.h"
class Friend;

class TextStatus : public Status
{
public:
	TextStatus(Date statusDate, Time statusTime, std::string status, Friend* author);
	void printColorAndProgram();
	virtual ~TextStatus();

};