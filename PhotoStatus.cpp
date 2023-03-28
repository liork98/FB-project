#include "PhotoStatus.h"
using namespace std;
#include <iostream>

PhotoStatus::PhotoStatus(Date statusDate, Time statusTime, std::string status)
	: Status(statusDate, statusTime, status)
{

}

void PhotoStatus::printColorAndProgram()
{
	cout << this->textData;
	cout << "\nThis status is printed colourful using simple program." << endl;
}
PhotoStatus::~PhotoStatus()
{

}