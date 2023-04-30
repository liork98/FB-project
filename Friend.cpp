#include "Friend.h"
#include <fstream>
using namespace std;
#define ZERO 0
#define INVALID_INDEX -1
#define SHOW_LAST_STATUSES_METHOD 7
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

	for (int i = 0; i < friendsArr.size(); i++) 
	{
		if (friendsArr[i] == friend_) 
		{
			*index = i;
			return true;
		}		
	}
	*index = INVALID_INDEX;
	return false;
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

bool Friend::areFriends(Friend* friend_)
{
	vector<Friend*>::iterator frienditr1 = friendsArr.begin();
	vector<Friend*>::iterator frienditrEnd1 = friendsArr.end();

	for (; frienditr1 != frienditrEnd1; ++frienditr1)
	{
		if (*frienditr1 == friend_)
		{
			return true;
		}
	}
	return false;
}

void Friend::printStatuses(int type, vector<Status*> statusesArr_) noexcept(false)
{
	
	int size = statusesArr.size();

	// If size is 0
	if (size == ZERO && type!=SHOW_LAST_STATUSES_METHOD)
	{
		throw "\n\n ERROR:  There are no statuses to print!";
	}

	else // size != 0
	{

		int count = ZERO;
		
		if (type == SHOW_LAST_STATUSES_METHOD)
		{
			vector<Status*> ::iterator statusitr = statusesArr_.begin();
			vector<Status*> ::iterator statusitrEnd = statusesArr_.end();

			size = getMin(statusesArr_.size(), TEN);
				
				for (; statusitrEnd != statusitr; ++statusitr) // Running per a status
				{
					if (areFriends((*statusitr)->getAuthor()))
					{
						cout << "\n  ________________________" << endl;
						cout << " /                        \\" << endl;
						cout << "|        Statuses of :     |	" << (*statusitr)->getAuthor()->getName() << endl;
						cout << " \\________________________/" << endl << "		";

						cout << "\n  ________________________" << endl;
							cout << " /                        \\" << endl;
							cout << "|       Status number:     |	" << ++count << endl;
							cout << " \\________________________/" << endl << "		";

							(*statusitr)->PrintStatus();

							
					}
					
				}
				if (count == 0)
				{
					cout << " \n\nERROR: There are no statuses to print!";
				}
				size--;
				count = ZERO;
		}
	
		else // type ==5
		{
			vector<Status*> ::iterator statusitr = statusesArr.begin();
			vector<Status*> ::iterator statusitrEnd = statusesArr.end();
			for (; statusitr != statusitrEnd; ++statusitr)
			{
				cout << "\n  ________________________" << endl;
				cout << " /                        \\" << endl;
				cout << "|       Status number:     |	" << count + 1 <<endl;
				cout << " \\________________________/" << endl << "		";

				(*statusitr)->PrintStatus();

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
		throw " ___________\n/           \\ \n|   ERROR   |\n\\___________/\n The friends are already unlinked.";
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
		throw "  ___________\n/           \\ \n|   ERROR   |\n\\___________/\nThis friend is not a fan of this page.";
	}
}

void Friend::printFriendArr()
{
	if (friendsArr.size() == 0)
	{
		cout << endl << "					-----------------------------------" << endl;
		cout << "					|                                 |" << endl;
		cout << "					|      No friends to preview      |" << endl;
		cout << "					|                                 |";
		cout << endl << "					-----------------------------------" << endl;
	}
	else
	{
		cout << "\nFriends:\n" << endl;
		int count = ZERO;
		vector<Friend*>::iterator itr = friendsArr.begin();
		vector<Friend*>::iterator itrEnd = friendsArr.end();
		for (; itr != itrEnd; ++itr)
		{
			cout << ++count << ". " << (*itr)->getName() << endl;
		}
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