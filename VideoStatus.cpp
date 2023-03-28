#include "VideoStatus.h"
using namespace std;
#include <iostream>

VideoStatus::VideoStatus(Date statusDate, Time statusTime, std::string status)
	: Status(statusDate, statusTime, status)
{
}

void VideoStatus::printColorAndProgram()
{
	cout << this->textData;
	cout << "\nThis status is printed colourful in video player" << endl;
}

VideoStatus::~VideoStatus()
{}