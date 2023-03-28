#include "TextStatus.h"
using namespace std;
#include <iostream>

void TextStatus::printColorAndProgram()
{
	cout << textData;
	cout << "\nThis status is printed in black and white in simple program." << endl;
}

TextStatus::TextStatus(Date statusDate, Time statusTime, std::string status) 
	: Status(statusDate, statusTime, status)
{
}

TextStatus::~TextStatus()
{
	//delete this;
}