#pragma once
#include "Status.h"

class PhotoStatus : public Status
{
public:
	PhotoStatus(Date statusDate, Time statusTime, std::string status, Friend* author);
	void printColorAndProgram();
	virtual ~PhotoStatus();
};