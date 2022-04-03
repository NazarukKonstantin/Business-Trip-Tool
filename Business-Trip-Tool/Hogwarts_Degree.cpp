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

	vector <Account> acc;								//массив аккаунтов
	readAccountFile(acc);

	return 0;
}
