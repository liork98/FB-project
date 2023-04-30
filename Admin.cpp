using namespace std; 
#include "Admin.h"
#define MIN 3
#define ZERO 0
#define INVALID_INDEX -1
#define SHOW_LAST_STATUSES_METHOD 7
#include <string>
#include <iostream>
#include "TextStatus.h"
#include "PhotoStatus.h"
#include "VideoStatus.h"
#include <fstream>

std::vector<Friend*> Admin::getFriendsArr()
{
	return friendsArr;
}

void Admin::PrintRecentStatuses(Friend& friend_)
{

	int count = 0;
	vector<Status*>::iterator statusitr = statusesArr.begin();
	vector<Status*>::iterator statusitrEnd = statusesArr.end();
	Friend* currentFriend;
	for (; statusitr != statusitrEnd; ++statusitr) // Run per status
	{
		
		currentFriend = (*statusitr)->getAuthor();
		if (currentFriend->areFriends(&friend_)) // The current status's author is a friend 
		{
			cout << "\n  ________________________" << endl;
			cout << " /                        \\" << endl;
			cout << "|       Status number:     |	" << ++count << endl;
			cout << " \\________________________/" << endl << "		";

			(*statusitr)->PrintStatus();
		}
	}
}




bool Admin::isExist(const string& name, int typeArr, int* indexResult) 
{
	//bool res = false;
	int count = ZERO;
	

	if (typeArr == TYPE_FRIEND) 
	{
		vector<Friend*>::iterator frienditr = friendsArr.begin();
		vector<Friend*>::iterator frienditrEnd = friendsArr.end();
		for (; frienditr != frienditrEnd; ++frienditr)
		{
			if (name== (*frienditr)->getName()) // if names are equal
			{
				*indexResult = count;
				return true;
				
			}
			count++;
		}
		
	}
	
	else if (typeArr == TYPE_PAGE)
	{
		vector<Page*>::iterator pageitr = pagesArr.begin();
		vector<Page*>::iterator pageitrEnd = pagesArr.end();
		for (; pageitr != pageitrEnd; ++pageitr)
		{
			if (name== (*pageitr)->getName()) // if names are equal
			{
				*indexResult = count;
				return true;
			}
			count++;
		}
	}

	return false;
}

bool Admin::createAFriend(const string& name, Date& date) noexcept(false)
{
	int resIndex = INVALID_INDEX;
	bool res;
	if (isExist(name, TYPE_FRIEND, &resIndex) == true)
	{
		throw "This user is already exist\n";
		res = false;
	}
	else
	{
		friendsArr.push_back(new Friend(name, date));
		res = true;
	}

	return res;
}

bool Admin::createAPage(const string& name) 
{
	int resIndex = INVALID_INDEX;
	bool res;
	if (isExist(name, TYPE_PAGE, &resIndex) == true)
	{
		res=false;
	}
	else
	{
		pagesArr.push_back(new Page(name));
		res= true;
	}
	return res;
}

bool Admin::addAStatus(int typeArr) 
{
	bool res=false;
	int indexResult;
	string name;
	string status;

	if (typeArr == TYPE_FRIEND) //Friends
	{
		cout << "Choose a friend to add status:\n" << endl;
		printFriendsArr();
		cout << "Name of friend:\n" <<endl;
		getchar();
		getline(cin, name);
	}
	else 
	{
		cout << "Choose a page to add status:\n" << endl;
		printPagesArr();
		cout << "Name of page:\n"<< endl;
		getchar();
		getline(cin, name);
	}
	if (isExist(name, typeArr, &indexResult)) // Page is exist
	{
		cout << "Please enter number of a type of status you want to add:\n1. Text\n2. Photo\n3. Video\n";
		int typeStatus;
		cin >> typeStatus;
		if (!(typeStatus >= ONE && typeStatus <= 3))
			throw "Invalid number of type of status.";

		cout << "Enter status data:";
		getchar();
		getline(cin, status);
		Date statusDate = createDate();
		Time statusTime = createTime();
		createAStatus(typeStatus, statusDate, statusTime, status, typeArr, indexResult);
		
		res = true;

	}
	return res; 
}

void Admin::createAStatus(int typeStatus, Date& statusDate, Time& statusTime, string& status, int typeArr, int indexResult)
{
	Status* newStatus;
	switch (typeStatus)
	{
	case(ONE):
	{
		Status* newStatus = new TextStatus(statusDate, statusTime, status, friendsArr[indexResult]);
		addStatusToArr(typeArr, indexResult, newStatus);
		break;
	}
	case(2):
	{
		Status* newStatus = new PhotoStatus(statusDate, statusTime, status, friendsArr[indexResult]);
		addStatusToArr(typeArr, indexResult, newStatus);
		break;
	}
	case(3):
	{
		Status* newStatus = new VideoStatus(statusDate, statusTime, status, friendsArr[indexResult]);
		addStatusToArr(typeArr, indexResult, newStatus);
		break;
	}
	}
}

void Admin::addStatusToArr(int typeArr, int index, Status* status)
{
	if (typeArr == TYPE_FRIEND)
	{
		vector<Friend*>::iterator itr1 = friendsArr.begin();
		(*(itr1 + index))->addNewStatus(status);
		statusesArr.push_back(status);
	}
	else 
	{
		vector<Page*>::iterator itr2 = pagesArr.begin();
		(*(itr2 + index))->addNewStatus(status);
	}
}

bool Admin::printFriendsOfFriends(const string& name_, int typeArr)
{
	int indexFriend = INVALID_INDEX;
	
	if (isExist(name_, typeArr, &indexFriend)) 
	{
		if (typeArr == TYPE_FRIEND) 
		{
			vector<Friend*>::iterator itr1 = friendsArr.begin();
			(*(itr1 + indexFriend))->printFriendArr();
		}
		else
		{
			vector<Page*>::iterator itr2 = pagesArr.begin();
			(*(itr2 + indexFriend))->printAllFriends();
		}
		return true;
	}
	else
	{
		cout << "This user isn't exist. Try again." << endl;
		return false;
	}
}

void Admin::printFriendsArr()
{
	cout << "Friends:\n" << endl;
	int count = ZERO;
	vector<Friend*>::iterator itr = friendsArr.begin();
	vector<Friend*>::iterator itrEnd = friendsArr.end();
	for (; itr != itrEnd; ++itr)
	{
		cout << count + 1 << ". " << (*itr)->getName() << endl;
		count++;
	}
	if (count == 0)
	{
			cout << endl << "					-----------------------------------" << endl;
			cout << "					|                                 |" << endl;
			cout << "					|      No statuses to preview     |" << endl;
			cout << "					|                                 |";
			cout << endl << "					-----------------------------------" << endl;
	}
}

void Admin::printPagesArr()
{
	cout << "\nPages:\n" << endl;
	int count = ZERO;

	vector<Page*>::iterator itr = pagesArr.begin();
	vector<Page*>::iterator itrEnd = pagesArr.end();
	for (; itr != itrEnd; ++itr)
	{
		cout << count + 1 << ". " << (*itr)->getName() << endl;
		count++;
	}
}

vector<Status*> Admin::getStatusesArr()
{
	return statusesArr;
}

void Admin::printAllStatus(int typeArr, int typeMethod, const string& name_2, Admin* admin) 
{
	int indexResult;
	string name;
	std::vector<Status*> statusesArr = admin->getStatusesArr();
	
		if (typeMethod != SHOW_LAST_STATUSES_METHOD)
		{
			if (typeArr == TYPE_FRIEND) //Friends
			{
				cout << "Enter the name of a friend from the list:\n" << endl;
				printFriendsArr();

			}
			else
			{
				cout << "Enter the name of a page from the list: \n" << endl;
				printPagesArr();
			}
			getchar();
			getline(cin, name);


			if (isExist(name, typeArr, &indexResult))
			{
				if (typeArr == TYPE_FRIEND)
				{
					vector<Friend*>::iterator itr = friendsArr.begin();
					(*(itr + indexResult))->printStatuses(typeMethod, statusesArr);
				}
				else
				{
					vector<Page*>::iterator itr = pagesArr.begin();
					(*(itr + indexResult))->printStatuses();
				}
			}

		}
		else if (isExist(name_2, typeArr, &indexResult) && typeMethod == 7)
		{

			if (typeArr == TYPE_FRIEND)
			{
				vector<Friend*>::iterator itr = friendsArr.begin();
				(*(itr + indexResult))->printStatuses(typeMethod, admin->getStatusesArr());
			}
			else
			{
				vector<Page*>::iterator itr = pagesArr.begin();
				(*(itr + indexResult))->printStatuses();
			}
		
	}
}

bool Admin::LinkMembers(const string& name1, const string& name2, int type1, int type2) 
{
	int indexResult1, indexResult2;
	bool res = false;
	vector<Friend*>::iterator frienditr = friendsArr.begin();
	vector<Page*>::iterator pageitr = pagesArr.begin();

	if (isExist(name1, type1, &indexResult1) && isExist(name2, type2, &indexResult2))
	{
		
		if (type1 == TYPE_FRIEND && type2==TYPE_FRIEND) // Link friends
		{
			(**(frienditr + indexResult1)) += (**(frienditr + indexResult2));
			(**(frienditr + indexResult2)) += (**(frienditr + indexResult1));

		}
		else if (type1 == TYPE_FRIEND && type2 == TYPE_PAGE)// Link fan to page
		{
			(**(pageitr + indexResult2)) += (**(frienditr + indexResult1));
			(**(frienditr + indexResult1)) += (**(pageitr + indexResult2));
		}
		res = true;
	}
	return res;
}

bool Admin::UnlinkMembers(const string& name1, const string& name2, int type1, int type2)
{
	int indexResult1, indexResult2;
	bool res = false;
	vector<Friend*>::iterator frienditr = friendsArr.begin();
	vector<Page*>::iterator pageitr = pagesArr.begin();

	if (isExist(name1, type1, &indexResult1) && isExist(name2, type2, &indexResult2))
	{
		if (type1 == TYPE_FRIEND && type2 == TYPE_FRIEND) // Unlink friends
		{
			(*(frienditr + indexResult1))->removeFriendFrom(*(frienditr + indexResult2));
			(*(frienditr + indexResult2))->removeFriendFrom(*(frienditr + indexResult1));
			cout << endl << "					-----------------------------------" << endl;
			cout << "					|                                 |" << endl;
			cout << "					|      Members are unlinked       |" << endl;
			cout << "					|                                 |" << endl;
			cout << "					-----------------------------------" << endl << endl;
		}
		else if (type1 == TYPE_FRIEND && type2 == TYPE_PAGE)// Unlink fan from page
		{
			(*(pageitr + indexResult1))->removeFanFromPage(*(frienditr + indexResult2));
			(*(frienditr + indexResult2))->removePageFrom(*(pageitr + indexResult1));
		}
		res = true;
	}
	return res;
}

void Admin::exit()
{
	writeToFile();

	vector<Friend*>::iterator frienditr = friendsArr.begin();
	vector<Friend*>::iterator frienditrEnd = friendsArr.end();
	vector<Page*>::iterator pageitr = pagesArr.begin();
	vector<Page*>::iterator pageitrEnd = pagesArr.end();
	
	for (; frienditr != frienditrEnd; ++frienditr)
	{
			delete (*frienditr);	
	}
	for (; pageitr != pageitrEnd; ++pageitr)
	{
     	delete (*pageitr);
	}
}

void Admin::writeToFile()
{
	vector<Friend*>::iterator frienditr = friendsArr.begin();
	vector<Friend*>::iterator frienditrEnd = friendsArr.end();
	vector<Page*>::iterator pageitr = pagesArr.begin();
	vector<Page*>::iterator pageitrEnd = pagesArr.end();
	ofstream inFile;
	inFile.open("recent_run_data.txt");
	int linksBTWfriends=0, linksBTWPages=0;

	inFile << friendsArr.size() << "\n" << pagesArr.size() << "\n";
	for (; frienditr != frienditrEnd; ++frienditr) // Printing friends to file
	{
		(*frienditr)->writeFriendToFile(inFile);
	}
	for (; pageitr != pageitrEnd; ++pageitr)// Printing pages to file
	{
		(*pageitr)->writeFriendToFile(inFile);
	}
	countLinks(&linksBTWfriends, &linksBTWPages);
	inFile << linksBTWfriends << "\n" << linksBTWPages << "\n";

	writeLinksBTWFriendsTofile(inFile);
	writeLinksBTWFriendsAndPagesTofile(inFile);
}

void Admin::writeLinksBTWFriendsAndPagesTofile(ofstream& inFile)
{
	vector<Friend*>::iterator frienditr = friendsArr.begin();
	vector<Friend*>::iterator frienditrEnd = friendsArr.end();
	vector<Page*>::iterator pageitr2;
	vector<Page*>::iterator pageitrEnd2;
	for (; frienditr != frienditrEnd; ++frienditr)
	{
		pageitr2 = (*frienditr)->getPagesVector().begin();
		pageitrEnd2 = (*frienditr)->getPagesVector().end();
		for (; pageitr2 != pageitrEnd2; ++pageitr2)
		{
				inFile << (*frienditr)->getName() << "\n" << (*pageitr2)->getName() << "\n";
		}
		
	}
}

void Admin::writeLinksBTWFriendsTofile(ofstream& inFile)
{
	vector<Friend*>::iterator frienditr = friendsArr.begin();
	vector<Friend*>::iterator frienditrEnd = friendsArr.end();
	vector<Friend*>::iterator frienditr2;
	vector<Friend*>::iterator frienditrEnd2;
	int index1, index2;
	for (; frienditr != frienditrEnd; ++frienditr)
	{
		frienditr2 =(*frienditr)->getFriendsVector().begin();
		frienditrEnd2 = (*frienditr)->getFriendsVector().end();
		for (; frienditr2 != frienditrEnd2; ++frienditr2)
		{
			isExist((*frienditr2)->getName(), TYPE_FRIEND, &index2);
			isExist((*frienditr)->getName(), TYPE_FRIEND, &index1);
			if (index2 > index1)
				inFile << (*frienditr)->getName() << "\n" << (*frienditr2)->getName() << "\n";
		}
		
	}
}
void Admin::countLinks(int* linksFriends, int* linksPages)
{
	vector<Friend*>::iterator frienditr = friendsArr.begin();
	vector<Friend*>::iterator frienditrEnd = friendsArr.end();
	vector<Page*>::iterator pageitr = pagesArr.begin();
	vector<Page*>::iterator pageitrEnd = pagesArr.end();
	
	for (; frienditr != frienditrEnd; ++frienditr) // Printing friends to file
	{
		*linksFriends += (*frienditr)->getNumberOfFriends();

	}
	*linksFriends = (*linksFriends) / 2;
	for (; pageitr != pageitrEnd; ++pageitr)// Printing pages to file
	{
		*linksPages += (*pageitr)->getNumberOfFans();
	}
	
	
}

Time Admin::createTime()
{
	int hours;
	int minutes;
	cout << "\nPlease Enter a time: Hour Minutes" << endl;
	cin >> hours >> minutes;
	Time res(hours, minutes);
	return res;
}

Date Admin::createDate()
{
	cout << "\nPlease Enter a date: Day Month Year" << endl;
	int year;
	int month;
	int day;
	
	cin >> day >> month >> year;
	Date res(day, month, year);
	return res;
}

void Admin::showAllPagesOfAFriend(const string& name1)
{
	int index = INVALID_INDEX;
	if (isExist(name1, TYPE_FRIEND, &index))
	{
		(**(friendsArr.begin() + index)).printPages();
	}
}
