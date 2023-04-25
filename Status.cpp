using namespace std;
#include "Status.h"

Status::Status(Date date, Time time, const std::string& textData, Friend* author)
{
	setStatus(textData);
	this->date = date;
	this->time = time;
	this->author = author;
}

void Status::setStatus(const string& status)
{
	textData = status;
}

const void Status::getStatus()
{
	printColorAndProgram();
}

void Status::PrintStatus()
{

	cout << "\n  ________________________" << endl;
	cout << " /                        \\" << endl;
	cout << "|           Date:          |	";
	date.printDate();
	cout << " \\________________________/" << endl << "	";

	cout << "\n  ________________________" << endl;
	cout << " /                        \\" << endl;
	cout << "|           Time:          |	";
	time.printTime();
	cout << "\n \\________________________/" << endl << "	";

	cout << "\n  ________________________" << endl;
	cout << " /                        \\" << endl;
	cout << "|        Status data:      |	" << this->getStatusData();
	
	cout << "\n \\________________________/" << endl << "---------------------------------------------------------------------------------------------";

}

Date Status::getStatusDate()
{
	return date;
}
Time Status::getStatusTime()
{
	return time;
}
string Status::getStatusData() 
{
	return textData;
}

bool Status::operator==(Status* statusToCompare) 
{
	if (statusToCompare->textData == this->textData)
	{
		return true;
	}
	return false;
}

bool Status::operator!=(Status* statusToCompare)
{
	if (statusToCompare->textData != this->textData)
	{
		return true;
	}
	return false;
}

Friend* Status::getAuthor()
{
	return author;
}

Status::~Status()
{

}