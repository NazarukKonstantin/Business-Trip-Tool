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
		if (choice == "1" || choice == "да" || choice == "yes")
		{
			writeTripFile(emp);
			break;
		}	
	}
}
void enter1Employee(Trip_Man& temp)
{
	clearScreen();
	inputSurname(temp);
	inputName(temp);
	inputPatronymic(temp);
	inputYear(temp);
	inputMonth(temp);
	inputDays(temp);
	inputMoney(temp);
	inputCurrency(temp);
	inputTown(temp);
}

void processTripFile(vector<Account>& acc, Account& guest,vector <Trip_Man>& emp,bool is_file_open,bool& exit_token)
{
	readTripFile(emp, is_file_open);
	while (!is_file_open)
	{
		clearScreen();
		int choice = inputIntNumbers(NO_FILE_ACCESS,0,2);
		switch (choice)
		{
		case 0: exit_token = true; is_file_open = true; break;
		case 1: enterEmployees(emp); break;
		case 2: processAccountMenu(acc,guest); break;
		}
		readTripFile(emp, is_file_open);
	}
}

void readTripFile(vector <Trip_Man>& emp, bool& is_file_open)
{
	int amount_of_employees = countStructuresInTripFile(is_file_open);
	if (is_file_open)
	{
		emp.reserve(amount_of_employees);						
		ifstream f_in(TRIP_INFO, ios::in);
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
	int amount_of_employees = 0;
	if (fin.is_open())
	{
		is_file_open = true;
		string temp;
		while (getline(fin, temp)) //reads file by lines
		{
			amount_of_employees++; //if line's read successfuly increases amount_of_accounts
		}
	}
	else //if file is not opening
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
	ofstream f_add(ACCOUNT_FILE_NAME, ios::app);
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
	do
	{
		clearScreen();
		int main_menu_choice = inputIntNumbers(MAIN_MENU,0, 2);
		switch (main_menu_choice)
		{
		case 1: processAccountMenu(acc, guest); break;
		case 2: processTripMenu(emp, guest); break;
		case 0: return;
		}
		clearScreen();
		cout << MAIN_MENU;
	} while (true);
}
void processAccountMenu(vector<Account>& acc, Account& guest)
{
	do
	{
		clearScreen();
		int choice = 0;
		(guest.role == 1) ? choice=inputIntNumbers(ACCOUNT_MENU_ROLE_1,0, 5) : choice = inputIntNumbers(ACCOUNT_MENU_ROLE_0, 0, 5);
		if (guest.role == 1) //admin only options
		{
			switch (choice)
			{
			case 2: showAccountArray(acc); break;
			case 3: addAccountInArray(acc, guest); break;
			case 4: pickAccountInArray(TO_EDIT,CHOOSE_TO_EDIT,acc, editAccountMenu); break;
			case 5: pickAccountInArray(TO_DELETE,CHOOSE_TO_DELETE,acc, deleteAccountInArray);break;
			}
		}
		switch (choice) //any user options
		{
		case 1: changeLogin(acc, guest); clearScreen(); break;
		case 0: return;
		}
		system("pause");
		clearScreen();
		guest.role == 1 ? cout << ACCOUNT_MENU_ROLE_1 : cout << ACCOUNT_MENU_ROLE_0;
	} while (true);
}
void processTripMenu(vector<Trip_Man> emp, Account guest)
{
	do
	{
		int useless_counter = 0;
		clearScreen();
		int choice = 0;
		(guest.role == 1) ? choice = inputIntNumbers(TRIP_MENU_ROLE_1,0, 6): choice = inputIntNumbers(TRIP_MENU_ROLE_0, 0, 6);
		if (guest.role == 1 && choice == 6) //admin only option
		{
			processDataChangeMenu(emp);
		}
		switch (choice) //any user options
		{
		case 1: showTripArray(emp); break;
		case 2: countMoney4MonthX(emp);break;
		case 3: sortTowns(emp);break;
		case 4: searchMenu(emp, useless_counter); break;
		case 5: sortMenu(emp); break;
		case 0: return;
		}
		system("pause");
		clearScreen();
		guest.role == 1 ? cout << TRIP_MENU_ROLE_1 : cout << TRIP_MENU_ROLE_0;
	} while (true);
}
void processDataChangeMenu(vector<Trip_Man>& emp)
{
	do
	{
		clearScreen();
		showTripArray(emp);
		int choice = inputIntNumbers(DATA_CHANGE_MENU_ROLE_1,0,3);
		switch (choice)
		{
		case 1: addData(emp); break;
		case 2: pickDataInArray(CHOOSE_TO_EDIT,emp,editDataMenu); break;
		case 3: pickDataInArray(CHOOSE_TO_DELETE,emp,deleteData); break;
		case 0: return;
		}
		system("pause");
		clearScreen();
		showTripArray(emp);
		cout << DATA_CHANGE_MENU_ROLE_1;
	} while (true);
}

void showTripArray(vector<Trip_Man>emp, int c_length)
{
	clearScreen();
	int vec_size = emp.size();
	string counter_length(c_length, ' ');
	cout <<counter_length<< TABLE_TRIP_HEADER;
	for (int curr_emp = 0; curr_emp < vec_size; curr_emp++)
	{
		showOneEmployee(emp, curr_emp);
	}
}
void showOneEmployee(vector<Trip_Man>emp, int curr_emp,int c_length)
{
	// strings filled with spaces to format the output
	string counter_length(c_length, ' ');
	string counter_length_div(c_length, '-');
	string blank_year(YEAR_LINE_LIMIT, ' '), blank_month(MONTH_LINE_LIMIT, ' '), blank_days(DAYS_LINE_LIMIT, ' '), blank_money(MONEY_LINE_LIMIT, ' '), blank_town(TOWN_LINE_LIMIT, ' ');
	string emp_divider(TABLE_TRIP_HEADER.size() - 3, '-');
	string surname_temp_length(F_I_O_LINE_LIMIT - (emp[curr_emp].surname).size(), ' ');
	string name_temp_length(F_I_O_LINE_LIMIT - (emp[curr_emp].name).size(), ' ');
	string year_temp_length(YEAR_LINE_LIMIT - to_string(emp[curr_emp].year).size(), ' ');
	string month_temp_length(MONTH_LINE_LIMIT - (emp[curr_emp].month).size(), ' ');
	string days_temp_length(DAYS_LINE_LIMIT - to_string(emp[curr_emp].trip_length).size(), ' ');
	string money_temp_length((MONEY_LINE_LIMIT - (doubleToString(emp[curr_emp].money_per_day).size() + (emp[curr_emp].currency).size()+1)), ' ');
	string town_temp_length(TOWN_LINE_LIMIT - (emp[curr_emp].town).size(), ' ');

	cout<< "|" << emp[curr_emp].surname << surname_temp_length
		<< "|" << emp[curr_emp].year << year_temp_length
		<< "|" << emp[curr_emp].month << month_temp_length
		<< "|" << emp[curr_emp].trip_length << days_temp_length
		<< "|" << doubleToString(emp[curr_emp].money_per_day) <<" "<< emp[curr_emp].currency << money_temp_length
		<< "|" << emp[curr_emp].town << town_temp_length << "|" << endl
		<<counter_length<< "|" << emp[curr_emp].name << name_temp_length
		<< "|" << blank_year << "|" << blank_month << "|" << blank_days << "|" << blank_money << "|" << blank_town <<"|"<< endl;

	if (emp[curr_emp].patronymic != "-") //printing patronymic if such exists
	{
		string patronymic_temp_length(F_I_O_LINE_LIMIT - emp[curr_emp].patronymic.size(), ' ');
		cout <<counter_length<< "|" << emp[curr_emp].patronymic << patronymic_temp_length
			<< "|" << blank_year << "|" << blank_month << "|" << blank_days << "|" << blank_money << "|" << blank_town <<"|"<< endl;
	}
	cout <<counter_length_div<< "|" << emp_divider << "|\n";
}

string doubleToString(double value)
{
	value = ceil(value * 100.0) / 100.0;
	string result,temp= to_string(value);
	int s_size=temp.size();
	for (int curr_symb = 0; curr_symb < s_size-3; curr_symb++)
	{
		result.push_back(temp[curr_symb]);
		if (temp[curr_symb] == '.'|| temp[curr_symb] == ',')
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
	showTripArray(emp);
	string input_month=check4TooBigString(MONTH_LINE_LIMIT,onlyLetterInput, ENTER_MONTH);
	if (input_month == NO_INFO) return;
	formatString(input_month);
	vector<Month_Money> value;
	Month_Money temp;
	int amount_of_emp = emp.size();
	for (int curr_emp = 0; curr_emp < amount_of_emp; curr_emp++)
	{
		if (input_month == emp[curr_emp].month) //filling month_money vector with money and currency for input_month
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
		if (value[curr_mon].unique == true) //if currency is unique
		{
			value[curr_mon].unique = false; //no longer unique
			currency_sum = value[curr_mon].money_per_day; //setting the first value of sum
			for (int next_mon = curr_mon + 1; next_mon < value_size; next_mon++)
			{
				if (value[curr_mon].currency == value[next_mon].currency) //looking 4 the same currency
				{
					currency_sum += value[next_mon].money_per_day; //adding money of the same currency to the sum
					value[next_mon].unique = false; //turning uniqueness of such unit to false
				}
			}
			result += to_string(currency_sum) + value[curr_mon].currency + ", "; //result string: "value_1_sum CURRENCY_1, value_2_sum CURRENCY_2..." 
		}
	}
	if (value[value_size - 1].unique == true) //if the last unit's currency is unique
	{
		result += to_string(value[value_size - 1].money_per_day) + value[value_size - 1].currency;
	}
	return result;
}

void sortTowns(vector<Trip_Man> emp)
{
	clearScreen();
	showTripArray(emp);
	string month_x, month_y;
	int year_x=0, year_y=0;
	int X = 0, Y = 0;
	X = enterMonth(emp,ENTER_MONTH_X, month_x);
	year_x = inputIntNumbers(ENTER_YEAR,YEAR_LINE_LIMIT);
	Y = enterMonth(emp,ENTER_MONTH_Y, month_y);
	year_y = inputIntNumbers(ENTER_YEAR,YEAR_LINE_LIMIT);
	if (year_x > year_y) swap(year_x, year_y); // if user firstly entered bigger year, swaps them
	vector<Town_Frequency> town_set, picked_towns;
	fillTowns2SortArray(town_set, emp, year_x, year_y, X, Y); //writing town_set array
	writeTownsInSortArray(town_set, picked_towns);
	mySort(picked_towns,&Town_Frequency::frequency);
	showSortedTowns(picked_towns, X, Y,year_x,year_y,emp);
}

int enterMonth(vector<Trip_Man> emp,string message, string& month)
{
	while (true)
	{
		clearScreen();
		showTripArray(emp);
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
		else if (!counter) //if counter remained 0, which means there're no numbers in month name
		{
			int temp = convertMonthName2Number(month, str_size);
			if (!temp)
			{
				continue;
			}
			return temp;
		}
		else //if month name is not only numbers or letters
		{
			cout << WRONG_MONTH;
		}
	}
}
int convertMonthName2Number(string& month, int str_size)
{
	while (true)
	{
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
		for (X; X <= 12; X++) //writing towns till the end of the year_x
		{
			write1TownInTownSet(emp, town_set, temp, emp_size, X, year_x);
		}
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
		}
	}
	if (town_set[set_size - 1].unique)
	{
		town_set[set_size - 1].unique = false;
		picked_towns.push_back(town_set[set_size - 1]);
	}
}
//bool sortByFrequency(Town_Frequency first, Town_Frequency second, int choice)
//{
//	return (choice==1)?first.frequency < second.frequency: first.frequency > second.frequency;
//}
void showSortedTowns(vector<Town_Frequency> picked_towns, int X, int Y, int year_x, int year_y, vector<Trip_Man>emp)
{
	int temp_size = picked_towns.size();
	int emp_size = emp.size();
	string month_x, month_y;
	bool flag_x = true, flag_y = true;
	int curr_emp=0;
	for (int curr_emp = 0; curr_emp < emp_size; curr_emp++) //defining month_x and month_y names
	{
		if (emp[curr_emp].month_num == X) //if month_x number matches one in emp array
		{
			month_x = emp[curr_emp].month;
			flag_x = false;
		}
		if (emp[curr_emp].month_num == Y) //if month_y number matches one in emp array
		{
			month_y = emp[curr_emp].month;
			flag_y = false;
		}
		if (!flag_x && !flag_y) break;
	}
	clearScreen();
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
		clearScreen();
		showTripArray(emp);
		int choice = inputIntNumbers(SEARCH_MENU,0,10);
		switch (choice)
		{
	/*	case 1: searchData(ENTER_SURNAME,emp,counter,searchBySurname); break;
		case 2: searchData(ENTER_NAME,emp,counter,searchByName); break;
		case 3: searchData(ENTER_PATRONYMIC,emp,counter,searchByPatronymic); break;
		case 4: searchData(ENTER_TOWN,emp,counter,searchByTown); break;
		case 5: searchData(ENTER_MONTH,emp,counter,searchByMonth); break;*/
		case 1: searchData(ENTER_SURNAME, emp,&Trip_Man::surname,counter); break;
		case 2: searchData(ENTER_NAME, emp,&Trip_Man::name, counter); break;
		case 3: searchData(ENTER_PATRONYMIC, emp,&Trip_Man::patronymic, counter); break;
		case 4: searchData(ENTER_TOWN, emp,&Trip_Man::town, counter); break;
		case 5: searchData(ENTER_MONTH, emp,&Trip_Man::month, counter); break;
		case 6: searchData(ENTER_MONTH, emp, &Trip_Man::month_num, counter); break;
		case 7: searchData(ENTER_YEAR, emp, &Trip_Man::year, counter); break;
		case 8: searchData(ENTER_MONEY, emp, &Trip_Man::money_per_day, counter); break;
		case 9: searchData(ENTER_CURRENCY, emp, &Trip_Man::currency, counter); break;
		case 10: searchData(ENTER_DAYS, emp, &Trip_Man::trip_length, counter); break;
		case 0: return;
		}
	} while (!wantToGoBack());
}

template<typename T>
void searchData(string message, vector<Trip_Man>& emp,T Trip_Man::*field,int& counter)
{
	clearScreen();
	showTripArray(emp);
	cout << message;
	string search_input = oneWordInput(numberOrLetterInput);
	int emp_size = emp.size();
	int search_size = 0;
	clearScreen();
	cout << "--№--"<<TABLE_TRIP_HEADER;
	for (int curr_emp = 0; curr_emp < emp_size; curr_emp++)
	{
		search_size = defineSearchSize(search_input, emp, field, curr_emp);
		for (int current_letter = 0; current_letter < search_size; current_letter++)
		{
			/*if (searchCondition(search_input,current_letter,emp,curr_emp))*/
			if (!doLettersMatch(search_input,current_letter,emp,field,curr_emp))
			{
				break;
			}
			string counter_length(COUNTER_LENGTH_LIMIT - to_string(emp[curr_emp].search_counter).size(), ' ');
			cout << counter_length << emp[curr_emp].search_counter++;
			counter++;
			showOneEmployee(emp, curr_emp,COUNTER_LENGTH_LIMIT);
			break;
		}
	}
}
template <typename T>
int defineSearchSize(string search_input, vector<Trip_Man>& emp, T Trip_Man::* field, int curr_emp)
{
	return (search_input.size() < to_string(emp[curr_emp].*field).size()) ? search_input.size() : to_string(emp[curr_emp].*field).size();
}
int defineSearchSize(string search_input, vector<Trip_Man>& emp, string Trip_Man::* field, int curr_emp)
{
	return (search_input.size() < (emp[curr_emp].*field).size()) ? search_input.size() : (emp[curr_emp].*field).size();
}
template <typename T>
bool doLettersMatch(string search_input, int current_letter, vector<Trip_Man>& emp, T Trip_Man::* field, int curr_emp)
{
	return search_input[current_letter] == to_string(emp[curr_emp].*field)[current_letter];
}
bool doLettersMatch(string search_input, int current_letter, vector<Trip_Man>& emp, string Trip_Man::* field, int curr_emp)
{
	return search_input[current_letter] == (emp[curr_emp].*field)[current_letter];
}
//bool searchBySurname(string search_input, int current_letter, vector<Trip_Man> emp, int curr_emp)
//{
//	return search_input[current_letter] != emp[curr_emp].surname[current_letter];
//}
//bool searchByName(string search_input, int current_letter, vector<Trip_Man> emp, int curr_emp)
//{
//	return search_input[current_letter] != emp[curr_emp].name[current_letter];
//}
//bool searchByPatronymic(string search_input, int current_letter, vector<Trip_Man> emp, int curr_emp)
//{
//	return search_input[current_letter] != emp[curr_emp].patronymic[current_letter];
//}
//bool searchByTown(string search_input, int current_letter, vector<Trip_Man> emp, int curr_emp)
//{
//	return search_input[current_letter] != emp[curr_emp].town[current_letter];
//}
//bool searchByMonth(string search_input, int current_letter, vector<Trip_Man> emp, int curr_emp)
//{
//	return search_input[current_letter] != emp[curr_emp].month[current_letter];
//}

void sortMenu(vector<Trip_Man> emp)
{
	do
	{
		clearScreen();
		showTripArray(emp);
		int choice = inputIntNumbers(SORT_MENU,0, 9);
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
	} while (!wantToGoBack());
}

template <typename T>
void sortData(string message, vector<Trip_Man>emp, T Trip_Man::* temp)
{
	int choice = inputIntNumbers(SORT_DIRECTION,1, 2);
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
//bool sortBySurname(Trip_Man first, Trip_Man second, int choice)
//{
//	return (choice == 1) ? first.surname < second.surname : first.surname > second.surname;
//}
//bool sortByName(Trip_Man first, Trip_Man second, int choice)
//{
//	return (choice==1) ? first.name < second.name: first.name > second.name;
//}
//bool sortByPatronymic(Trip_Man first, Trip_Man second, int choice)
//{
//	return (choice == 1) ? first.patronymic < second.patronymic : first.patronymic > second.patronymic;
//}
//bool sortByDays(Trip_Man first, Trip_Man second, int choice)
//{
//	return (choice == 1) ? first.trip_length < second.trip_length : first.trip_length > second.trip_length;
//}
//bool sortByMoney(Trip_Man first, Trip_Man second, int choice)
//{
//	return (choice == 1) ? first.money_per_day < second.money_per_day : first.money_per_day > second.money_per_day;
//}
//bool sortByMonth(Trip_Man first, Trip_Man second, int choice)
//{
//	return (choice == 1) ? first.month_num < second.month_num : first.month_num > second.month_num;
//}
//bool sortByCurrency(Trip_Man first, Trip_Man second, int choice)
//{
//	return (choice == 1) ? first.currency < second.currency : first.currency > second.currency;
//}
//bool sortByTown(Trip_Man first, Trip_Man second, int choice)
//{
//	return (choice == 1) ? first.town < second.town : first.town > second.town;
//}

void addData(vector<Trip_Man>&emp)
{
	enterEmployees(emp);
	writeTripFile(emp);
}

void pickDataInArray(string message, vector<Trip_Man>& emp, void (*changeData)(vector<Trip_Man>& emp, int curr_emp))
{
	clearScreen();
	showTripArray(emp);
	int counter = 1; //counter
	searchMenu(emp,counter);
	int choice = inputIntNumbers(message,1, counter);
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
	int sure = inputIntNumbers(YOU_SURE,1, 2);
	if (sure == 1)
	{
		clearScreen();
		showTripArray(emp);
		int choice = inputIntNumbers(EDIT_DATA_MENU,0, 10);
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
	clearScreen();
	showTripArray(emp);
	cout << message;
	inputNewData(emp[curr_emp]);
}

void formatString(string& temp)
{
	int str_size = temp.size();
	temp[0] = toupper(temp[0]);
	int curr_symb = 1;
	while(curr_symb < str_size)
	{
		temp[curr_symb] = tolower(temp[curr_symb]);
		if ((temp[curr_symb] == '-' || temp[curr_symb] == '_') && curr_symb < str_size - 1)
		{
			temp[curr_symb + 1] = toupper(temp[curr_symb + 1]);
			curr_symb ++;
		}
		curr_symb++;
	}
}

void inputSurname(Trip_Man& temp)
{
	temp.surname = check4TooBigString(F_I_O_LINE_LIMIT,onlyLetterInput,ENTER_SURNAME);
	if (temp.surname == NO_INFO) return;
	formatString(temp.surname);
}
void inputName(Trip_Man& temp)
{
	temp.name = check4TooBigString(F_I_O_LINE_LIMIT,onlyLetterInput,ENTER_NAME);
	if (temp.name == NO_INFO) return;
	formatString(temp.name);
}
void inputPatronymic(Trip_Man& temp)
{
	while (true)
	{
		temp.patronymic = check4TooBigString(F_I_O_LINE_LIMIT, onlyLetterInput, ENTER_PATRONYMIC);
		if (temp.patronymic == NO_INFO) return;
		string tempor = temp.patronymic;
		int tempor_size = tempor.size();
		for (int curr_char = 0; curr_char < tempor_size; curr_char++)
		{
			tempor.at(curr_char) = tolower(tempor.at(curr_char));
		}
		if (tempor == "no" || temp.patronymic == "нет") //no means employee got no patronymic
		{
			temp.patronymic = "-";
			break;
		}
		else
		{
			int sure = inputIntNumbers(YOU_SURE,1, 2);
			if (sure == 2)
			{
				temp.patronymic = check4TooBigString(F_I_O_LINE_LIMIT, onlyLetterInput,ENTER_PATRONYMIC);
				if (temp.patronymic == NO_INFO) return;
				break;
			}
			break;
		}
	}
	if (temp.patronymic!="-") formatString(temp.patronymic);
}
void inputYear(Trip_Man& temp)
{
	temp.year = inputIntNumbers(ENTER_YEAR,YEAR_LINE_LIMIT);
}
void inputMonth(Trip_Man& temp)
{
	temp.month = check4TooBigString(MONTH_LINE_LIMIT,onlyLetterInput,ENTER_MONTH);
	while (!isMonth(temp.month))
	{
		temp.month = check4TooBigString(MONTH_LINE_LIMIT, onlyLetterInput, ENTER_MONTH);
	}
	if (temp.month == NO_INFO) return;
	formatString(temp.month);
	int month_size = temp.month.size();
	temp.month_num = convertMonthName2Number(temp.month, month_size);
}
bool isMonth(string input_month)
{
	formatString(input_month);
	int month_set_size = MONTH_SET.size();
	for (int i = 0; i < month_set_size; i++)
	{
		if (input_month == MONTH_SET.at(i))
		{
			return true;
		}
	}
	cout << WRONG_MONTH;
	return false;
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
	temp.money_per_day = inputDouble(ENTER_MONEY,MONEY_LINE_LIMIT);
	temp.money_per_day = ceil(temp.money_per_day * 100.0) / 100.0;
}
void inputCurrency(Trip_Man& temp)
{
	string curr = check4TooBigString(CURRENCY_LIMIT,onlyLetterInput,ENTER_CURRENCY);
	if (curr == NO_INFO) return;
	int curr_size = curr.size();
	for (int i = 0; i < curr_size; i++)
	{
		temp.currency.push_back(toupper(curr.at(i)));
	}
}
void inputTown(Trip_Man& temp)
{
	temp.town = check4TooBigString(TOWN_LINE_LIMIT,onlyLetterInput,ENTER_TOWN);
	if (temp.town == NO_INFO) return;
	formatString(temp.town);
}

void deleteData(vector<Trip_Man>& emp, int curr_emp)
{
	clearScreen();
	showTripArray(emp);
	int sure = inputIntNumbers(YOU_SURE,1,2);
	if (sure == 1)
	{
		emp.erase(emp.begin() + curr_emp);
	}
	writeTripFile(emp);
}