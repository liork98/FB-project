#pragma once
#ifndef _ADMIN_H
#define _ADMIN_H
#include "Friend.h"
#include "Page.h"
#define MAX_LEN_NAME 30
#define ZERO 0
#define ONE 1
#define TYPE_FRIEND 0
#define TYPE_PAGE 1

class Admin
{
private:
	std::vector<Friend*> friendsArr;
	std::vector<Page*> pagesArr;
	//std::vector<Status*> statusArr;
public:
	void writeLinksBTWFriendsAndPagesTofile(std::ofstream& inFile);
	void writeLinksBTWFriendsTofile(std::ofstream& inFile);
	bool isExist(const std::string& name, int typeArr, int* indexResult);// checks if friend / page is exist
	bool createAFriend(const std::string& name, Date& date); // creating new member (type friend) in facebook
	bool createAPage(const std::string& name);// creating new member (type page) in facebook
	bool addAStatus(int typeArr); //set status and reads addStatusToArr()
	void printFriendsArr();
	void printPagesArr();
	Date createDate();
	Time createTime();
	void addStatusToArr(int typeArr, int index, Status* status);//adding a status to friend/page
	bool printFriendsOfFriends(const std::string& name_, int typeArr);// prints all friends of a friend
	void printAllStatus(int typeArr, int typeMethod, const std::string& name_2);
	bool LinkMembers(const std::string& name1, const std::string& name2, int type1, int type2); // link between friends/ page and friend
	bool UnlinkMembers(const std::string& name1, const std::string& name2, int type1, int type2);// Cancels link between friends/ page and friend
	void showAllPagesOfAFriend(const std::string& name1);
	void exit();
	void writeToFile();
	void countLinks(int* linksFriends, int* linksPages);
	void createAStatus(int typeStatus, Date& statusDate, Time& statusTime, std::string& status,int typeArr, int indexResult);
};
#endif // _ADMIN_H
