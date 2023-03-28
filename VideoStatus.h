#pragma once
#include "Status.h"

class VideoStatus : public Status
{	
public:
	VideoStatus(Date statusDate, Time statusTime, std::string status);
	void printColorAndProgram();
	virtual ~VideoStatus();
};