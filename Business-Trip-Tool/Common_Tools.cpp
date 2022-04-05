#include "Common_Tools.h"

bool wantToGoBack()
{
	cout << GO_BACK_QUESTION;
	int choice = 0;
	cin >> choice;
	if (choice == 1)
	{
		return true;
	}
	return false;
}

string check4TooBigString(int limit)
{
	string temp;
	getline(cin, temp);
	if (temp.size() > limit)
	{
		cout << TOO_BIG_STRING;
		getline(cin, temp);
	}
	return temp;
}