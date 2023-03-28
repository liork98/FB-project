#include "Friend.h"
#include <fstream>
using namespace std;
#define ZERO 0
#define INVALID_INDEX -1
#define METHOD_7 7
#define TEN 10

Friend::Friend(const string name, Date& birth_)
{
	setName(name);

	this->birth = birth_;
}

void Friend::setName(const string name)
{
	this->name = name;
}

const string Friend::getName()
{
	return name;
}

bool Friend::isFriendIsLinked(Friend* friend_, int* index)
{
	bool res = false;
	for (int i = 0; i < friendsArr.size() && res != true; i++) 
	{
		if (friendsArr[i] == friend_) 
		{
			*index = i;
			res= true;
		}		
	}
	*index = INVALID_INDEX;
	return res;
}

bool Friend::isFriendIsAFan(Page* page_, int* index)
{
	int count = ZERO;
	bool res = false;
	*index = INVALID_INDEX;
	vector<Page*>::iterator itr = pagesArr.begin();
	vector<Page*>::iterator itrEnd = pagesArr.end();
	for (; itr != itrEnd; ++itr)
	{
		if (*itr == page_)
		{
			*index = count;
			res = true;
		}
		count++;
	}
	return res;

}

void Friend::addNewStatus(Status* status) 
{
	statusesArr.push_back(status);
}

void Friend::printStatuses(int type) noexcept(false)
{
	
	int size = statusesArr.size();

	// If size is 0
	if (size == ZERO && type!=METHOD_7)
	{
		throw "Error: There are no statuses to print!";
	}

	else // size != 0
	{
		
		vector<Friend*> ::iterator frienditr = friendsArr.begin();
		vector<Friend*> ::iterator frienditrEnd = friendsArr.end();
		vector<Status*> ::iterator statusitr = statusesArr.begin();
		vector<Status*> ::iterator statusitrEnd = statusesArr.end();

		int count = ZERO;
		
		if (type == METHOD_7)
		{
			size = getMin((*frienditr)->statusesArr.size(), TEN);
			for (; frienditrEnd != frienditr && size != 0; ++frienditrEnd) // Running per a friend
			{
				cout << "Statuses of: " << (*frienditr)->getName() << endl;
				statusitr = (*frienditr)->statusesArr.begin();
				statusitrEnd =  (*frienditr)->statusesArr.end();
				if (size == ZERO)
				{
					cout << "Error: There are no statuses to print!";
				}
				for (; statusitrEnd != statusitr && size != ZERO; --statusitrEnd) // Running per a status
				{
					cout << "Status number " << count + 1 << ":\n Date: ";
					(**(statusitrEnd-1)).getStatusDate().printDate();
					(**(statusitrEnd - 1)).getStatusTime().printTime();
					cout << "The status data: " << endl;
					(**(statusitrEnd - 1)).getStatus();
					count++;
					size--;
				}
				size = getMin((*frienditr)->statusesArr.size(), TEN);
				count = ZERO;
			}
		}
	
		else // type ==5
		{
			for (; statusitr != statusitrEnd; ++statusitr)
			{
				cout << "Status number " << count + 1 << "\nDate: ";
				(**statusitr).getStatusDate().printDate();
				cout << "Time: ";
				(**statusitr).getStatusTime().printTime();
				cout << "\nThe status data: " <<endl << endl;
				(**statusitr).getStatus();
				//cout << "\n";
				count++;
			}
		}
	}
	
}

void Friend::addAFriendTo(Friend* friend_) noexcept(false)
{
	int index = INVALID_INDEX;
	if (isFriendIsLinked(friend_, &index)) 
	{
		throw "Friends are already linked";
	}
	friendsArr.push_back(friend_);
}

void Friend::addPageToArr(Page* page_)
{
	pagesArr.push_back(page_);
}

void Friend::removeFriendFrom(Friend* friend_) noexcept(false) //Unlink between friends
{
	int index;

	if (isFriendIsLinked(friend_, &index)) 
	{
		friendsArr.erase(friendsArr.begin() + index);
	}
	else
	{
		throw "Error: The friends are already unlinked.";
	}
	
}

void Friend::removePageFrom(Page* page_) noexcept(false) //unlink between friend and a page
{
	int index;

	if (isFriendIsAFan(page_, &index))
	{
		pagesArr.erase(pagesArr.begin() + index);
	}
	else
	{
		throw "Error: This friend is not a fan of this page.";
	}
}

void Friend::printFriendArr()
{
	cout << "Friends:\n" << endl;
	int count = ZERO;
	vector<Friend*>::iterator itr = friendsArr.begin();
	vector<Friend*>::iterator itrEnd = friendsArr.end();
	for (; itr != itrEnd; ++itr)
	{
		cout << count << ". " << (*itr)->getName() << endl;
		count++;
	}

}

Friend::~Friend() 
{
	vector<Status*>::iterator statusitr = statusesArr.begin();
	vector<Status*>::iterator statusitrEnd = statusesArr.end();
	
	for (; statusitr != statusitrEnd; ++statusitr) // Free statuses
	{
		delete (*statusitr);
	}
}

int Friend::getMin(int a, int b)
{
	return (a < b ? a : b);
}
 
void Friend::printPages()
{
	vector<Page*>::iterator pageitr = pagesArr.begin();
	vector<Page*>::iterator pageitrEnd = pagesArr.end();
	for (; pageitr != pageitrEnd; ++pageitr)
	{
		cout << (*pageitr)->getName() <<endl;
	}
	this;
}

Date Friend::getDate()
{
	return birth;
}

int Friend::getNumberOfFriends()
{
	return friendsArr.size();
}
int Friend::getNumberOfpages()
{
	return pagesArr.size();
}
int Friend::getNumberOfstatuses()
{
	return statusesArr.size();
}
void Friend::writeFriendToFile(ofstream& inFile)
{
	vector<Status*>::iterator statusitr = statusesArr.begin();
	vector<Status*>::iterator statusitrEnd = statusesArr.end();
	inFile << name << "\n" << birth.getDay() << " " << birth.getMonth() << " " << birth.getYear() << "\n";
	inFile << friendsArr.size() << "\n" << pagesArr.size() << "\n" << statusesArr.size() << "\n";
	for (; statusitr != statusitrEnd; ++statusitr)
	{
		string st = typeid(**statusitr).name()+6;
		if (st == "TextStatus")
			inFile << "1\n";
		else if (st == "PhotoStatus")
			inFile << "2\n";
		else
			inFile << "3\n";

		inFile << (*statusitr)->getStatusDate().getDay() << " " << (*statusitr)->getStatusDate().getMonth()
			<< " " << (*statusitr)->getStatusDate().getYear() <<" " << (*statusitr)->getStatusTime().getHour()
			<< " " << (*statusitr)->getStatusTime().getMin() << "\n" << (*statusitr)->getStatusData() << "\n";
	}
}

vector<Friend*>& Friend::getFriendsVector()
{
	return friendsArr;
}


vector<Page*>& Friend::getPagesVector()
{
	return pagesArr;
}