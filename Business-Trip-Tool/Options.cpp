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

void enterEmployee(vector <Trip_Man>& emp)
{
	while (true)
	{
		Trip_Man temp;
		cout << ENTER_SURNAME;
		temp.surname = check4TooBigString(F_I_O_LINE_LIMIT);
		cout << ENTER_NAME;
		temp.name = check4TooBigString(F_I_O_LINE_LIMIT);
		cout << ENTER_PATRONYMIC;
		checkPatronymic(temp);
		cout << ENTER_YEAR;
		string tempor_year;
		temp.year = stoi(tempor_year = check4TooBigString(YEAR_LINE_LIMIT));
		cout << ENTER_MONTH;
		temp.month=check4TooBigString(MONTH_LINE_LIMIT);
		cout << ENTER_DAYS;
		string tempor_days;
		temp.trip_length = stoi(tempor_days = check4TooBigString(DAYS_LINE_LIMIT));
		cout << ENTER_MONEY;
		string tempor_money;
		temp.money_per_day = stoi(tempor_money = check4TooBigString(MONEY_LINE_LIMIT));
		cout << ENTER_TOWN;
		temp.town = check4TooBigString(TOWN_LINE_LIMIT);
		emp.push_back(temp);
		cout << WANT_STOP;
		string choice;
		getline(cin, choice);
		if (choice == "1" || choice == "ДА" || choice == "да" || choice == "Да"
		|| choice == "YES" || choice == "YEs" || choice == "yES" || choice == "Yes" || choice == "yEs"
		|| choice == "yeS" || choice == "yes") break;
	}
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
		enterEmployee(emp);
	}
}
void checkPatronymic(Trip_Man& temp)
{
	getline(cin, temp.patronymic);
	while (true)
	{
		if (temp.patronymic == "No" || temp.patronymic == "no" || temp.patronymic == "nO" || temp.patronymic == "NO"
			||temp.patronymic == "НЕТ" || temp.patronymic == "Нет" || temp.patronymic == "нет" || temp.patronymic == "НЕт"
			||temp.patronymic == "нЕТ" || temp.patronymic == "нЕт" || temp.patronymic == "неТ")
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
				temp.patronymic = check4TooBigString(F_I_O_LINE_LIMIT);
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
		emp.reserve(amount_of_employees);						// резервируется память под массив работников
		ifstream f_in(TRIP_INFO, ios::in);						// открывает файл в режиме чтения
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
	ofstream f_add(ACCOUNT_FILE_NAME, ios::app);			// открывает файл для дозаписи
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

void processMainMenu(vector<Account>& acc, Account& guest)
{
	cout << MAIN_MENU;
	char main_menu_choice=_getch();
	switch (main_menu_choice)
	{
	case '1': processAccountMenu(acc,guest);
	case '2': processTripMenu(guest);
	case '0': return;
	}
}
void processAccountMenu(vector<Account>& acc, Account& guest)
{
	do
	{
		guest.role == 1 ? cout << ACCOUNT_MENU_ROLE_1 : cout << ACCOUNT_MENU_ROLE_0;
		char choice = _getch();
		if (guest.role == 1)
		{
			switch (choice)
			{
			case '2': showAccountArray(acc); break;
			case '3': addAccountInArray(acc, guest); break;
			case '4': pickAccountInArray(acc, editAccountInArray); break;
			case '5': pickAccountInArray(acc, deleteAccountInArray); break;
			}
		}
		switch (choice)
		{
		case'1': changeLogin(acc, guest); break;
		case'0': return;
		}
	} while (!wantToGoBack());
}
void processTripMenu(vector<Trip_Man> emp, Account guest)
{
	do
	{
		guest.role == 1 ? cout << TRIP_MENU_ROLE_1 : cout << TRIP_MENU_ROLE_0;
		char choice = _getch();
		if (guest.role == 1 && choice == '6')
		{
			processDataChangeMenu();
		}
		switch (choice)
		{
		case '1': showTripArray(emp); break;
		case '2':
		case '3':
		case '4':
		case '5':
		case '0': return;
		}
	} while (!wantToGoBack());
}
void processDataChangeMenu()
{
	do
	{
		cout << DATA_CHANGE_MENU_ROLE_1;
		char choice = _getch();
		switch (choice)
		{
		case '1': 
		case '2':
		case '3':
		case '0': return;
		}
	} while (!wantToGoBack());
}

void showTripArray(vector<Trip_Man>emp)
{
	int vec_size = emp.size();
	cout << TABLE_TRIP_HEADER;

	for (int curr_emp = 0; curr_emp < vec_size; curr_emp++)
	{
		string blank_year(YEAR_LINE_LIMIT, ' '), blank_month(MONTH_LINE_LIMIT, ' '), blank_days(DAYS_LINE_LIMIT, ' '), blank_money(MONEY_LINE_LIMIT, ' '), blank_town(TOWN_LINE_LIMIT, ' ');
		string emp_divider(TABLE_TRIP_HEADER.size() - 3, '-');
		string surname_temp_length(F_I_O_LINE_LIMIT - emp[curr_emp].surname.size(),' ');
		string name_temp_length(F_I_O_LINE_LIMIT - emp[curr_emp].name.size(),' ');
		string year_temp_length(YEAR_LINE_LIMIT-to_string(emp[curr_emp].year).size(), ' ');
		string month_temp_length(MONTH_LINE_LIMIT-emp[curr_emp].month.size(), ' ');
		string days_temp_length(DAYS_LINE_LIMIT-to_string(emp[curr_emp].trip_length).size(), ' ');
		string money_temp_length(MONEY_LINE_LIMIT-to_string(emp[curr_emp].money_per_day).size(), ' ');
		string town_temp_length(TOWN_LINE_LIMIT - emp[curr_emp].town.size(), ' ');

		cout << "|" << emp[curr_emp].surname << surname_temp_length
			<< "|" << emp[curr_emp].year << year_temp_length
			<< "|" << emp[curr_emp].month << money_temp_length
			<< "|" << emp[curr_emp].trip_length << days_temp_length
			<< "|" << emp[curr_emp].money_per_day << money_temp_length
			<< "|" << emp[curr_emp].town << town_temp_length << endl
			<< "|" << emp[curr_emp].name << name_temp_length
			<< "|" << blank_year << "|" << blank_month << "|" << blank_days << "|" << blank_money << "|" << blank_town << endl;

		if (emp[curr_emp].patronymic != "-")
		{
			string patronymic_temp_length(F_I_O_LINE_LIMIT - emp[curr_emp].patronymic.size(), ' ');
			cout << "|" << emp[curr_emp].patronymic << patronymic_temp_length
				 << "|" << blank_year << "|" << blank_month << "|" << blank_days << "|" << blank_money << "|" << blank_town << endl;
		}
		cout << "|" << emp_divider << "|\n";
	}
}

//void addAccountInArray(vector<Account>& acc, Account& guest)
//{
//	cout << ROLE;
//	int role_choice = 0;
//	cin >> role_choice;
//	cout << ACCESS;
//	int access_choice = 0;
//	if (access_choice == 1 && role_choice == 1)
//	{
//		signUp(acc, adminCase, guest);
//	}
//	else if (access_choice == 2 && role_choice == 1)
//	{
//		signUp(acc, blockedAdminCase, guest);
//	}
//	else if (access_choice == 1 && role_choice == 2)
//	{
//		signUp(acc, userCase, guest);
//	}
//	else if (access_choice == 2 && role_choice == 2)
//	{
//		signUp(acc, newAccCase, guest);
//	}
//}
//void pickAccountInArray(vector<Account> acc, void (*changeAccount)(vector<Account>& acc, int acc_num))
//{
//	int counter = 0;
//	searchAccount(acc);
//	cout << CHOOSE_TO_EDIT;
//	int choice = 0;
//	cin >> choice;
//	while (choice > counter)
//	{
//		cout << ERROR_INPUT;
//		cin >> choice;
//	}
//	int vec_size = acc.size();
//	for (int acc_num = 0; acc_num < vec_size; acc_num++)
//	{
//		if (choice == acc[acc_num].search_counter)
//		{
//			changeAccount(acc, acc_num);
//			break;
//		}
//	}
//}
//void editAccountInArray(vector<Account>& acc, int acc_num)
//{
//	int access_choice = 0;
//	int role_choice = 0;
//	cout << EDIT_MENU;
//	int choice = 0;
//	cin >> choice;
//	cout << YOU_SURE;
//	char sure;
//	sure = _getch();
//	if (sure == '1')
//	{
//		switch (choice)
//		{
//		case 1:
//			cout << LOGIN_REQUEST;
//			getline(cin, acc[acc_num].login);
//			while (!isLoginUnique(acc, acc[acc_num].login))
//			{
//				cout << EXISTING_LOGIN_ERROR;
//				getline(cin, acc[acc_num].login);
//			} break;
//		case 2:
//			if (acc[acc_num].active)
//			{
//				cout << DONT_CHANGE_YOUR_ROLE;
//				break;
//			}
//			cout << ROLE;
//			cin >> role_choice;
//			if (role_choice == 1) { acc[acc_num].role = 1; }; break;
//		case 3:
//			if (acc[acc_num].active)
//			{
//				cout << DONT_CHANGE_YOUR_ACCESS;
//				break;
//			}
//			cout << ACCESS;
//			if (access_choice == 1) { acc[acc_num].access = 1; }; break;
//		case 0: break;
//		}
//	}
//	writeAccountFile(acc);
//}
//void searchAccount(vector<Account>& acc)
//{
//	cout << TO_EDIT;
//	string search_to_edit, temp_role, temp_access;
//	getline(cin, search_to_edit);
//	int amount_of_accounts = acc.size();
//	int search_size = search_to_edit.size();
//	cout << "--№--|" << TABLE_ACCOUNTS_HEADER;
//	for (int current_account = 0; current_account < amount_of_accounts; current_account++)
//	{
//		for (int current_letter = 0; current_letter < search_size; current_letter++)
//		{
//			if (search_to_edit[current_letter] != acc[current_account].login[current_letter])
//			{
//				break;
//			}
//			roleAccessConverter(acc, current_account, temp_role, temp_access);
//			string temp_4_login(LOGIN_LENGTH_LIMIT - acc[current_account].login.size(), ' ');
//			string role_length(ROLE_LENGTH - temp_role.size(), ' ');
//			string access_length(ACCESS_LENGTH - temp_access.size(), ' ');
//			string counter_length(5 - to_string(acc[current_account].search_counter).size(), ' ');
//			cout << counter_length << acc[current_account].search_counter++ << "|" << acc[current_account].login << temp_4_login << "|" <<
//				temp_role << role_length << "|" << temp_access << access_length << "|\n";
//		}
//	}
//}
//void deleteAccountInArray(vector<Account>& acc, int acc_num)
//{
//	cout << YOU_SURE;
//	char sure;
//	sure = _getch();
//	if (sure == '1')
//	{
//		acc.erase(acc.begin() + acc_num);
//	}
//	writeAccountFile(acc);
//}