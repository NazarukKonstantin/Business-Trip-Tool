#pragma once

#include "Accounts.h"
#include <algorithm>

struct Trip_Man
{
	string surname;
	string name;
	string patronymic;
	int year = 0;
	string month;
	int trip_length=0; //amount of days spent on one trip
	string town;
	double money_per_day = 0;

	string currency;
	int month_num=0;

	int search_counter = 0; //necessary for search; is used like indexes for search
};
struct Month_Money //being used to count money sum for the required month
{
	string currency;
	double money=0;
	bool unique = true; //stands for currency uniqueness in system; necessary for sum
};
struct Town_Frequency //being used to sort most visited towns in particular period
{
	string town;
	int frequency = 1; //amount of times the particular town's been visited
	bool unique = true; //stands for town uniqueness in system; necessary for putting non-repeating towns in sort array
};

const string TRIP_INFO = "trip_data.txt";
const string TEST_FILE = "test_info.txt";

const string NO_FILE_ACCESS = "���� ���� ��� ���������� ��� ������. �������� ���������� ��������:\n1.������� ������\n2.������������ �������� ����\n3.������ � ����������\n0.����� �� ���������\n";
//--------------------DATA INPUT MESSAGES-------------------------------------------------------------------------------------------------------------------------
const string ENTER_SURNAME="������� ������� ���������:\n";
const string ENTER_NAME="������� ��� ���������:\n";
const string ENTER_PATRONYMIC="������� �������� ���������(���� � ��������� ��� ��������, ������� \"���\" ��� \"-\")\n";
const string ENTER_YEAR="������� ��� ������������:\n";
const string ENTER_MONTH="������� ����� ������������ (�����):\n";
const string ENTER_MONTH_NAME = "������� �������� ������ ������������:\n";
const string ENTER_TOWN="������� ����� ���������� ������������:\n";
const string ENTER_DAYS="������� ���������� (������ �����) ���������� �� ������������ ����:\n";
const string ENTER_MONEY="������� ���������� (������ �����) ���������� ����� � ������� �� ����:\n";
const string ENTER_CURRENCY = "������� ������ (� ������� USD,EUR,RUB,BYN � �.�.):\n";
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
const string WANT_STOP = "������� ������������?\n 1.��\n 2.���\n";
//------------------------MENU------------------------------------------------------------------------------------------------------------------------------------
const string ACCOUNT_MENU_ROLE_0 = " 1.�������� ���� ����� � ������\n 0.����� � ������� ����\n";
const string TRIP_MENU_ROLE_0 = " 1.����������� ��� ��������������� ������\n 2.���������� ����� ������� ��������������� �� ����� � (�������� � ����������)\n\
 3.������� ������ �������� ����� ���������� ������� � ������ X �� ����� Y (�������� X � Y �������� � ����������)\n 4.����� ������\n 5.������������� ������\n\
 0.����� � ������� ����\n";
const string MAIN_MENU = " 1.������ � ����������\n 2.������ � ���������������� �������\n 0.�����\n";
const string ACCOUNT_MENU_ROLE_1 = " 1.�������� ���� ����� � ������\n 2.����������� ��� ������� ������\n 3.�������� ������� ������\n 4.�������� ������� ������\n\
 5.������� ������� ������\n 0.����� � ������� ����\n";
const string TRIP_MENU_ROLE_1 = " 1.����������� ��� ��������������� ������\n 2.���������� ����� ������� ��������������� �� ����� �\
(�������� � ����������)\n 3.������� ������ �������� ����� ���������� ������� � ������ X �� ����� Y (�������� X � Y �������� � ����������)\n\
 4.����� ������;\n 5.������������� ������\n 6.�������� ������ (��������,��������,�������)\n 0.����� � ������� ����\n";
const string DATA_CHANGE_MENU_ROLE_1 =" 1.�������� ������\n 2.�������� ������\n 3.������� ������\n 0.����� � ���� ������ � ���������������� �������\n";
const string EDIT_DATA_MENU = "��������:\n 1.�������\n 2.���\n 3.��������\n 4.���\n 5.�����\n 6.���-�� ���� ������������\n 7.����� �� ����\n\
 8.������\n 9.����� ����������\n 10.��� ������ � ����������\n 0.��������� � ���� ��������� ������\n";
const string SEARCH_MENU="������ ������ ��:\n 1.�������\n 2.����� \n 3.��������\n 4.������ ����������\n 5.������ �������(�������� ������)\n\
 6.������ �������(�����)\n 7.���� �������\n 8.����� � ���� �� �������\n 9.������\n 10.������������ �������(� ����)\n 0.����� � ���� ������ � ���������������� �������\n";
const string SORT_MENU="����������� ������ ��:\n 1.�������\n 2.�����\n 3.��������\n 4.������������ ������������(� ����)\n\
 5.����� ��������������� �������� � ����\n 6.������\n 7.�������\n 8.�����\n 9.�������\n 0.����� � ���� ������ � ���������������� �������\n";
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
const string F_I_O_HEADER="-------|�.�.�.|-------";
const string YEAR_HEADER="-|���|-";
const string MONTH_HEADER="---|�����|---";
const string DAYS_HEADER="-|���� �������|-";
const string MONEY_HEADER="-|����� �� ����|-";
const string TOWN_HEADER="-|����� ����������|-";
const string SURNAME_HEADER = "-------|�������|------";
const string NAME_HEADER = "---------|���|--------";
const string PATRONYMIC_HEADER = "------|��������|------";
const string TABLE_TRIP_HEADER = { "|" + F_I_O_HEADER + "|" + YEAR_HEADER + "|" + MONTH_HEADER + "|" + DAYS_HEADER + "|" + MONEY_HEADER + "|" + TOWN_HEADER + "|\n" };

const string MONEY_RES_P1 = "���������� ����� �� ";
const string MONEY_RES_P2 = "-�� ���� ���������: ";

const string ENTER_MONTH_X = "������� ����� X (����� ������, � �������� ������� ���������� �������): \n";
const string ENTER_MONTH_Y = "������� ����� Y (����� ������, ������� ���������� ���������� �������): \n";
const string SORTED_TOWNS_P1 = "�������� ���������� ������ � ������ ";
const string SORTED_TOWNS_P2 = "-�� ���� �� ����� ";
const string SORTED_TOWNS_P3 = "-�� ����:\n";
const string TOWN_TABLE_HEADER = "|-------|�����|------|-|���-�� ���������|-|\n";

const string SORT_DIRECTION = "����������� ��:\n 1.�����������\n 2.��������\n";
const string SORTED_BY = "������ ����������, ���������������� �� ";
const string SB_SURNAME="�������:\n";
const string SB_NAME="�����:\n";
const string SB_PATRONYMIC="��������:\n";
const string SB_DAYS="������������ ������������ (� ����):\n";
const string SB_MONEY="����� ��������������� �������� � ����:\n";
const string SB_CURRENCY = "������:\n";
const string SB_MONTH="�������:\n";
const string SB_YEAR = "�����:\n";
const string SB_TOWN="�������:\n";

const vector<string> MONTH_SET = {"������","�������","����","������","���","����","����","������","��������","�������","������","�������"};

const string WRONG_DAYS_P1 = "������! � ������ ������ ";
const string WRONG_DAYS_P2 = " �� ���������� ����� ���-�� ����\n";

const string NO_DATA_FOUND = "������, ��������������� �������, �� �������\n";

//-----NUMERIC CONSTANTS-------
//-----TABLE LINE LIMITS-------
const int F_I_O_LINE_LIMIT = 22;
const int YEAR_LINE_LIMIT = 7;
const int MONTH_LINE_LIMIT = 13;
const int DAYS_LINE_LIMIT = 16;
const int MONEY_LINE_LIMIT = 14;
const int MONEY_LINE_LIMIT_2 = 21;
const int TOWN_LINE_LIMIT = 20;
const int CURRENCY_LIMIT = 3;
const int FREQUENCY_LINE_LIMIT = 20;

const int YEAR_INPUT_LIM = 4; //max reasonable digits of year number to input

bool canUserContinue(Account& guest, bool exit_token); //checks user's access and log-in condition to let user use the system

void enterEmployees(vector <Trip_Man>& emp); //also calls enter1Employee()
void enter1Employee(Trip_Man& temp);

void processTripFile(vector<Account>& acc, Account& guest,vector <Trip_Man>& emp,bool& is_file_open, bool& exit_token,string file_name=TRIP_INFO); //reading file with unable to read file situation management
void readTripFile(vector <Trip_Man>& emp, bool& is_file_open, string file_name);
int countStructuresInTripFile(bool& is_file_open,string file_name); // counts amount of structures in file
void writeTripFile(vector<Trip_Man> emp);

void processMainMenu(vector <Trip_Man>& emp,vector<Account>& acc, Account& guest, bool& exit_token);
void processAccountMenu(vector<Account>& acc, Account& guest, bool& exit_token);
void processTripMenu(vector<Trip_Man>&emp, Account guest);
void processDataChangeMenu(vector<Trip_Man>& emp);

void tripHeaderOutput(int c_length = 0, string counter="");
void showTripArray(vector<Trip_Man>emp); //shows data array
string doubleToString(double value); //converts double value to string with two decimals after comma
void showOneEmployee(vector<Trip_Man>emp,int curr_emp, int c_length = 0);
void showOneEmployee(string surname=SURNAME_HEADER, string name=NAME_HEADER, string patronymic=PATRONYMIC_HEADER, string year = YEAR_HEADER, string month = MONTH_HEADER,
					string days=DAYS_HEADER, string money = MONEY_HEADER, string currency = "***", string town = TOWN_HEADER); //is used for adding employees
void countMoney4MonthX(vector<Trip_Man> emp); //also calls countMoney()
string countMoney(vector<Month_Money> value);

void sortTowns(vector<Trip_Man> emp); //function performing individual task - sorting most visited towns from month X to month Y
int enterMonth(vector<Trip_Man> emp,string message, string& month); //month X and month Y input
//fillTowns2TownSet - filling town set with towns (calls write1TownInTownSet()) visited since month X of year X till month Y of year_y
void fillTowns2TownSet(vector<Town_Frequency>& town_set,vector<Trip_Man> emp, int year_x, int year_y, int X, int Y);
//write1TownInTownSet - writes one town in town set
void write1TownInTownSet(vector<Trip_Man> emp, vector<Town_Frequency>& town_set, Town_Frequency temp, int emp_size, int X, int year_x);
//writeTownsInSortArray - filling new array with unique towns of town_set array
void writeTownsInSortArray(vector<Town_Frequency> town_set, vector<Town_Frequency>&picked_towns);
void showSortedTowns(vector<Town_Frequency> picked_towns, string month_x, string month_y, int year_x, int year_y, vector<Trip_Man>emp);

void searchMenu(vector<Trip_Man>& emp,int& counter);

template<typename T>
void searchData(string message, vector<Trip_Man>& emp, T Trip_Man::* field, int& counter, 
	bool (*searchCondition) (vector<Trip_Man> emp, T Trip_Man::* field, string search_input, int curr_emp),
	char(*inputCondition)() = onlyLetterInput);

bool searchString(vector<Trip_Man> emp, string Trip_Man::* field, string search_input, int curr_emp);
bool searchInt(vector<Trip_Man> emp, int Trip_Man::* field, string search_input, int curr_emp);
bool searchDouble(vector<Trip_Man> emp, double Trip_Man::* field, string search_input, int curr_emp);

void sortMenu(vector<Trip_Man> emp);
template <typename T>
void sortData(string message, vector<Trip_Man>emp, T Trip_Man::* temp); //let user choose direction of sorting and calls mySort()

template <typename T, typename J>
void mySort(vector<J>&vec, T J::* temp, int direction=1);

void pickDataInArray(string message, vector<Trip_Man>& emp, void (*changeData)(vector<Trip_Man>& emp, int curr_emp)); //in edit and delete cases makes user choose data to edit/delete
void editDataMenu(vector<Trip_Man>& emp, int curr_emp);
void formatString(string& temp); //makes strings start with a capital letter and end with small ones; also works with complex names like New-York and so on
void inputSurname(Trip_Man& temp);
void inputName(Trip_Man& temp);
void inputPatronymic(Trip_Man& temp); //also asks if employee's got patronymic
void inputYear(Trip_Man& temp);
void inputMonth(Trip_Man& temp);
void inputDays(Trip_Man& temp);
void inputMoney(Trip_Man& temp);
void inputCurrency(Trip_Man& temp);
void inputTown(Trip_Man& temp);

void deleteData(vector<Trip_Man>& emp, int curr_emp);