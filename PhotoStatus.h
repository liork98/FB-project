#pragma once
#include "Status.h"

class PhotoStatus : public Status
{
public:
	PhotoStatus(Date statusDate, Time statusTime, std::string status);
	void printColorAndProgram();
	virtual ~PhotoStatus();
};