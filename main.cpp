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
#define SHOW_STATUSES_METHOD 5
#define SHOW_LAST_STATUSES_METHOD 7


void Method(Admin& admin, int choose);
void showMenu(Admin& admin);
Admin readFile(ifstream& inFile);
void getFriendArr(bool* flag, ifstream& inFile, char delimeter1, char delimeter2, int i, Admin& newAdmin);
void getPageArr(bool* flag, ifstream& inFile, char delimeter1, char delimeter2, int i, Admin& newAdmin);
void linkMembers(Admin& newAdmin, ifstream& inFile, char delimeter1, char delimeter2);
void showWelcome();
void showTitle(int methodNumber);

int main()
{
		// Creating local admin.
		Admin admin;

		ifstream inFile;
		inFile.open("recent_run_data.txt");
		admin = readFile(inFile);

		int choose = ZERO;
		showWelcome();
		while (choose != EXIT)
		{
			showMenu(admin);
			cin >> choose;
			Method(admin, choose);
		}
		inFile.close(); // Close file
	return 0;
}

void showWelcome()
{
	cout << "	 __          __  _                            _          ______             _                 _    \n";
	cout << "	 \\ \\        / / | |                          | |        |  ____|           | |               | |   \n";
	cout << "	  \\ \\  /\\  / /__| | ___ ___  _ __ ___   ___  | |_ ___   | |__ __ _  ___ ___| |__   ___   ___ | | __\n";
	cout << "	   \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\  |  __/ _` |/ __/ _ \\ '_ \\ / _ \\ / _ \\| |/ /\n";
	cout << "	    \\  /\\  /  __/ | (_| (_) | | | | | |  __/ | || (_) | | | | (_| | (_|  __/ |_) | (_) | (_) |   < \n";
	cout << "	     \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|  \\__\\___/  |_|  \\__,_|\\___\\___|_.__/ \\___/ \\___/|_|\\_\\ \n\n\n";

}

Admin readFile(ifstream& inFile)
{
	Admin newAdmin;
	int numOfFriends, numOfpages;
	
	char delimeter1 = ' ';
	char delimeter2 = '\n';
	inFile >> numOfFriends >> numOfpages;
	bool flag = true;
	for (int i = 0; i < numOfFriends; i++) // Adding per a friend
	{
		getFriendArr(&flag, inFile, delimeter1, delimeter2, i, newAdmin);
		
	}
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
	string name1, name2, ch;
	int linksBTWfriends, linkBTWpages, k;
	inFile >> linksBTWfriends >> linkBTWpages;
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
	string name,status, ch;
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
	cout << "					  __  __                            \n";
	cout << "					 |  \\/  |                         _ \n";
	cout << "					 | \\  / |   ___   _ __    _   _  (_) \n";
	cout << "					 | |\\/| |  / _ \\ | '_ \\  | | | |    \n";
	cout << "					 | |  | | |  __/ | | | | | |_| |  _ \n";
	cout << "					 |_|  |_|  \\___| |_| |_|  \\__,_| (_) \n\n";

	cout << "			  	   Please select an option from the menu below::\n" << endl << 
	"1.  Create a new friend." << endl <<//											(no. 1)
	"2.  Create a fan page." << endl <<//											(no. 2)
	"3.  Add a status update to a friend." << endl <<//								(no. 3)
	"4.  Add a status update to a fan page." << endl <<//							(no. 3)
	"5.  Display all status updates of a friend." << endl <<//						(no. 4)
	"6.  Display all status updates of a fan page." << endl << //					(no. 4)
	"7.  Display the last 10 status updates of friends of a member." << endl << //	(no. 5)
	"8.  Establish a link between two friends." << endl << //						(no. 6)
	"9.  Cancel link between two friends." << endl << //							(no. 7)
	"10. Link a fan to a fan page." << endl << //									(no. 8)
	"11. Cancel link between a friend and a fan page." << endl << //				(no. 9)
	"12. Display all members (friends and fan pages)." << endl << //				(no. 10)
	"13. Display all friends of a specific friend." << endl << //					(no. 11)
	"14. Display all fans of a specific fan page." << endl << //					(no. 11)
	"15. Display all fan pages that a friend has joined." << endl <<
	"16. Exit the program." << endl; //												(no. 12)
}

void Method(Admin& admin, int choose) noexcept(false)
{
	try
	{
		string name_1;
		string name_2;
		int day, month, year;
		showTitle(choose);
		switch (choose)
		{
		case 1:
		{
			cout << "Enter name:" << endl;

			getchar();
			getline(cin, name_1);
			cout << "Enter a date in format: DD MM YYYY (For example: 31 12 1998)" << endl;

			cin >> day >> month >> year;
			Date date_(day, month, year);
			if (!admin.createAFriend(name_1, date_))
			{
				throw "Name already exist. Try again. \nName: ";
			}
			cout << "  ________________________" << endl;
			cout << " /                        \\" << endl;
			cout << "|     Member was created   |" << endl;
			cout << " \\________________________/" << endl;

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
			admin.printAllStatus(TYPE_FRIEND, SHOW_STATUSES_METHOD, name_1, &admin);
			break;
		case 6:
			admin.printAllStatus(TYPE_PAGE, SHOW_STATUSES_METHOD, name_1, &admin);
			break;
		case 7:
		{
			admin.printFriendsArr();
			cout << "\nName: " << endl;
			getchar();
			getline(cin, name_1);
			admin.printAllStatus(TYPE_FRIEND, SHOW_LAST_STATUSES_METHOD, name_1, &admin);
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

void showTitle(int methodNumber)
{
	switch (methodNumber)
	{
	case 1:
	{
		cout << endl << "					-----------------------------------" << endl;
		cout << "					|                                 |" << endl;
		cout << "					|        Create a new user        |" << endl;
		cout << "					|                                 |" << endl;
		cout << "					-----------------------------------" << endl << endl;
		break;
	}
	case 2: {
		cout << endl << "					-----------------------------------" << endl;
		cout << "					|                                 |" << endl;
		cout << "					|      Create a new fan page      |" << endl;
		cout << "					|                                 |" << endl;
		cout << "					-----------------------------------" << endl << endl;
		break;
	}
	case 3: {
		cout << endl << "					-----------------------------------" << endl;
		cout << "					|                                 |" << endl;
		cout << "					|     Add a status to a friend    |" << endl;
		cout << "					|                                 |" << endl;
		cout << "					-----------------------------------" << endl << endl;
		break;
	}
	case 4: {
		cout << endl << "					-----------------------------------" << endl;
		cout << "					|                                 |" << endl;
		cout << "					|    Add a status to a fan page   |" << endl;
		cout << "					|                                 |" << endl;
		cout << "					-----------------------------------" << endl << endl;
		break;
	}
	case 8: {
		cout << endl << "					-----------------------------------" << endl;
		cout << "					|                                 |" << endl;
		cout << "					|       Link between friends      |" << endl;
		cout << "					|                                 |" << endl;
		cout << "					-----------------------------------" << endl << endl;
		break;
	}
	case 9: {
		cout << endl << "					-----------------------------------" << endl;
		cout << "					|                                 |" << endl;
		cout << "					|   Cancel link between friends   |" << endl;
		cout << "					|                                 |" << endl;
		cout << "					-----------------------------------" << endl << endl;
		break;
	}
	case 10: {
		cout << endl << "					-----------------------------------" << endl;
		cout << "					|                                 |" << endl;
		cout << "					|   Link a friend to a fan page   |" << endl;
		cout << "					|                                 |" << endl;
		cout << "					-----------------------------------" << endl << endl;
		break;
	}
	case 11: {
		cout << endl << "					-----------------------------------" << endl;
		cout << "					|                                 |" << endl;
		cout << "					|     Cancel link  between a      |" << endl;
		cout << "					|     friend and a fan page       |" << endl;
		cout << "					|                                 |" << endl;
		cout << "					-----------------------------------" << endl << endl;
		break;
	}
	case 16:
	{
		cout << endl << "					-----------------------------------" << endl;
		cout << "					|                                 |" << endl;
		cout << "					|   Data has saved - Bye bye      |" << endl;
		cout << "					|                                 |" << endl;
		cout << "					-----------------------------------" << endl << endl;
		break;
	}
	default:
		break;
	}
}