#pragma once
#include "Status.h"
#include "Date.h"
#include "Time.h"
class TextStatus : public Status
{
public:
	TextStatus(Date statusDate, Time statusTime, std::string status);
	void printColorAndProgram();
	virtual ~TextStatus();

};