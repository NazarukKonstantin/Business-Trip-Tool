#include "Accounts.h"
#include <windows.h>
#include "Options.h"

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "RUS");

	vector <Account> acc;								//массив аккаунтов
	Account guest;
	bool exit_token = false;
	readAccountFile(acc);
	showOptionsOnEnter(acc, guest,exit_token);
	if (canUserContinue(guest, exit_token))
	{
		vector <Trip_Man> emp;
		bool is_file_open = true;
		processTripFile(emp, is_file_open, exit_token);
		if (!exit_token)
		{
			do
			{
				processMainMenu(emp, acc, guest);
				writeTripFile(emp);
			} while (!wantToGoBack());
		}
	}
	return 0;
}