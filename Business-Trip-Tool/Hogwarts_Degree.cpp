#include "Hogwarts_Degree.h"
#include "Accounts.h"
#include <windows.h>
#include "Common_Tools.h"
#include "Options.h"


int magic()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "RUS");

	vector <Account> acc;								//������ ���������
	Account guest;
	readAccountFile(acc);
	showOptionsOnEnter(acc,guest);
	if (canUserContinue(guest))
	{
		vector <Trip_Man> emp;
		bool is_file_open = true;
		bool exit_token = false;
		processTripFile(emp,is_file_open,exit_token);
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