#include "PhotoStatus.h"
using namespace std;
#include <iostream>
PhotoStatus::PhotoStatus(Date statusDate, Time statusTime, std::string status, Friend* author)
	: Status(statusDate, statusTime, status, author)
{

}

void PhotoStatus::printColorAndProgram()
{
	cout << this->textData;
	cout << " (This status is printed colourful using simple program.)" << endl;
}
PhotoStatus::~PhotoStatus()
{

}