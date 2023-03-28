#pragma once
#ifndef _FRIEND_H
#define _FRIEND_H
#define _CRT_SECURE_NO_WARNINGS
#include "Status.h"
#include "Page.h"
#include <list>
#include <vector>
#include <string.h>
#include <string>
#include <fstream>
class Page;
class Friend
{
private:
	std::string name="";
	Date birth;
	std::vector<Status*> statusesArr; 
	std::vector<Friend*> friendsArr;
	std::vector<Page*>pagesArr;

public:
	// C'tor
	Friend(const std::string name_, Date& birth_);
	// Returns friend's name
	const std::string getName();
	//Returns true if friends are already linked 
	bool isFriendIsLinked(Friend* friend_, int* index); 
	//Returns true if page is already linked
	bool isFriendIsAFan(Page* page_, int* index); 
	void addNewStatus(Status* status);
	void printStatuses(int type) noexcept(false);
	void addAFriendTo(Friend* friend_)noexcept(false);
	void addPageToArr(Page* page_);
	void removeFriendFrom(Friend* friend_) noexcept(false);
	void removePageFrom(Page* page_)noexcept(false);
	void printFriendArr();
	void setName(const std::string name);
	void printPages();
	// Returns minimum between two numbers
	int getMin(int a, int b);
	// D'tor
	~Friend();
	Date getDate();
	std::vector<Friend*>& getFriendsVector();
	std::vector<Page*>& getPagesVector();
	int getNumberOfFriends();
	int getNumberOfpages();
	int getNumberOfstatuses();
	void writeFriendToFile(std::ofstream& inFile);

	Friend& operator+=(Friend& friendToAdd)
	{
		addAFriendTo(&friendToAdd);
		return *this;
	}

	Friend& operator+=(Page& pageToAdd)
	{
		addPageToArr(&pageToAdd);
		return *this;
	}

};


#endif // _FRIEND_H
