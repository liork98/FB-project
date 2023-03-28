#include "Admin.h"
#include "Friend.h"
#include "Page.h"
#include "TextStatus.h"
#include "PhotoStatus.h"
#include "VideoStatus.h"
#include <fstream>

using namespace std;
#define ZERO 0
#define EXIT 16
#define METHOD_5 5
#define METHOD_7 7


void Method(Admin& admin, int choose);
void showMenu(Admin& admin);
Admin readFile(ifstream& inFile);
void getFriendArr(bool* flag, ifstream& inFile, char delimeter1, char delimeter2, int i, Admin& newAdmin);
void getPageArr(bool* flag, ifstream& inFile, char delimeter1, char delimeter2, int i, Admin& newAdmin);
void linkMembers(Admin& newAdmin, ifstream& inFile, char delimeter1, char delimeter2);

int main()
{
		// Creating local admin.
		Admin admin;

		ifstream inFile;
		inFile.open("Data.txt");
		if (!inFile)
		{
			// Creating local members.
			Date date1(20, 5, 2000);
			admin.createAFriend("friend1", date1);

			Date date2(1, 11, 1998);
			admin.createAFriend("friend2", date2);

			Date date3(15, 2, 1997);
			admin.createAFriend("friend3", date3);

			admin.createAPage("FanPage1");
			admin.createAPage("FanPage2");
			admin.createAPage("FanPage3");

			// Every local member have two friends.
			admin.LinkMembers("friend1", "friend2", TYPE_FRIEND, TYPE_FRIEND);
			admin.LinkMembers("friend1", "friend3", TYPE_FRIEND, TYPE_FRIEND);
			admin.LinkMembers("friend3", "friend2", TYPE_FRIEND, TYPE_FRIEND);

			// Every local member have two statuses.
			//Friend1
			Date date11(1, 12, 2000);
			Time time11(1, 1);
			Status* status1a = new TextStatus(date11, time11, "status text 1");
			Status* status1b = new PhotoStatus(date11, time11, "status text 2");
			//Friend2
			Status* status1c = new TextStatus(date11, time11, "status text 1");
			Status* status1d = new PhotoStatus(date11, time11, "status photo 2");
			//Friend3
			Status* status1e = new TextStatus(date11, time11, "status text 1");
			Status* status1f = new VideoStatus(date11, time11, "status video 2");

			admin.addStatusToArr(TYPE_FRIEND, 0, status1a);
			admin.addStatusToArr(TYPE_FRIEND, 0, status1b);
			admin.addStatusToArr(TYPE_FRIEND, 1, status1c);
			admin.addStatusToArr(TYPE_FRIEND, 1, status1d);
			admin.addStatusToArr(TYPE_FRIEND, 2, status1e);
			admin.addStatusToArr(TYPE_FRIEND, 2, status1f);
		}
		else
		{
			admin = readFile(inFile);
		}
		
		int choose = ZERO;
		while (choose != EXIT)
		{
			showMenu(admin);
			cin >> choose;
			Method(admin, choose);
		}
		inFile.close();// close file
	return 0;
}

Admin readFile(ifstream& inFile)
{
	Admin newAdmin;
	int numOfFriends, numOfpages;
	
	int day, month, year, dayStatus, monthStatus, yearStatus;
	int hourStatus, minStatus;
	char delimeter1 = ' ';
	char delimeter2 = '\n';
	inFile >> numOfFriends >> numOfpages;
	bool flag = true;
	for (int i = 0; i < numOfFriends; i++) // Adding per a friend
	{
		getFriendArr(&flag,inFile, delimeter1, delimeter2, i, newAdmin);
		
	}
	//inFile >> numOfpages;
	flag = true;
	for (int i = 0; i < numOfpages; i++) // Adding per a friend
	{
		getPageArr(&flag , inFile, delimeter1, delimeter2, i, newAdmin);

	}

	linkMembers(newAdmin, inFile, delimeter1, delimeter2);
	return newAdmin;
}
void linkMembers(Admin& newAdmin, ifstream& inFile, char delimeter1, char delimeter2)
{
	string name1, name2;
	int linksBTWfriends, linkBTWpages, k;
	inFile >> linksBTWfriends >> linkBTWpages;
	string ch;
	bool flag = true;
	for (k = 0; k < linksBTWfriends; k++)
	{
		if (flag)
			getline(inFile, ch);
		flag = false;
		getline(inFile, name1);
		getline(inFile, name2);
		newAdmin.LinkMembers(name1, name2, TYPE_FRIEND, TYPE_FRIEND);
	}
	for (k = 0; k < linkBTWpages; k++)
	{
		getline(inFile, name1);
		getline(inFile, name2);
		newAdmin.LinkMembers(name1, name2, TYPE_FRIEND, TYPE_PAGE);
	}
}


void getPageArr(bool* flag,ifstream& inFile, char delimeter1, char delimeter2, int i, Admin& newAdmin)
{
	int numOfStatusesOfAPage, numOfFans;
	string name,status;
	string ch;
	int day, month, year, hourStatus, minStatus, statusType;
	if(!(*flag))
		getline(inFile, ch);
	*flag = false;
	getline(inFile, name);
	newAdmin.createAPage(name);
	inFile >> numOfFans >> numOfStatusesOfAPage ;
	for (int j = 0; j < numOfStatusesOfAPage; j++)
	{
		getline(inFile, status);
		inFile >> statusType >> delimeter2;
		inFile >> day  >> month  >> year  >> hourStatus >> minStatus;
		Date date2(day, month, year);
		Time time2(hourStatus, minStatus);
		newAdmin.createAStatus(statusType, date2, time2, status, TYPE_PAGE, i);
	}
	
	
}
void getFriendArr(bool* flag, ifstream& inFile ,char delimeter1, char delimeter2, int i, Admin& newAdmin)
{
	string name, status;
	int day, month, year, hourStatus, minStatus;
	int numOfFriendsOfAFriend, numOfFPagesOfAFriend, numOfStatusesOfAFriend, statusType;
	string ch;
	if (*flag)
		getline(inFile, ch);
	*flag = false;
	getline(inFile, name);
	inFile >> day  >> month >> year ;
	Date date1(day, month, year);
	inFile >> numOfFriendsOfAFriend >> numOfFPagesOfAFriend >> numOfStatusesOfAFriend;
	newAdmin.createAFriend(name, date1);
	for (int j = 0; j < numOfStatusesOfAFriend; j++)
	{
		inFile >> statusType;
		inFile >> day >> month >> year >> hourStatus >> minStatus;
		getline(inFile, ch);
		getline(inFile, status);
		
		
		Date date2(day, month, year);
		Time time2(hourStatus, minStatus);
		newAdmin.createAStatus(statusType, date2, time2, status, TYPE_FRIEND, i);
	}
	

}

void showMenu(Admin& admin)
{
	cout << "\n- - - Menu - - -\nPlease enter the number of what you want to do:\n" << endl;
	cout << "1. Create a friend." << endl;// (no. 1)
	cout << "2. Create a fan page." << endl;// (no. 2)
	cout << "3. Add a status to a friend." << endl;// (no. 3)
	cout << "4. Add a status to a fan page." << endl;// (no. 3)
	cout << "5. Show all status of a friend." << endl;// (no. 4)
	cout << "6. Show all status of a fan page." << endl; // (no. 4)
	cout << "7. Show last 10 statuses of friends of a member." << endl; // (no. 5)
	cout << "8. Link two friends." << endl; // (no. 6)
	cout << "9. Cancel link between two friends." << endl; // (no. 7)
	cout << "10. Link a fan to a page." << endl; // (no. 8)
	cout << "11. Cancel link between a friend and a fan page." << endl; // (no. 9)
	cout << "12. Show all members (friends and fan pages)." << endl; // (no. 10)
	cout << "13. Show all friends of a friend." << endl; // (no. 11)
	cout << "14. Show all fan of a fan page." << endl; // (no. 11)
	cout << "15. Show all fan pages of a friend." << endl;
	cout << "16. Exit." << endl; // (no. 12)
}

void Method(Admin& admin, int choose) noexcept(false)
{
	try
	{
		string name_1;
		string name_2;
		int day, month, year;
		switch (choose)
		{
		case 1:
		{
			cout << "Name: " << endl;
			getchar();
			getline(cin, name_1);
			cout << "Please Enter a date: Day Month Year" << endl;
			cin >> day >> month >> year;
			Date date_(day, month, year);
			if (!admin.createAFriend(name_1, date_))
			{
				throw "Name already exist. Try again. \nName: ";
			}
			cout << "\nMember was created" << endl;
			break;
		}
		case 2:
		{
			cout << "Name: " << endl;
			getchar();
			getline(cin, name_1);
			if (!admin.createAPage(name_1))
			{
				throw "Name already exist. Try again.";
			}
			cout << "\nMember was created" << endl;
			break;

		}
		case 3:
			if (!(admin.addAStatus(TYPE_FRIEND)))
			{
				throw "Name isn't exist.";
			}
			cout << "\nStatus was added" << endl;
			break;
		case 4:
			if (!(admin.addAStatus(TYPE_PAGE)))
			{
				throw "Name isn't exist.";
			}
			cout << "\nStatus was added" << endl;
			break;
		case 5:
			admin.printAllStatus(TYPE_FRIEND, METHOD_5, name_1);
			break;
		case 6:
			admin.printAllStatus(TYPE_PAGE, METHOD_5, name_1);
			break;
		case 7:
		{
			admin.printFriendsArr();
			cout << "\nName: " << endl;
			getchar();
			getline(cin, name_1);
			admin.printAllStatus(TYPE_FRIEND, METHOD_7, name_1);
			break;
		}
		case 8:
		{
			cout << "Name of the first friend: " << endl;
			getchar();
			getline(cin, name_1);
			cout << "Name of the second friend: " << endl;
			getline(cin, name_2);
			if (name_1 == name_2)
			{
				throw "A friend can't add himself.";
			}
			if (!(admin.LinkMembers(name_1, name_2, TYPE_FRIEND, TYPE_FRIEND)))
			{
				throw "One of the name isn't exist. Try again.";

			}
			//else if ()
			cout << "\nMembers are linked" << endl;
			break;
		}
		case 9:
		{
			cout << "Name of the first friend: " << endl;
			getchar();
			getline(cin, name_1);
			cout << "Name of the second friend: " << endl;
			getchar();
			getline(cin, name_2);
			if (!admin.UnlinkMembers(name_1, name_2, TYPE_FRIEND, TYPE_FRIEND))
			{
				throw "One of the name isn't exist. Try again.";
			}
			cout << "\nMembers are unlinked";
			break;
		}
		case 10:
		{
			cout << "Name of friend: " << endl;
			getchar();
			getline(cin, name_1);
			cout << "\nName of page: " << endl;
			getline(cin, name_2);
			if (!(admin.LinkMembers(name_1, name_2, TYPE_FRIEND, TYPE_PAGE)))
			{
				throw "One of the name isn't exist. Try again.";
			}
			cout << "\nMembers are linked";
			break;
		}

		case 11:
		{
			cout << "Name of friend: ";
			getchar();
			getline(cin, name_1);
			cout << "\nName of page: ";
			getline(cin, name_2);
			if (!(admin.UnlinkMembers(name_1, name_2, TYPE_FRIEND, TYPE_PAGE)))
			{
				throw "\nOne of the name isn't exist. Try again.";
			}
			cout << "\nMembers are unlinked" << endl;
			break;

		}
		case 12:
		{
			admin.printFriendsArr();
			admin.printPagesArr();
			break;

		}
		case 13:
		{
			cout << "Name of friend: " << endl;
			getchar();
			getline(cin, name_1);
			if (!(admin.printFriendsOfFriends(name_1, TYPE_FRIEND)))
			{
				throw "Name isn't exist. Try again.";
			}
			break;
		}
		case 14:
		{
			cout << "Name of page: " << endl;
			getchar();
			getline(cin, name_1);
			if (!admin.printFriendsOfFriends(name_1, TYPE_PAGE))
			{
				throw "Name isn't exist. Try again.";
			}
			break;
		}
		case 15:
		{
			cout << "Name of a friend: ";
			getchar();
			getline(cin, name_1);
			admin.showAllPagesOfAFriend(name_1);
			break;
		}
		case 16:

			admin.exit();
			break;
		default:
			cout << "This method isn't exist" << endl;
			break;
		}
	}
	catch (const char* msg)
	{
		cout << msg << endl;
	}
}
