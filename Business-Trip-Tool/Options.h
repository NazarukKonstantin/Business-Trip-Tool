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
	int trip_length=0;
	string town;
	double money_per_day = 0;

	string currency;
	int month_num=0;

	int search_counter = 1;
};
struct Month_Money
{
	string currency;
	double money_per_day=0;
	bool unique = true;
};
struct Town_Frequency
{
	string town;
	int frequency = 1;
	bool unique = true;
};

const string TRIP_INFO = "trip_data.txt";

const string NO_FILE_ACCESS = "���� ���� ��� ���������� ��� ������. �������� ���������� ��������:\n1.������� ������.\n2.����� �� ���������\n";
//--------------------DATA INPUT MESSAGES-------------------------------------------------------------------------------
const string ENTER_SURNAME="������� ������� ���������:\n";
const string ENTER_NAME="������� ��� ���������:\n";
const string ENTER_PATRONYMIC="������� �������� ���������(���� � ��������� ��� ��������, ������� \"No\")\n";
const string ENTER_YEAR="������� ��� ������������:\n";
const string ENTER_MONTH="������� ����� ������������:\n";
const string ENTER_TOWN="������� ����� ���������� ������������:\n";
const string ENTER_DAYS="������� ���������� (������ �����) ���������� �� ������������ ����:\n";
const string ENTER_MONEY="������� ���������� (������ �����) ���������� ����� � ������� �� ����:\n";
const string ENTER_CURRENCY = "������� ������ (� ������� USD,EUR,RUB,BYN � �.�.):\n";
//--------------------------------------------------------------------------------------------------------------
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
 4.����� ������;\n 5.������������� ������\n 6.�������� ������\n 0.����� � ������� ����\n";
const string DATA_CHANGE_MENU_ROLE_1 = " 1.�������� ������\n 2.�������� ������\n 3.������� ������\n 0.����� � ���� ������ � ���������������� �������\n";
const string EDIT_DATA_MENU = "��������:\n 1.�������\n 2.���\n 3.��������\n 4.���\n 5.�����\n 6.���-�� ���� ������������\n 7.����� �� ����\n\
 8.������\n 9.����� ����������\n 10.��� ������ � ����������\n 0.��������� � ���� ��������� ������\n";
const string SEARCH_MENU="������ ������ ��:\n 1.�������\n 2.����� \n3.��������\n 4.������ ����������\n 5.������ �������\n 0.����� � ���� ������ � ���������������� �������\n";
const string SORT_MENU="����������� ������ ��:\n 1.�������\n 2.�����\n 3.��������\n 4.������������ ������������(� ����)\n\
 5.����� ��������������� �������� � ����\n 0.����� � ���� ������ � ���������������� �������\n";
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
const string TABLE_TRIP_HEADER = "|-------|�.�.�.|-------|---|���|---|---|�����|---|-|���-�� ���� �������|-|-|����� �� ����|-|-------|�����|-------|\n";

const string MONEY_RES = "���������� ����� �� ��������� ����� ���������: ";

const string ENTER_MONTH_X = "������� ����� X (�������� ��� ����� ������, � �������� ������� ���������� �������): \n";
const string ENTER_MONTH_Y = "������� ����� Y (�������� ��� ����� ������, ������� ���������� ���������� �������): \n";
const string SORTED_TOWNS_P1 = "�������� ���������� ������ � ������ \"";
const string SORTED_TOWNS_P2 = "\" ";
const string SORTED_TOWNS_P3 = " ���� �� ����� \"";
const string SORTED_TOWNS_P4 = " ����:\n";
const string TOWN_TABLE_HEADER = "|-------|�����|-------|-|���-�� ���������|-|\n";

const string SORT_DIRECTION = "����������� ��:\n 1.�����������\n 2.��������\n";
const string SORTED_BY = "������ ����������, ���������������� �� ";
const string SB_SURNAME="�������:\n";
const string SB_NAME="�����:\n";
const string SB_PATRONYMIC="��������:\n";
const string SB_DAYS="������������ ������������ (� ����):\n";
const string SB_MONEY="����� ��������������� �������� � ����\n";

const string WRONG_MONTH = "�������� ������ ������� �������, ���������� ��� ���:\n";

//-----NUMERIC CONSTANTS-------
const int F_I_O_LINE_LIMIT = 22;
const int YEAR_LINE_LIMIT = 11;
const int MONTH_LINE_LIMIT = 13;
const int DAYS_LINE_LIMIT = 21;
const int MONEY_LINE_LIMIT = 14;
const int TOWN_LINE_LIMIT = 21;
const int CURRENCY_LIMIT = 3;
const int FREQUENCY_LINE_LIMIT = 20;

bool canUserContinue(Account& guest, bool exit_token);

void checkPatronymic(Trip_Man& temp);

void enterEmployees(vector <Trip_Man>& emp);
void enter1Employee(Trip_Man& temp);

void processTripFile(vector <Trip_Man>& emp,bool is_file_open, bool& exit_token);
void readTripFile(vector <Trip_Man>& emp, bool& is_file_open);
int countStructuresInTripFile(bool& is_file_open);
void writeTripFile(vector<Trip_Man> emp);
void writeEndTripFile(Trip_Man new_emp);

void processMainMenu(vector <Trip_Man>& emp,vector<Account>& acc, Account& guest);
void processAccountMenu(vector<Account>& acc, Account& guest);
void processTripMenu(vector<Trip_Man> emp, Account guest);
void processDataChangeMenu(vector<Trip_Man>& emp);

void showTripArray(vector<Trip_Man>emp);
void showOneEmployee(vector<Trip_Man>emp, int curr_emp);
void countMoney4MonthX(vector<Trip_Man> emp);
string countMoney(vector<Month_Money> value);

void sortTowns(vector<Trip_Man> emp);

int enterMonth(string message, string& month);
int convertMonthName2Number(string month, int str_size);
void fillTowns2SortArray(vector<Town_Frequency>& town_set,vector<Trip_Man> emp, int year_x, int year_y, int X, int Y);
void write1TownInTownSet(vector<Trip_Man> emp, vector<Town_Frequency>& town_set, Town_Frequency temp, int emp_size, int X, int year_x);
void writeTownsInSortArray(vector<Town_Frequency> town_set, vector<Town_Frequency>& picked_towns);
bool sortByFrequency(Town_Frequency first, Town_Frequency second);
void showSortedTowns(vector<Town_Frequency> picked_towns, int X, int Y, int year_x, int year_y, vector<Trip_Man>emp);

void searchMenu(vector<Trip_Man> emp,int& counter);
void searchData(string message, vector<Trip_Man>& emp, int& counter, bool(*searchCondition)(string search_input, int current_letter, vector<Trip_Man> emp, int curr_emp));
bool searchBySurname(string search_input, int current_letter, vector<Trip_Man> emp, int curr_emp);
bool searchByName(string search_input, int current_letter, vector<Trip_Man> emp, int curr_emp);
bool searchByPatronymic(string search_input, int current_letter, vector<Trip_Man> emp, int curr_emp);
bool searchByTown(string search_input, int current_letter, vector<Trip_Man> emp, int curr_emp);
bool searchByMonth(string search_input, int current_letter, vector<Trip_Man> emp, int curr_emp);

void sortMenu(vector<Trip_Man> emp);
void sortData(string message, vector<Trip_Man>emp, bool(*sortCondition)(Trip_Man first, Trip_Man second));
bool sortBySurname(Trip_Man first, Trip_Man second);
bool sortByName(Trip_Man first, Trip_Man second);
bool sortByPatronymic(Trip_Man first, Trip_Man second);
bool sortByDays(Trip_Man first, Trip_Man second);
bool sortByMoney(Trip_Man first, Trip_Man second);
void mySort4Decending(vector<Trip_Man> emp, bool (*sortCondition)(Trip_Man first, Trip_Man second));

void addData(vector<Trip_Man>& emp);

void pickDataInArray(string message, vector<Trip_Man>& emp, void (*changeData)(vector<Trip_Man>& emp, int curr_emp));
void editDataMenu(vector<Trip_Man>& emp, int curr_emp);
void editData(string message, vector<Trip_Man>& emp, int curr_emp, void(*inputNewData)(Trip_Man& temp));
void inputSurname(Trip_Man& temp);
void inputName(Trip_Man& temp);
void inputPatronymic(Trip_Man& temp);
void inputYear(Trip_Man& temp);
void inputMonth(Trip_Man& temp);
void inputDays(Trip_Man& temp);
void inputMoney(Trip_Man& temp);
void inputCurrency(Trip_Man& temp);
void inputTown(Trip_Man& temp);

void deleteData(vector<Trip_Man>& emp, int curr_emp);