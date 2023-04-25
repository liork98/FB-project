#pragma once
#ifndef _PAGE_H
#define _PAGE_H
#include "Status.h"
#include "Friend.h"
#include <vector>
#include <fstream>

class Status;
class Friend;

class Page
{
private:
	std::string name;
	std::vector <Friend*> fansArr;
	std::vector<Status*> statusArr;

public:
	Page(const std::string name); //c'tor
	void setName(const std::string& name1);
	std::string getName();
	void addNewStatus(Status* status);
	void printStatuses();
	void printAllFriends();
	void addFanToPage(Friend* friend_) noexcept(false);
	void removeFanFromPage(Friend* friend_);
	bool isFriendIsAFan(Friend* friend_, int* index);
	Page& operator+=(Friend& fan_)
	{
		addFanToPage(&fan_);
		return *this;

	}
	bool operator>(const Page* other) const
	{
		return (fansArr.size() > other->fansArr.size());
	}
	void writeFriendToFile(std::ofstream& inFile);
	int getNumberOfFans();
	~Page();
	
};

#endif // !_PAGE_H#pragma once
