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
			clearScreen();
			cout << BAN_CONDITION;
		}
		else if (!doesAccountHaveAccess(guest) && areYouNew(guest))
		{
			clearScreen();
			if (!exit_token)
			{
				cout << WAIT_4_CONFIRMATION;
			}
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
		choice = oneWordInput(justEnterChar);
		int choice_size = choice.size();
		for (int curr_char = 0; curr_char < choice_size; curr_char++)
		{
			choice.at(curr_char) = tolower(choice.at(curr_char));
		}
		if (choice == "1" || choice == "да")
		{
			writeTripFile(emp);
			break;
		}	
	}
}
void enter1Employee(Trip_Man& temp)
{
	clearScreen();
	showOneEmployee();
	inputSurname(temp);
	clearScreen();
	showOneEmployee(temp.surname);
	inputName(temp);
	clearScreen();
	showOneEmployee(temp.surname,temp.name);
	inputPatronymic(temp);
	clearScreen();
	showOneEmployee(temp.surname,temp.name,temp.patronymic);
	inputYear(temp);
	clearScreen();
	showOneEmployee(temp.surname,temp.name,temp.patronymic,to_string(temp.year));
	inputMonth(temp);
	clearScreen();
	showOneEmployee(temp.surname, temp.name, temp.patronymic, to_string(temp.year),temp.month);
	inputDays(temp);
	clearScreen();
	showOneEmployee(temp.surname, temp.name, temp.patronymic, to_string(temp.year), temp.month,to_string(temp.trip_length));
	inputMoney(temp);
	clearScreen();
	showOneEmployee(temp.surname, temp.name, temp.patronymic, to_string(temp.year), temp.month, to_string(temp.trip_length),doubleToString(temp.money_per_day));
	inputCurrency(temp);
	clearScreen();
	showOneEmployee(temp.surname, temp.name, temp.patronymic, to_string(temp.year), temp.month, to_string(temp.trip_length), doubleToString(temp.money_per_day),temp.currency);
	inputTown(temp);
	clearScreen();
	showOneEmployee(temp.surname, temp.name, temp.patronymic, to_string(temp.year), temp.month, to_string(temp.trip_length), doubleToString(temp.money_per_day), temp.currency,temp.town);
}
void showOneEmployee (string surname,string name,string patronymic,string year, string month, string days, string money, string currency,string town)
{
	string emp_divider(TABLE_TRIP_HEADER.size()+1, '-');
	string blank_year(YEAR_LINE_LIMIT, ' '), blank_month(MONTH_LINE_LIMIT, ' '), blank_days(DAYS_LINE_LIMIT, ' '), blank_money(MONEY_LINE_LIMIT_2, ' '), blank_town(TOWN_LINE_LIMIT, ' ');

	cout << "|" << setw(F_I_O_LINE_LIMIT) << surname
		<< "|" << setw(YEAR_LINE_LIMIT) << year
		<< "|" << setw(MONTH_LINE_LIMIT) << month
		<< "|" << setw(DAYS_LINE_LIMIT) << days
		<< "|" << setw(MONEY_LINE_LIMIT_2) << money + " " + currency
		<< "|" << setw(TOWN_LINE_LIMIT) << town << "|" << endl
		<< "|" << setw(F_I_O_LINE_LIMIT) << name
		<< "|" << blank_year << "|" << blank_month << "|" << blank_days << "|" << blank_money<< "|" << blank_town << "|" << endl;

	if (patronymic != "-") //printing patronymic if such exists
	{
		cout << "|" << setw(F_I_O_LINE_LIMIT) << patronymic
			<< "|" << blank_year << "|" << blank_month << "|" << blank_days << "|" << blank_money << "|" << blank_town << "|" << endl;
	}
	cout << "|" << emp_divider << "|\n";
}

void processTripFile(vector<Account>& acc, Account& guest,vector <Trip_Man>& emp,bool& is_file_open,bool& exit_token,string file_name)
{
	readTripFile(emp, is_file_open,file_name);
	while (!is_file_open&&!exit_token)
	{
		clearScreen();
		int choice = inputIntNumbers(NO_FILE_ACCESS,0,3, ERROR_NUM_RANGE_INPUT + "(0-3)\n");
		switch (choice)
		{
		case 0: exit_token = true; break;
		case 1: enterEmployees(emp); break;
		case 2: processTripFile(acc, guest, emp, is_file_open, exit_token, TEST_FILE); writeTripFile(emp);	break;
		case 3: processAccountMenu(acc, guest, exit_token); break;
		}
		readTripFile(emp, is_file_open,file_name);
	}
}

void readTripFile(vector <Trip_Man>& emp, bool& is_file_open,string file_name)
{
	int amount_of_employees = countStructuresInTripFile(is_file_open,file_name);
	if (is_file_open)
	{
		if (emp.size()) emp.clear();
		emp.reserve(amount_of_employees);						
		ifstream f_in(file_name, ios::in);
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
int countStructuresInTripFile(bool& is_file_open, string file_name)
{
	ifstream fin(file_name, ios::in);
	int amount_of_employees = 0;
	if (fin.is_open())
	{
		is_file_open = true;
		string temp;
		while (getline(fin, temp)) //reads file by lines
		{
			amount_of_employees++; //if line's read successfuly increases amount_of_accounts
		}
		fin.close();
	}
	else //if file is not opening
	{
		is_file_open = false;
		fin.close();
		return 0;
	}
	return amount_of_employees;
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

void processMainMenu(vector <Trip_Man>& emp, vector<Account>& acc, Account& guest, bool& exit_token)
{
	do
	{
		clearScreen();
		int main_menu_choice = inputIntNumbers(MAIN_MENU,0, 2, ERROR_NUM_RANGE_INPUT + "(0-2)\n");
		switch (main_menu_choice)
		{
		case 1: processAccountMenu(acc, guest,exit_token); break;
		case 2: processTripMenu(emp, guest); break;
		case 0: return;
		}
	} while (true);
}
void processAccountMenu(vector<Account>& acc, Account& guest,bool&exit_token)
{
	do
	{
		clearScreen();
		int choice = 0;
		(guest.role == 1) ? choice=inputIntNumbers(ACCOUNT_MENU_ROLE_1,0, 5, ERROR_NUM_RANGE_INPUT + "(0-5)\n") : choice = inputIntNumbers(ACCOUNT_MENU_ROLE_0, 0, 5, ERROR_NUM_RANGE_INPUT + "(0-5)\n");
		if (guest.role == 1) //admin only options
		{
			switch (choice)
			{
			case 2: showAccountArray(acc); _getch(); break;
			case 3: addAccountInArray(acc, guest); break;
			case 4: changeAccountInArray(CHOOSE_TO_EDIT, acc,guest,editAccountMenu,EDIT_ACCOUNT_MENU); _getch(); break;
			case 5: changeAccountInArray(CHOOSE_TO_DELETE, acc,guest,deleteAccountInArray); _getch(); break;
			}
		}
		switch (choice) //any user options
		{
		case 1: changeLogin(acc, guest,exit_token); _getch(); break;
		case 0: return;
		}
	} while (true);
}
void processTripMenu(vector<Trip_Man>& emp, Account guest)
{
	do
	{
		int useless_counter = 0;
		clearScreen();
		int choice = 0;
		(guest.role == 1) ? choice = inputIntNumbers(TRIP_MENU_ROLE_1,0, 6, ERROR_NUM_RANGE_INPUT + "(0-6)\n"): choice = inputIntNumbers(TRIP_MENU_ROLE_0, 0, 6, ERROR_NUM_RANGE_INPUT + "(0-6)\n");
		if (guest.role == 1 && choice == 6) //admin only option
		{
			processDataChangeMenu(emp);
		}
		switch (choice) //any user options
		{
		case 1: showTripArray(emp); _getch(); break;
		case 2: countMoney4MonthX(emp); _getch(); break;
		case 3: sortTowns(emp); _getch(); break;
		case 4: searchMenu(emp, useless_counter); break;
		case 5: sortMenu(emp); break;
		case 0: return;
		}
	} while (true);
}
void processDataChangeMenu(vector<Trip_Man>& emp)
{
	do
	{
		clearScreen();
		int choice = inputIntNumbers(DATA_CHANGE_MENU_ROLE_1,0,3, ERROR_NUM_RANGE_INPUT + "(0-3)\n");
		switch (choice)
		{
		case 1: enterEmployees(emp); break;
		case 2: pickDataInArray(CHOOSE_TO_EDIT, emp, editDataMenu); _getch(); break;
		case 3: pickDataInArray(CHOOSE_TO_DELETE, emp, deleteData); _getch(); break;
		case 0: return;
		}
	} while (true);
}

void tripHeaderOutput(int c_length, string counter)
{
	cout << counter << TABLE_TRIP_HEADER;
	string counter_length_div(c_length, '-');
	string blank_counter(c_length, ' '), blank_fio(F_I_O_LINE_LIMIT, ' '), blank_year(YEAR_LINE_LIMIT, ' '), 
			blank_month(MONTH_LINE_LIMIT, ' '), blank_days(DAYS_LINE_LIMIT, ' '), blank_money(MONEY_LINE_LIMIT + CURRENCY_LIMIT, ' '), blank_town(TOWN_LINE_LIMIT, ' ');
	string  emp_divider(TABLE_TRIP_HEADER.size() - 3, '-');
	cout <<blank_counter<<"|" << blank_fio << "|" << blank_year << "|" << blank_month << "|" << blank_days << "|" << blank_money << "|" << blank_town << "|" << endl;
	cout << counter_length_div << "|" << emp_divider << "|\n";
}
void showTripArray(vector<Trip_Man>emp)
{
	clearScreen();
	int vec_size = emp.size();
	tripHeaderOutput();
	for (int curr_emp = 0; curr_emp < vec_size; curr_emp++)
	{
		showOneEmployee(emp,curr_emp);
	}
}
void showOneEmployee(vector<Trip_Man>emp,int curr_emp,int c_length)
{
	string blank_year(YEAR_LINE_LIMIT, ' '), blank_month(MONTH_LINE_LIMIT, ' '),
		blank_days(DAYS_LINE_LIMIT, ' '), blank_money(MONEY_LINE_LIMIT + CURRENCY_LIMIT, ' '), blank_town(TOWN_LINE_LIMIT, ' ');
	string emp_divider(TABLE_TRIP_HEADER.size() - 3, '-');
	string counter_length_div(c_length, '-');

	cout<< "|" << setw(F_I_O_LINE_LIMIT)<< emp[curr_emp].surname
		<< "|" << setw(YEAR_LINE_LIMIT) <<emp[curr_emp].year
		<< "|" << setw(MONTH_LINE_LIMIT)<< emp[curr_emp].month
		<< "|" << setw(DAYS_LINE_LIMIT) << emp[curr_emp].trip_length
		<< "|" << setw(MONEY_LINE_LIMIT+CURRENCY_LIMIT)<< doubleToString(emp[curr_emp].money_per_day)+" "+emp[curr_emp].currency
		<< "|" << setw(TOWN_LINE_LIMIT) << emp[curr_emp].town << "|" << endl
		<<setw(c_length+1)<< "|" << setw(F_I_O_LINE_LIMIT) << emp[curr_emp].name
		<< "|" << blank_year << "|" << blank_month << "|" << blank_days << "|" << blank_money << "|" << blank_town <<"|"<< endl;

	if (emp[curr_emp].patronymic != "-") //printing patronymic if such exists
	{
		cout <<setw(c_length+1) << "|" <<setw(F_I_O_LINE_LIMIT)<< emp[curr_emp].patronymic
			<< "|" << blank_year << "|" << blank_month << "|" << blank_days << "|" << blank_money << "|" << blank_town <<"|"<< endl;
	}
	cout <<counter_length_div<< "|" << emp_divider << "|\n";
}

string doubleToString(double value)
{
	string result,temp= to_string(value);
	int s_size=temp.size();
	for (int curr_symb = 0; curr_symb < s_size-3; curr_symb++)
	{
		result.push_back(temp[curr_symb]);
		if (temp[curr_symb] == ',')
		{
			int next_symb = curr_symb + 1;
			while (next_symb!=curr_symb+3)
			{
				result.push_back(temp[next_symb]);
				next_symb++;
			}
			break;
		}
	}
	return result;
}

void countMoney4MonthX(vector<Trip_Man> emp)
{
	clearScreen();
	int month_size = MONTH_SET.size();
	for (int curr_month = 0; curr_month < month_size; curr_month++)
	{
		cout << setw(5) << curr_month + 1 << ". " << MONTH_SET.at(curr_month) << endl;
	}
	int month_num = inputIntNumbers(ENTER_MONTH, 1, month_size, ERROR_NUM_RANGE_INPUT + "(1-" + to_string(month_size) + ")\n");
	string input_month = MONTH_SET.at(month_num - 1);
	int input_year = inputIntNumbers(ENTER_YEAR, YEAR_INPUT_LIM, ERROR_LIMIT_INPUT_P1 + to_string(YEAR_INPUT_LIM) + ERROR_LIMIT_INPUT_P2);
	if (input_month == NO_INFO) return;
	formatString(input_month);
	vector<Month_Money> value;
	Month_Money temp;
	int amount_of_emp = emp.size();
	bool data_exists = false;
	for (int curr_emp = 0; curr_emp < amount_of_emp; curr_emp++)
	{
		if (input_month == emp[curr_emp].month && input_year==emp[curr_emp].year) //filling month_money vector with money and currency for input_month of input_year
		{
			temp.money = emp[curr_emp].money_per_day*emp[curr_emp].trip_length;
			temp.currency = emp[curr_emp].currency;
			value.push_back(temp);
			data_exists = true;
		}
	}
	if (data_exists)
	{
		clearScreen();
		showTripArray(emp);
		cout << MONEY_RES_P1 << input_month << " " << input_year << MONEY_RES_P2 << countMoney(value) << endl;
	}
	else
	{
		cout << NO_DATA_FOUND;
	}	
}
string countMoney(vector<Month_Money> value)
{
	double currency_sum = 0;
	string result;
	int value_size = value.size();
	for (int curr_mon = 0; curr_mon < value_size-1; curr_mon++)
	{
		if (value[curr_mon].unique == true) //if currency is unique
		{
			value[curr_mon].unique = false; //no longer unique
			currency_sum = value[curr_mon].money; //setting the first value of sum
			for (int next_mon = curr_mon + 1; next_mon < value_size; next_mon++)
			{
				if (value[curr_mon].currency == value[next_mon].currency) //looking 4 the same currency
				{
					currency_sum += value[next_mon].money; //adding money of the same currency to the sum
					value[next_mon].unique = false; //turning uniqueness of such unit to false
				}
			}
			result += doubleToString(currency_sum) +" "+ value[curr_mon].currency + ", "; //result string: "value_1_sum CURRENCY_1, value_2_sum CURRENCY_2..." 
		}
	}
	if (value[value_size - 1].unique == true) //if the last unit's currency is unique
	{
		result += doubleToString(value[value_size - 1].money) + value[value_size - 1].currency;
	}
	while (result.at(result.size() - 1) == ',' || result.at(result.size() - 1) == ' ')
	{
		result.erase(result.end() - 1);
	}
	return result;
}

void sortTowns(vector<Trip_Man> emp)
{
	string month_x, month_y;
	int year_x=0, year_y=0;
	int X = 0, Y = 0;
	X = enterMonth(emp,ENTER_MONTH_X, month_x);
	year_x = inputIntNumbers(ENTER_YEAR,YEAR_INPUT_LIM,ERROR_LIMIT_INPUT_P1+to_string(YEAR_INPUT_LIM)+ERROR_LIMIT_INPUT_P2);
	Y = enterMonth(emp,ENTER_MONTH_Y, month_y);
	year_y = inputIntNumbers(ENTER_YEAR,YEAR_INPUT_LIM, ERROR_LIMIT_INPUT_P1 + to_string(YEAR_INPUT_LIM) + ERROR_LIMIT_INPUT_P2);
	if (year_x > year_y) swap(year_x, year_y); // if user firstly entered bigger year, swaps them
	vector<Town_Frequency> town_set, picked_towns;
	fillTowns2TownSet(town_set, emp, year_x, year_y, X, Y); //writing town_set array
	writeTownsInSortArray(town_set, picked_towns);
	mySort(picked_towns, &Town_Frequency::town);
	mySort(picked_towns,&Town_Frequency::frequency);
	clearScreen();
	showTripArray(emp);
	showSortedTowns(picked_towns,month_x, month_y,year_x,year_y,emp);
}

int enterMonth(vector<Trip_Man> emp,string message, string& month)
{
	clearScreen();
	int month_size = MONTH_SET.size();
	for (int curr_month = 0; curr_month < month_size; curr_month++)
	{
		cout << setw(5) << curr_month + 1 << ". " << MONTH_SET.at(curr_month) << endl;
	}
	int month_num = inputIntNumbers(message,1,MONTH_SET.size(),ERROR_NUM_RANGE_INPUT+"(1-"+to_string(MONTH_SET.size())+")\n");
	month = MONTH_SET.at(month_num-1);
	return month_num;
}

void fillTowns2TownSet(vector<Town_Frequency>& town_set,vector<Trip_Man> emp, int year_x, int year_y, int X, int Y)
{
	Town_Frequency temp;
	int emp_size = emp.size();
	if (year_x != year_y)
	{
		for (X; X <= 12; X++) //writing towns till the end of the year_x
		{
			write1TownInTownSet(emp, town_set, temp, emp_size, X, year_x);
		}
		year_x++;
		while(year_x!=year_y)
		{
			for (X = 1; X <= 12; X++) //writing towns for one year
			{
				write1TownInTownSet(emp, town_set, temp, emp_size, X, year_x);
			}
			year_x++;
		}
	}
	for (X = 1; X <= Y; X++) //writing towns in the year_y
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
			temp.frequency = 1;
		}
	}
	if (town_set[set_size - 1].unique)
	{
		town_set[set_size - 1].unique = false;
		picked_towns.push_back(town_set[set_size - 1]);
	}
}
void showSortedTowns(vector<Town_Frequency> picked_towns, string month_x, string month_y, int year_x, int year_y, vector<Trip_Man>emp)
{
	int temp_size = picked_towns.size();
	string town_divider(TOWN_TABLE_HEADER.size() - 3, '-');
	cout << SORTED_TOWNS_P1 << month_x << " " << year_x << SORTED_TOWNS_P2 << month_y << " " << year_y << SORTED_TOWNS_P3 << endl;
	cout << TOWN_TABLE_HEADER;
	cout << "|" << town_divider << "|" << endl;
	for (int curr_town = 0; curr_town < temp_size; curr_town++)
	{
		cout << "|" << setw(TOWN_LINE_LIMIT) << picked_towns[curr_town].town << "|" << setw(FREQUENCY_LINE_LIMIT) << picked_towns[curr_town].frequency << "|\n";
		cout << "|" << town_divider << "|" << endl;
	}
}

void searchMenu(vector<Trip_Man>&emp, int& counter)
{
	do
	{
		clearScreen();
		int choice = inputIntNumbers(SEARCH_MENU,0,10, ERROR_NUM_RANGE_INPUT + "(0-10)\n");
		switch (choice)
		{
		case 1: searchData(ENTER_SURNAME, emp,&Trip_Man::surname,counter,searchString); break;
		case 2: searchData(ENTER_NAME, emp,&Trip_Man::name,counter, searchString); break;
		case 3: searchData(ENTER_PATRONYMIC, emp, &Trip_Man::patronymic,counter, searchString); break;
		case 4: searchData(ENTER_TOWN, emp, &Trip_Man::town,counter, searchString); break;
		case 5: searchData(ENTER_MONTH_NAME, emp,&Trip_Man::month, counter,searchString); break;
		case 6: searchData(ENTER_MONTH, emp, &Trip_Man::month_num,counter, searchInt, onlyNumInput); break;
		case 7: searchData(ENTER_YEAR, emp, &Trip_Man::year, counter, searchInt,onlyNumInput); break;
		case 8: searchData(ENTER_MONEY, emp, &Trip_Man::money_per_day, counter, searchDouble,onlyNumInput); break;
		case 9: searchData(ENTER_CURRENCY, emp, &Trip_Man::currency, counter, searchString,currencyInput); break;
		case 10: searchData(ENTER_DAYS, emp, &Trip_Man::trip_length, counter, searchInt,onlyNumInput); break;
		case 0: counter = 0; return;
		}
	} while (!wantToGoBack(FINISHED_SEARCHING,2));
}

template<typename T>
void searchData(string message, vector<Trip_Man>& emp,T Trip_Man::*field,int& counter, bool (*searchCondition) (vector<Trip_Man> emp, T Trip_Man::* field, string search_input, int curr_emp),char(*inputCondition)())
{
	clearScreen();
	cout << message;
	string search_input = oneWordInput(inputCondition);
	if (inputCondition==onlyLetterInput) formatString(search_input);
	int emp_size = emp.size();
	int search_size = 0;
	counter = 0;
	clearScreen();
	tripHeaderOutput(COUNTER_LENGTH_LIMIT,"--№--");
	for (int curr_emp = 0; curr_emp < emp_size; curr_emp++)
	{
		if (searchCondition(emp,field,search_input,curr_emp))
		{
			counter++;
			emp[curr_emp].search_counter = counter;
			cout <<setw(COUNTER_LENGTH_LIMIT) << emp[curr_emp].search_counter;
			showOneEmployee(emp,curr_emp, COUNTER_LENGTH_LIMIT);
		}
	}
	if (!counter)
	{
		clearScreen();
		cout << NO_DATA_FOUND;
	}
}
bool searchString(vector<Trip_Man> emp, string Trip_Man::* field, string search_input, int curr_emp)
{
	return (emp[curr_emp].*field).rfind(search_input, 0) == 0;//finds matching letters of search_input in emp[curr_emp].*field 
															  //from position 0 and nowhere further; returns the position of the first character of the last match
}
bool searchInt(vector<Trip_Man> emp, int Trip_Man::* field, string search_input, int curr_emp)
{
	return to_string((emp[curr_emp].*field)).rfind(search_input, 0) == 0;//finds matching letters of search_input in emp[curr_emp].*field 
																		  //from position 0 and nowhere further; returns the position of the first character of the last match
}
bool searchDouble(vector<Trip_Man> emp, double Trip_Man::* field, string search_input, int curr_emp)
{
	return doubleToString((emp[curr_emp].*field)).rfind(search_input, 0) == 0;//finds matching letters of search_input in emp[curr_emp].*field 
																			 //from position 0 and nowhere further; returns the position of the first character of the last match
}

void sortMenu(vector<Trip_Man> emp)
{
	do
	{
		clearScreen();
		int choice = inputIntNumbers(SORT_MENU,0, 9,ERROR_NUM_RANGE_INPUT + "(0-9)\n");
		switch (choice)
		{
		case 1: sortData(SB_SURNAME, emp, &Trip_Man::surname); break;
		case 2: sortData(SB_NAME, emp,&Trip_Man::name); break;
		case 3: sortData(SB_PATRONYMIC, emp, &Trip_Man::patronymic); break;
		case 4: sortData(SB_DAYS, emp, &Trip_Man::trip_length); break;
		case 5: sortData(SB_MONEY, emp, &Trip_Man::money_per_day); break;
		case 6: sortData(SB_CURRENCY, emp, &Trip_Man::currency); break;
		case 7: sortData(SB_MONTH, emp, &Trip_Man::month_num); break;
		case 8: sortData(SB_YEAR, emp, &Trip_Man::year); break;
		case 9: sortData(SB_TOWN, emp, &Trip_Man::town); break;
		case 0: return;
		}
	} while (!wantToGoBack(REPEAT_SORT,2));
}

template <typename T>
void sortData(string message, vector<Trip_Man>emp, T Trip_Man::* temp)
{
	int choice = inputIntNumbers(SORT_DIRECTION,1, 2,ERROR_NUM_RANGE_INPUT + "(1-2)\n");
	cout << SORTED_BY << message;
	mySort(emp, temp, choice);
	showTripArray(emp);
}

template <typename T, typename J>
void mySort(vector<J>&vec, T J::*temp, int direction)
{
	sort(vec.begin(), vec.end(), [direction,temp](J first, J second)
		{
			return (direction == 1) ? (first.*temp < second.*temp) : (first.*temp > second.*temp);
		}
	);
}
void pickDataInArray(string message, vector<Trip_Man>& emp, void (*changeData)(vector<Trip_Man>& emp, int curr_emp))
{
	int counter = 0;
	searchMenu(emp,counter);
	if (!counter) return;
	int choice = inputIntNumbers(message,1, counter, ERROR_NUM_RANGE_INPUT + "(1-"+to_string(counter)+ ")\n");
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
	int sure = inputIntNumbers(YOU_SURE_TO_EDIT,1, 2, ERROR_NUM_RANGE_INPUT + "(1-2)\n");
	if (sure == 1)
	{
		int choice = inputIntNumbers(EDIT_DATA_MENU,0, 10, ERROR_NUM_RANGE_INPUT + "(0-10)\n");
		switch (choice)
		{
		case 1: inputSurname(emp[curr_emp]); break;
		case 2: inputName(emp[curr_emp]); break;
		case 3: inputPatronymic(emp[curr_emp]); break;
		case 4: inputYear(emp[curr_emp]); break;
		case 5: inputMonth(emp[curr_emp]); break;
		case 6: inputDays(emp[curr_emp]); break;
		case 7: inputMoney(emp[curr_emp]); break;
		case 8: inputCurrency(emp[curr_emp]); break;
		case 9: inputTown(emp[curr_emp]); break;
		case 10: enter1Employee(emp[curr_emp]); break;
		case 0: return;
		}
		cout << SUCC_EDIT;
	}
}

void formatString(string& temp)
{
	int str_size = temp.size();
	int curr_symb = 0;
	temp[curr_symb] = toupper(temp[curr_symb]);
	while(curr_symb < str_size)
	{
		if ((temp[curr_symb] == '-' || temp[curr_symb] == '_') && curr_symb < str_size - 1)
		{
			temp[curr_symb + 1] = toupper(temp[curr_symb + 1]);
			curr_symb ++;
		}
		curr_symb++;
		temp[curr_symb] = tolower(temp[curr_symb]);
	}
}

void inputSurname(Trip_Man& temp)
{
	temp.surname = check4TooBigString(F_I_O_LINE_LIMIT,onlyLetterInput,ENTER_SURNAME); //returns NO_INFO if user wants to go back
	if (temp.surname == NO_INFO) return;
	formatString(temp.surname);
}
void inputName(Trip_Man& temp)
{
	temp.name = check4TooBigString(F_I_O_LINE_LIMIT,onlyLetterInput,ENTER_NAME); //returns NO_INFO if user wants to go back
	if (temp.name == NO_INFO) return;
	formatString(temp.name);
}
void inputPatronymic(Trip_Man& temp)
{
	temp.patronymic = check4TooBigString(F_I_O_LINE_LIMIT, onlyLetterInput, ENTER_PATRONYMIC); //returns NO_INFO if user wants to go back
	if (temp.patronymic == NO_INFO) return;
	int temp_size = temp.patronymic.size();
	for (int curr_char = 0; curr_char < temp_size; curr_char++)
	{
		temp.patronymic.at(curr_char) = tolower(temp.patronymic.at(curr_char));
	}
	if (temp.patronymic == "нет"||temp.patronymic=="-") //no means employee got no patronymic
	{
		temp.patronymic = "-";
	}
	else
	{
		formatString(temp.patronymic);
	}
}
void inputYear(Trip_Man& temp)
{
	temp.year = inputIntNumbers(ENTER_YEAR,YEAR_INPUT_LIM, ERROR_LIMIT_INPUT_P1 + to_string(YEAR_INPUT_LIM) + ERROR_LIMIT_INPUT_P2);
}
void inputMonth(Trip_Man& temp)
{
	int month_size = MONTH_SET.size();
	for (int curr_month = 0; curr_month < month_size; curr_month++)
	{
		cout << setw(5) << curr_month + 1 << ". " << MONTH_SET.at(curr_month) << endl;
	}
	temp.month_num = inputIntNumbers(ENTER_MONTH,1,month_size, ERROR_NUM_RANGE_INPUT + "(1-"+to_string(month_size)+")\n");
	temp.month = MONTH_SET.at(temp.month_num - 1);
}
void inputDays(Trip_Man& temp)
{
	switch (temp.month_num)
	{
	default: case 1: case 3: case 5: case 7: case 11: temp.trip_length = inputIntNumbers(ENTER_DAYS,1, 31,WRONG_DAYS_P1+temp.month+WRONG_DAYS_P2); break;
	case 4: case 6: case 8: case 12: temp.trip_length = inputIntNumbers(ENTER_DAYS,1, 30, WRONG_DAYS_P1 + temp.month + WRONG_DAYS_P2); break;
	case 2: ((temp.year-2012)%4==0)? temp.trip_length = inputIntNumbers(ENTER_DAYS,1, 29, WRONG_DAYS_P1 + temp.month + WRONG_DAYS_P2):temp.trip_length = inputIntNumbers(ENTER_DAYS,1, 28, WRONG_DAYS_P1 + temp.month + WRONG_DAYS_P2); break;
	}
}
void inputMoney(Trip_Man& temp)
{
	temp.money_per_day = ceil(inputDouble(ENTER_MONEY, MONEY_LINE_LIMIT) * 100.0) / 100.0;
}
void inputCurrency(Trip_Man& temp)
{
	if (temp.currency.size()) temp.currency.clear();
	temp.currency = check4TooBigString(CURRENCY_LIMIT,currencyInput,ENTER_CURRENCY); //returns NO_INFO if user wants to go back
}
void inputTown(Trip_Man& temp)
{
	temp.town = check4TooBigString(TOWN_LINE_LIMIT,onlyLetterInput,ENTER_TOWN); //returns NO_INFO if user wants to go back
	if (temp.town == NO_INFO) return;
	formatString(temp.town);
}

void deleteData(vector<Trip_Man>& emp, int curr_emp)
{
	int sure = inputIntNumbers(YOU_SURE_TO_DELETE,1,2, ERROR_NUM_RANGE_INPUT + "(1-2)\n");
	if (sure == 1)
	{
		emp.erase(emp.begin() + curr_emp);
		cout << SUCC_DELETE;
	}
	writeTripFile(emp);
}