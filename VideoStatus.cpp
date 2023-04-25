#include "VideoStatus.h"
using namespace std;
#include <iostream>

VideoStatus::VideoStatus(Date statusDate, Time statusTime, std::string status, Friend* author)
	: Status(statusDate, statusTime, status, author)
{
}

void VideoStatus::printColorAndProgram()
{
	cout << this->textData;
	cout << " (This status is printed colourful in video player)" << endl;
}

VideoStatus::~VideoStatus()
{}