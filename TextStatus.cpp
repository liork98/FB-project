#include "TextStatus.h"
using namespace std;
#include <iostream>

void TextStatus::printColorAndProgram()
{
	cout << textData;
	cout << " (This status is printed in black and white in simple program.)" << endl;
}

TextStatus::TextStatus(Date statusDate, Time statusTime, std::string status, Friend* author)
	: Status(statusDate, statusTime, status, author)
{
}

TextStatus::~TextStatus()
{

}