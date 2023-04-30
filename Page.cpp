using namespace std; 
#include "Page.h"
#define ZERO 0
#define INVALID_INDEX -1


Page::Page(const string name_)
{
	setName(name_);
}

void Page::setName(const string& name1)
{
	name = name1;
}

string Page::getName()
{
	return name;
}

void Page::addNewStatus(Status* status)
{
	statusArr.push_back(status);
}

void Page::printStatuses()
{
	if (statusArr.size() == 0)
	{
		cout << "\nFriend list is empty." << endl;
	}
	else 
	{
		vector<Status*>::iterator itr = statusArr.begin();
		vector<Status*>::iterator itrEnd = statusArr.end();
		int i = 0;
		for (; itr != itrEnd; ++itr)
		{
			cout << "Status number " << i << ": " << endl;
			(**itr).getStatus();
			i++;
		}
	}
}


void Page::printAllFriends()
{
	cout << "Fans:\n" << endl;
	int count = ZERO;
	vector<Friend*>::iterator itr = fansArr.begin();
	vector<Friend*>::iterator itrEnd = fansArr.end();
	for (; itr != itrEnd; ++itr)
	{
		cout << count+1 << ". " << (*itr)->getName() << endl;
		count++;
	}
}

void Page::addFanToPage(Friend* friend_) noexcept(false)
{
	int index = INVALID_INDEX;
	if (isFriendIsAFan(friend_, &index))
	{
		throw "This user is already a fan";
	}
	fansArr.push_back(friend_);
}

void Page::removeFanFromPage(Friend* friend_)
{
	int index;
	if (isFriendIsAFan(friend_, &index))
	{
		fansArr.erase(fansArr.begin() + index);
	}

}

bool Page::isFriendIsAFan(Friend* friend_, int* index)
{
	vector<Friend*>::iterator itr = fansArr.begin();
	for (int i = 0; i < fansArr.size(); i++)
	{
		if ((*itr) == friend_)
		{
			*index = i;
			return true;
		}
	}
	*index = INVALID_INDEX;
	return false;

}

Page::~Page() //d'ctor
{

	vector<Status*>::iterator statusitr = statusArr.begin();
	vector<Status*>::iterator statusitrEnd = statusArr.end();

	for (; statusitr != statusitrEnd; ++statusitr) // Free statuses
	{
		delete (*statusitr);
	}
}


void Page::writeFriendToFile(ofstream& inFile)
{

	vector<Status*>::iterator statusitr = statusArr.begin();
	vector<Status*>::iterator statusitrEnd = statusArr.end();
	inFile << name << "\n" << fansArr.size() << "\n" << statusArr.size() << "\n";
	for (; statusitr != statusitrEnd; ++statusitr)
	{
		if (typeid(**statusitr).name() == "TextStatus")
			inFile << "1\n";
		else if (typeid(**statusitr).name() == "PhotoStatus")
			inFile << "2\n";
		else
			inFile << "3\n";

		inFile << (*statusitr)->getStatusDate().getDay() << " " << (*statusitr)->getStatusDate().getMonth()
			<< " " << (*statusitr)->getStatusDate().getYear() << (*statusitr)->getStatusTime().getHour()
			<< " " << (*statusitr)->getStatusTime().getMin() << "\n" << (*statusitr)->getStatusData() << "\n";
	}
}

int Page::getNumberOfFans()
{
	return fansArr.size();
};