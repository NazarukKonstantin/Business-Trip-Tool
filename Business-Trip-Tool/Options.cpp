#include "Options.h"

bool canUserContinue(Account& guest, bool exit_token)
{
	if (doesAccountHaveAccess(guest) && isLogInSuccessful(guest))
	{
		return true;
	}
	else
	{
		if (!doesAccountHaveAccess(guest) && !areYouNew(guest))
		{
			cout << BAN_CONDITION;
		}
		else if (!doesAccountHaveAccess(guest) && areYouNew(guest))
		{
			if(!exit_token)
			cout << WAIT_4_CONFIRMATION;
		}
	}
	return false;
}

void enterEmployees(vector <Trip_Man>& emp)
{
	while (true)
	{
		Trip_Man temp;
		enter1Employee(temp);
		emp.push_back(temp);
		cout << WANT_STOP;
		string choice;
		choice = justEnterString();
		int choice_size = choice.size();
		for (int curr_char = 0; curr_char < choice_size; curr_char++)
		{
			choice.at(curr_char) = tolower(choice.at(curr_char));
		}
		if (choice == "1" || choice == "да" || choice == "yes") break;
	}
}
void enter1Employee(Trip_Man& temp)
{
	cout << ENTER_SURNAME;
	inputSurname(temp);
	cout << ENTER_NAME;
	inputName(temp);
	cout << ENTER_PATRONYMIC;
	inputPatronymic(temp);
	cout << ENTER_YEAR;
	inputYear(temp);
	cout << ENTER_MONTH;
	inputMonth(temp);
	cout << ENTER_DAYS;
	inputDays(temp);
	cout << ENTER_MONEY;
	inputMoney(temp);
	cout << ENTER_CURRENCY;
	inputCurrency(temp);
	cout << ENTER_TOWN;
	inputTown(temp);
}

void processTripFile(vector <Trip_Man>& emp,bool is_file_open,bool& exit_token)
{
	readTripFile(emp, is_file_open);
	if (!is_file_open)
	{
		cout << NO_FILE_ACCESS;
		int choice = inputIntNumbers(1, 2);
		if (choice == 2)
		{
			exit_token = true;
			return;
		}
		enterEmployees(emp);
	}
}
void checkPatronymic(Trip_Man& temp)
{
	temp.patronymic = check4TooBigString(F_I_O_LINE_LIMIT,TOO_BIG_STRING,onlyLettersInput);
	while (true)
	{
		string tempor = temp.patronymic;
		int tempor_size = tempor.size();
		for (int curr_char = 0; curr_char <tempor_size; curr_char++)
		{
			tempor.at(curr_char) = tolower(tempor.at(curr_char));
		}
		if (tempor == "no" || temp.patronymic == "нет")
		{
			temp.patronymic = "-";
			break;
		}
		else
		{
			cout << YOU_SURE;
			int sure = inputIntNumbers(1, 2);
			if (sure == 1)
			{
				temp.patronymic = check4TooBigString(F_I_O_LINE_LIMIT, TOO_BIG_STRING, onlyLettersInput);
				break;
			}
		}
	}
}

void readTripFile(vector <Trip_Man>& emp, bool& is_file_open)
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
				>> temp.month >>temp.month_num>> temp.trip_length >> temp.money_per_day
				>>temp.currency>>temp.town ;
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
		<< new_emp.month_num<<" "
		<< new_emp.trip_length<<" "
		<< new_emp.money_per_day<<" "
		<< new_emp.currency<<" "
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
			emp.at(i).month_num<<" "<<
			emp.at(i).trip_length<<" "<<
			emp.at(i).money_per_day<<" "<<
			emp.at(i).currency<<" "<<
			emp.at(i).town;
		if (i < vec_size - 1)
		{
			fout << endl;
		}
	}
	fout.close();
}

void processMainMenu(vector <Trip_Man>& emp, vector<Account>& acc, Account& guest)
{
	cout << MAIN_MENU;
	int main_menu_choice = inputIntNumbers(0, 2);
	switch (main_menu_choice)
	{
	case 1: processAccountMenu(acc, guest);
	case 2: processTripMenu(emp, guest);
	case 0: return;
	}
}
void processAccountMenu(vector<Account>& acc, Account& guest)
{
	do
	{
		guest.role == 1 ? cout << ACCOUNT_MENU_ROLE_1 : cout << ACCOUNT_MENU_ROLE_0;
		int choice = inputIntNumbers(0, 5);
		if (guest.role == 1)
		{
			switch (choice)
			{
			case 2: showAccountArray(acc); break;
			case 3: addAccountInArray(acc, guest); break;
			case 4: pickAccountInArray(TO_EDIT,CHOOSE_TO_EDIT,acc, editAccountMenu); break;
			case 5: pickAccountInArray(TO_DELETE,CHOOSE_TO_DELETE,acc, deleteAccountInArray); break;
			}
		}
		switch (choice)
		{
		case 1: changeLogin(acc, guest); break;
		case 0: return;
		}
	} while (!wantToGoBack());
}
void processTripMenu(vector<Trip_Man> emp, Account guest)
{
	do
	{
		int useless_counter = 0;
		guest.role == 1 ? cout << TRIP_MENU_ROLE_1 : cout << TRIP_MENU_ROLE_0;
		int choice = inputIntNumbers(0, 6);
		if (guest.role == 1 && choice == 6)
		{
			processDataChangeMenu(emp);
		}
		switch (choice)
		{
		case 1: showTripArray(emp); break;
		case 2: countMoney4MonthX(emp); break;
		case 3: sortTowns(emp); break;
		case 4: searchMenu(emp,useless_counter); break;
		case 5: sortMenu(emp); break;
		case 0: return;
		}
	} while (!wantToGoBack());
}
void processDataChangeMenu(vector<Trip_Man>& emp)
{
	do
	{
		cout << DATA_CHANGE_MENU_ROLE_1;
		int choice = inputIntNumbers(0,3);
		switch (choice)
		{
		case 1: addData(emp); break;
		case 2: pickDataInArray(CHOOSE_TO_EDIT,emp,editDataMenu); break;
		case 3: pickDataInArray(CHOOSE_TO_DELETE,emp,deleteData); break;
		case 0: return;
		}
	} while (!wantToGoBack());
}

void showTripArray(vector<Trip_Man>emp)
{
	int vec_size = emp.size();
	cout << TABLE_TRIP_HEADER;
	for (int curr_emp = 0; curr_emp < vec_size; curr_emp++)
	{
		showOneEmployee(emp, curr_emp);
	}
}
void showOneEmployee(vector<Trip_Man>emp, int curr_emp)
{
	string blank_year(YEAR_LINE_LIMIT, ' '), blank_month(MONTH_LINE_LIMIT, ' '), blank_days(DAYS_LINE_LIMIT, ' '), blank_money(MONEY_LINE_LIMIT, ' '), blank_town(TOWN_LINE_LIMIT, ' ');
	string emp_divider(TABLE_TRIP_HEADER.size() - 3, '-');
	string surname_temp_length(F_I_O_LINE_LIMIT - emp[curr_emp].surname.size(), ' ');
	string name_temp_length(F_I_O_LINE_LIMIT - emp[curr_emp].name.size(), ' ');
	string year_temp_length(YEAR_LINE_LIMIT - to_string(emp[curr_emp].year).size(), ' ');
	string month_temp_length(MONTH_LINE_LIMIT - emp[curr_emp].month.size(), ' ');
	string days_temp_length(DAYS_LINE_LIMIT - to_string(emp[curr_emp].trip_length).size(), ' ');
	string money_temp_length(MONEY_LINE_LIMIT + CURRENCY_LIMIT - to_string(emp[curr_emp].money_per_day).size() - emp[curr_emp].currency.size(), ' ');
	string town_temp_length(TOWN_LINE_LIMIT - emp[curr_emp].town.size(), ' ');

	cout << "|" << emp[curr_emp].surname << surname_temp_length
		<< "|" << emp[curr_emp].year << year_temp_length
		<< "|" << emp[curr_emp].month << money_temp_length
		<< "|" << emp[curr_emp].trip_length << days_temp_length
		<< "|" << emp[curr_emp].money_per_day << emp[curr_emp].currency << money_temp_length
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
void countMoney4MonthX(vector<Trip_Man> emp)
{
	cout << ENTER_MONTH;
	string input_month=check4TooBigString(MONTH_LINE_LIMIT,TOO_BIG_STRING,onlyLettersInput);
	vector<Month_Money> value;
	Month_Money temp;
	int amount_of_emp = emp.size();
	for (int curr_emp = 0; curr_emp < amount_of_emp; curr_emp++)
	{
		if (input_month == emp[curr_emp].month)
		{
			temp.money_per_day = emp[curr_emp].money_per_day;
			temp.currency = emp[curr_emp].currency;
			value.push_back(temp);
		}
	}
	cout << MONEY_RES << countMoney(value)<<endl;
}
string countMoney(vector<Month_Money> value)
{
	double currency_sum = 0;
	string result;
	int value_size = value.size();
	for (int curr_mon = 0; curr_mon < value_size-1; curr_mon++)
	{
		if (value[curr_mon].unique == true)
		{
			value[curr_mon].unique = false;
			currency_sum = value[curr_mon].money_per_day;
			for (int next_mon = curr_mon + 1; next_mon < value_size; next_mon++)
			{
				if (value[curr_mon].currency == value[next_mon].currency)
				{
					currency_sum += value[next_mon].money_per_day;
					value[next_mon].unique = false;
				}
			}
			result += to_string(currency_sum) + value[curr_mon].currency + " ";
		}
	}
	if (value[value_size-1].unique == true)
	{
		result += to_string(value[value_size - 1].money_per_day) + value[value_size - 1].currency;
	}
	return result;
}

void sortTowns(vector<Trip_Man> emp)
{
	string month_x, month_y;
	int year_x=0, year_y=0;
	int X = 0, Y = 0;
	cout << ENTER_MONTH_X;
	X = enterMonth(ENTER_MONTH_X, month_x);
	cout << ENTER_YEAR;
	year_x = inputIntNumbers(YEAR_LINE_LIMIT);
	Y = enterMonth(ENTER_MONTH_Y, month_y);
	cout << ENTER_YEAR;
	year_y = inputIntNumbers(YEAR_LINE_LIMIT);
	if (year_x > year_y) swap(year_x, year_y);
	vector<Town_Frequency> town_set, picked_towns;
	fillTowns2SortArray(town_set, emp, year_x, year_y, X, Y);
	writeTownsInSortArray(town_set, picked_towns);
	sort(picked_towns.begin(), picked_towns.end(), sortByFrequency);
	showSortedTowns(picked_towns, X, Y,year_x,year_y,emp);
}

int enterMonth(string message, string& month)
{
	while (true)
	{
		cout << message;
		(cin >> month).get();
		int str_size = month.size();
		int counter = 0;
		for (int curr_symb = 0; curr_symb < str_size; curr_symb++)
		{
			if (isdigit(month[curr_symb]))
			{
				counter++;
			}
		}
		if (counter == str_size)
		{
			return stoi(month);
		}
		else if (!counter)
		{
			int temp = convertMonthName2Number(month, str_size);
			if (!temp)
			{
				continue;
			}
			return temp;
		}
		else
		{
			cout << WRONG_MONTH;
		}
	}
}
int convertMonthName2Number(string month, int str_size)
{
	while (true)
	{
		for (int curr_symb = 0; curr_symb < str_size; curr_symb++)
		{
			month[curr_symb]=tolower(month[curr_symb]);
		}
		month[0] = toupper(month[0]);
		switch (month[0])
		{
		case 'S': case 'С': return 9;
		case 'O': case 'О': return 10;
		case 'N': case 'Н': return 11;
		case 'D': case 'Д': return 12;
		case 'F': case 'Ф': return 2;
		case 'M': case 'М': switch (month[2]) { case 'r': case'p': return 3; case'у': case'й': return 5; }
		case 'A': case 'А': switch (month[1]) { case 'p': case'п': return 4; case'u': case'в': return 8; }
		case 'J': switch (month[3]) { case 'u': return 1; case 'e': return 6; case'y': return 7; }
		case 'Я': return 1;
		case 'И': switch (month[2]) { case'н': return 6; case'л':return 7; }
		default: cout << WRONG_MONTH; return 0;
		}
	}
}
void fillTowns2SortArray(vector<Town_Frequency>& town_set,vector<Trip_Man> emp, int year_x, int year_y, int X, int Y)
{
	Town_Frequency temp;
	int emp_size = emp.size();
	if (year_x != year_y)
	{
		for (X; X <= 12; X++)
		{
			write1TownInTownSet(emp, town_set, temp, emp_size, X, year_x);
		}
		while(year_x!=year_y)
		{
			for (X = 1; X <= 12; X++)
			{
				write1TownInTownSet(emp, town_set, temp, emp_size, X, year_x);
			}
			year_x++;
		}
	}
	for (X = 1; X <= Y; X++)
	{
		write1TownInTownSet(emp, town_set, temp, emp_size, X, year_x);
	}
}
void write1TownInTownSet(vector<Trip_Man> emp, vector<Town_Frequency>& town_set, Town_Frequency temp, int emp_size, int X, int year_x)
{
	for (int curr_emp = 0; curr_emp < emp_size; curr_emp++)
	{
		if (emp[curr_emp].year == year_x && emp[curr_emp].month_num == X)
		{
			temp.town = emp[curr_emp].town;
			town_set.push_back(temp);
		}
	}
}
void writeTownsInSortArray(vector<Town_Frequency> town_set, vector<Town_Frequency>& picked_towns)
{
	Town_Frequency temp;
	int set_size = town_set.size();
	for (int curr_town = 0; curr_town < set_size - 1; curr_town++)
	{
		if (town_set[curr_town].unique)
		{
			temp.town = town_set[curr_town].town;
			town_set[curr_town].unique = false;
			for (int next_town = curr_town + 1; next_town < set_size; next_town++)
			{
				if (town_set[next_town].town == town_set[curr_town].town)
				{
					temp.frequency++;
					town_set[next_town].unique = false;
				}
			}
			picked_towns.push_back(temp);
		}
	}
}
bool sortByFrequency(Town_Frequency first, Town_Frequency second)
{
	return first.frequency < second.frequency;
}
void showSortedTowns(vector<Town_Frequency> picked_towns, int X, int Y, int year_x, int year_y, vector<Trip_Man>emp)
{
	int temp_size = picked_towns.size();
	int emp_size = emp.size();
	string month_x, month_y;
	bool flag_x = true, flag_y = true;
	int curr_emp=0;
	for (int curr_emp = 0; curr_emp < emp_size; curr_emp++)
	{
		if (emp[curr_emp].month_num == X)
		{
			month_x = emp[curr_emp].month;
			flag_x = false;
		}
		if (emp[curr_emp].month_num == Y)
		{
			month_y = emp[curr_emp].month;
			flag_y = false;
		}
		if (!flag_x && !flag_y) break;
	}
	cout << SORTED_TOWNS_P1 << month_x << SORTED_TOWNS_P2 << year_x << SORTED_TOWNS_P3 << month_y << SORTED_TOWNS_P2 << year_y << SORTED_TOWNS_P4;
	cout << TOWN_TABLE_HEADER;	
	for (int curr_town = 0; curr_town < temp_size; curr_town++)
	{
		string town_temp_length(TOWN_LINE_LIMIT - picked_towns[curr_town].town.size(), ' ');
		string frequency_temp_length(FREQUENCY_LINE_LIMIT - to_string(picked_towns[curr_town].frequency).size(), ' ');
		cout << "|" << picked_towns[curr_town].town << town_temp_length << "|" << picked_towns[curr_town].frequency << frequency_temp_length << "|\n";
	}
}

void searchMenu(vector<Trip_Man> emp, int& counter)
{
	do
	{
		cout << SEARCH_MENU;
		int choice = inputIntNumbers(0,5);
		switch (choice)
		{
		case 1: searchData(ENTER_SURNAME,emp,counter,searchBySurname); break;
		case 2: searchData(ENTER_NAME,emp,counter,searchByName); break;
		case 3: searchData(ENTER_PATRONYMIC,emp,counter,searchByPatronymic); break;
		case 4: searchData(ENTER_TOWN,emp,counter,searchByTown); break;
		case 5: searchData(ENTER_MONTH,emp,counter,searchByMonth); break;
		case 0: return;
		}
	} while (!wantToGoBack());
}
void searchData(string message, vector<Trip_Man>& emp, int& counter, bool(*searchCondition)(string search_input, int current_letter, vector<Trip_Man> emp, int curr_emp))
{
	cout << message;
	string search_input = onlyLettersInput();
	int emp_size = emp.size();
	int search_size = search_input.size();
	cout << "--№--|"<<TABLE_TRIP_HEADER;
	for (int curr_emp = 0; curr_emp < emp_size; curr_emp++)
	{
		for (int current_letter = 0; current_letter < search_size; current_letter++)
		{
			if (searchCondition(search_input,current_letter,emp,curr_emp))
			{
				break;
			}
			string counter_length (COUNTER_LENGTH_LIMIT - to_string(emp[curr_emp].search_counter).size(), ' ');
			cout <<counter_length<<emp[curr_emp].search_counter++;
			showOneEmployee(emp, curr_emp);
		}
	}
} 
bool searchBySurname(string search_input, int current_letter, vector<Trip_Man> emp, int curr_emp)
{
	return search_input[current_letter] != emp[curr_emp].surname[current_letter];
}
bool searchByName(string search_input, int current_letter, vector<Trip_Man> emp, int curr_emp)
{
	return search_input[current_letter] != emp[curr_emp].name[current_letter];
}
bool searchByPatronymic(string search_input, int current_letter, vector<Trip_Man> emp, int curr_emp)
{
	return search_input[current_letter] != emp[curr_emp].patronymic[current_letter];
}
bool searchByTown(string search_input, int current_letter, vector<Trip_Man> emp, int curr_emp)
{
	return search_input[current_letter] != emp[curr_emp].town[current_letter];
}
bool searchByMonth(string search_input, int current_letter, vector<Trip_Man> emp, int curr_emp)
{
	return search_input[current_letter] != emp[curr_emp].month[current_letter];
}

void sortMenu(vector<Trip_Man> emp)
{
	do
	{
		cout << SORT_MENU;
		int choice = inputIntNumbers(0, 5);
		switch (choice)
		{
		case 1: sortData(SB_SURNAME, emp, sortBySurname); break;
		case 2: sortData(SB_NAME, emp, sortByName); break;
		case 3: sortData(SB_PATRONYMIC, emp, sortByPatronymic); break;
		case 4: sortData(SB_DAYS, emp, sortByDays); break;
		case 5: sortData(SB_MONEY, emp, sortByMoney); break;
		case 0: return;
		}
	} while (!wantToGoBack());
}
void sortData(string message, vector<Trip_Man>emp, bool(*sortCondition)(Trip_Man first, Trip_Man second))
{
	cout << SORT_DIRECTION;
	int choice = inputIntNumbers(1, 2);
	cout << SORTED_BY << message;
	switch (choice)
	{
	case 1: sort(emp.begin(), emp.end(), sortCondition); break;
	case 2: mySort4Decending(emp, sortCondition); break;
	}
	showTripArray(emp);
}
void mySort4Decending(vector<Trip_Man> emp, bool (*sortCondition)(Trip_Man first, Trip_Man second))
{
	int emp_size = emp.size();
	for (int curr_emp = 0; curr_emp < emp_size - 1; curr_emp++)
	{
		for (int next_emp = curr_emp + 1; next_emp < emp_size; next_emp++)
		{
			if (sortCondition(emp[curr_emp], emp[next_emp]))
				swap(emp[curr_emp], emp[next_emp]);
		}
	}
}
bool sortBySurname(Trip_Man first, Trip_Man second)
{
	return first.surname < second.surname;
}
bool sortByName(Trip_Man first, Trip_Man second)
{
	return first.name < second.name;
}
bool sortByPatronymic(Trip_Man first, Trip_Man second)
{
	return first.patronymic < second.patronymic;
}
bool sortByDays(Trip_Man first, Trip_Man second)
{
	return first.trip_length < second.trip_length;
}
bool sortByMoney(Trip_Man first, Trip_Man second)
{
	return first.money_per_day < second.money_per_day;
}

void addData(vector<Trip_Man>&emp)
{
	cout << YOU_SURE;
	int sure = inputIntNumbers(1, 2);
	if (sure==1)
	{
		enterEmployees(emp);
		writeTripFile(emp);
	}
}

void pickDataInArray(string message, vector<Trip_Man>& emp, void (*changeData)(vector<Trip_Man>& emp, int curr_emp))
{
	showTripArray(emp);
	int counter = 0;
	searchMenu(emp,counter);
	cout << message;
	int choice = inputIntNumbers(1, counter);
	int vec_size = emp.size();
	for (int curr_emp = 0; curr_emp < vec_size; curr_emp++)
	{
		if (choice == emp[curr_emp].search_counter)
		{
			changeData(emp, curr_emp);
			break;
		}
	}
}

void editDataMenu(vector<Trip_Man>& emp, int curr_emp)
{
	cout << YOU_SURE;
	int sure = inputIntNumbers(1, 2);
	if (sure == 1)
	{
		cout << EDIT_DATA_MENU;
		int choice = inputIntNumbers(0, 10);
		switch (choice)
		{
		case 1: editData(ENTER_SURNAME,emp,curr_emp,inputSurname); break;
		case 2: editData(ENTER_NAME, emp, curr_emp,inputName); break;
		case 3: editData(ENTER_PATRONYMIC, emp, curr_emp,inputPatronymic); break;
		case 4: editData(ENTER_YEAR, emp, curr_emp,inputYear); break;
		case 5: editData(ENTER_MONTH, emp, curr_emp,inputMonth); break;
		case 6: editData(ENTER_DAYS, emp, curr_emp,inputDays); break;
		case 7: editData(ENTER_MONEY, emp, curr_emp,inputMoney); break;
		case 8: editData(ENTER_CURRENCY,emp,curr_emp,inputCurrency); break;
		case 9: editData(ENTER_TOWN, emp, curr_emp,inputTown); break;
		case 10: enter1Employee(emp[curr_emp]); break;
		case 0: return;
		}
	}
}
void editData(string message,vector<Trip_Man>& emp, int curr_emp,void(*inputNewData)(Trip_Man& temp))
{
	cout << message;
	inputNewData(emp[curr_emp]);
}

void inputSurname(Trip_Man& temp)
{
	temp.surname = check4TooBigString(F_I_O_LINE_LIMIT, TOO_BIG_STRING, onlyLettersInput);
}
void inputName(Trip_Man& temp)
{
	temp.name = check4TooBigString(F_I_O_LINE_LIMIT, TOO_BIG_STRING, onlyLettersInput);
}
void inputPatronymic(Trip_Man& temp)
{
	checkPatronymic(temp);
}
void inputYear(Trip_Man& temp)
{
	temp.year = inputIntNumbers(YEAR_LINE_LIMIT);
}
void inputMonth(Trip_Man& temp)
{
	temp.month = check4TooBigString(MONTH_LINE_LIMIT, TOO_BIG_STRING, onlyLettersInput);
	int month_size = temp.month.size();
	temp.month_num = convertMonthName2Number(temp.month, month_size);
}
void inputDays(Trip_Man& temp)
{
	switch (temp.month_num)
	{
	case 1: case 3: case 5: case 7: case 11: temp.trip_length = inputIntNumbers(1, 31); break;
	case 4: case 6: case 8: case 12: temp.trip_length = inputIntNumbers(1, 30); break;
	case 2: ((temp.year-2012)%4==0)? temp.trip_length = inputIntNumbers(1, 29):temp.trip_length = inputIntNumbers(1, 28); break;
	}
}
void inputMoney(Trip_Man& temp)
{
	temp.money_per_day = inputIntNumbers(MONEY_LINE_LIMIT);
}
void inputCurrency(Trip_Man& temp)
{
	string curr = check4TooBigString(CURRENCY_LIMIT, TOO_BIG_STRING, onlyLettersInput);
	int curr_size = curr.size();
	for (int i = 0; i < curr_size; i++)
	{
		temp.currency.push_back(toupper(curr.at(i)));
	}
}
void inputTown(Trip_Man& temp)
{
	temp.town = check4TooBigString(TOWN_LINE_LIMIT, TOO_BIG_STRING, onlyLettersInput);
}

void deleteData(vector<Trip_Man>& emp, int curr_emp)
{
	cout << YOU_SURE;
	int sure = inputIntNumbers(1,2);
	if (sure == 1)
	{
		emp.erase(emp.begin() + curr_emp);
	}
	writeTripFile(emp);
}