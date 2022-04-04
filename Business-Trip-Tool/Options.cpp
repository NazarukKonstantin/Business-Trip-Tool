#include "Options.h"

bool canUserContinue(Account& guest)
{
	if (doesAccountHaveAccess(guest) && isLogInSuccessful(guest))
	{
		return true;
	}
	else
	{
		if (!doesAccountHaveAccess(guest) && isLogInSuccessful(guest))
		{
			cout << BAN_CONDITION;
		}
		else if (!doesAccountHaveAccess(guest) && !isLogInSuccessful(guest))
		{
			cout << WAIT_4_CONFIRMATION;
		}
	}
	return false;
}

void processTripFile(vector <Trip_Man>& emp,bool is_file_open,bool& exit_token)
{
	readTripFile(emp, is_file_open);
	if (!is_file_open)
	{
		cout << NO_FILE_ACCESS;
		char choice = _getch();
		if (choice == '2')
		{
			exit_token = true;
			return;
		}
		while (true)
		{
			Trip_Man temp;
			cout << ENTER_SURNAME;
			getline(cin, temp.surname);
			cout << ENTER_NAME;
			getline(cin, temp.name);
			cout << ENTER_PATRONYMIC;
			checkPatronymic(temp);
			cout << ENTER_YEAR;
			cin >> temp.year;
			cout << ENTER_MONTH;
			getline(cin, temp.month);
			cout << ENTER_DAYS;
			cin >> temp.trip_length;
			cout << ENTER_MONEY;
			cin >> temp.money_per_day;
			cout << ENTER_TOWN;
			getline(cin, temp.town);
			emp.push_back(temp);
			cout << WANT_STOP;
			string choice;
			getline(cin, choice);
			if (choice == "1" || choice == "ƒј" || choice == "да" || choice == "ƒа") break;
		}
	}
}
void checkPatronymic(Trip_Man& temp)
{
	getline(cin, temp.patronymic);
	while (true)
	{
		if (temp.patronymic == "No" || temp.patronymic == "no" || temp.patronymic == "nO" || temp.patronymic == "NO")
		{
			temp.patronymic = "-";
			break;
		}
		else
		{
			cout << YOU_SURE;
			char sure = _getch();
			if (sure == '1')
			{
				getline(cin, temp.patronymic);
				break;
			}
		}
	}
}
void readTripFile(vector <Trip_Man> emp, bool& is_file_open)
{
	int amount_of_employees = countStructuresInTripFile(is_file_open);
	if (is_file_open)
	{
		emp.reserve(amount_of_employees);						// резервируетс€ пам€ть под массив работников
		ifstream f_in(TRIP_INFO, ios::in);						// открывает файл в режиме чтени€
		while (!f_in.eof())
		{
			Trip_Man temp;
			f_in >> temp.surname >> temp.name >> temp.patronymic >> temp.year
				>> temp.month >> temp.trip_length >> temp.money_per_day>> temp.town ;
			emp.push_back(temp);
		}
		f_in.close();
	}
}
int countStructuresInTripFile(bool& is_file_open)
{
	ifstream fin(TRIP_INFO, ios::in);
	int amount_of_employees = 0;							//кол-во работников в массиве, считываемом из файла
	if (fin.is_open())
	{
		string temp;
		while (getline(fin, temp))						//считывает текстовый файл построчно
		{
			amount_of_employees++;						//если удалось считать строку, инкриментирует кол-во работников
		}
	}
	else
	{
		is_file_open = false;
		fin.close();
		return 0;
	}
	fin.close();
	return amount_of_employees;
}
void writeEndTripFile(Trip_Man new_emp)
{
	ofstream f_add(ACCOUNT_FILE_NAME, ios::app);			// открывает файл дл€ дозаписи
	f_add << endl;
	f_add << new_emp.surname << " "
		<< new_emp.name << " "
		<< new_emp.patronymic << " "
		<< new_emp.year << " "
		<< new_emp.month<< " "
		<< new_emp.trip_length<<" "
		<< new_emp.money_per_day<<" "
		<< new_emp.town;
	f_add.close();
}
void writeTripFile(vector<Trip_Man> emp)
{
	int vec_size = emp.size();
	ofstream fout(TRIP_INFO, ios::out);
	for (int i = 0; i < vec_size; i++)
	{
		fout << emp.at(i).surname << " " <<
			emp.at(i).name << " " <<
			emp.at(i).patronymic << " " <<
			emp.at(i).year << " " <<
			emp.at(i).month<<" "<<
			emp.at(i).trip_length<<" "<<
			emp.at(i).money_per_day<<" "<<
			emp.at(i).town;
		if (i < vec_size - 1)
		{
			fout << endl;
		}
	}
	fout.close();
}

void processMenu(Account guest)
{
	cout << MAIN_MENU;
	char main_menu_choice=_getch();
	switch (main_menu_choice)
	{
	case '1': guest.role == 1 ? cout << ACCOUNT_MENU_ROLE_1 : cout << ACCOUNT_MENU_ROLE_0;
	case '2': guest.role == 1 ? cout << TRIP_MENU_ROLE_1 : cout << TRIP_MENU_ROLE_0;
	case '0': return;
	}
	char sub_menu_choice = _getch();
	switch (sub_menu_choice)
	{
	case '1':
	}


}