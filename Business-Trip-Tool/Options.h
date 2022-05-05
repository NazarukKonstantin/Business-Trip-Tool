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

const string NO_FILE_ACCESS = "Файл пуст или недоступен для чтения. Выберите дальнейшее действие:\n1.Вписать данные.\n2.Выйти из программы\n";
//--------------------DATA INPUT MESSAGES-------------------------------------------------------------------------------
const string ENTER_SURNAME="Введите фамилию работника:\n";
const string ENTER_NAME="Введите имя работника:\n";
const string ENTER_PATRONYMIC="Введите отчество работника(если у работника нет отчества, введите \"No\")\n";
const string ENTER_YEAR="Введите год командировки:\n";
const string ENTER_MONTH="Введите месяц командировки:\n";
const string ENTER_TOWN="Введите город назначения командировки:\n";
const string ENTER_DAYS="Введите количество (только число) выделенных на командировку дней:\n";
const string ENTER_MONEY="Введите количество (только число) выделенной суммы в расчёте на день:\n";
const string ENTER_CURRENCY = "Введите валюту (в формате USD,EUR,RUB,BYN и т.д.):\n";
//--------------------------------------------------------------------------------------------------------------
const string WANT_STOP = "Желаете остановиться?\n 1.Да\n 2.Нет\n";
//------------------------MENU------------------------------------------------------------------------------------------------------------------------------------
const string ACCOUNT_MENU_ROLE_0 = " 1.Изменить свой логин и пароль\n 0.Выйти в главное меню\n";
const string TRIP_MENU_ROLE_0 = " 1.Просмотреть все командировочные данные\n 2.Определить общие выплаты командировочных за месяц Х (вводится с клавиатуры)\n\
 3.Вывести список наиболее часто посещаемых городов с месяца X по месяц Y (значения X и Y вводятся с клавиатуры)\n 4.Найти данные\n 5.Отсортировать данные\n\
 0.Выйти в главное меню\n";
const string MAIN_MENU = " 1.Работа с аккаунтами\n 2.Работа с командировочными данными\n 0.Выход\n";
const string ACCOUNT_MENU_ROLE_1 = " 1.Изменить свой логин и пароль\n 2.Просмотреть все учётные записи\n 3.Добавить учётную запись\n 4.Изменить учётную запись\n\
 5.Удалить учётную запись\n 0.Выйти в главное меню\n";
const string TRIP_MENU_ROLE_1 = " 1.Просмотреть все командировочные данные\n 2.Определить общие выплаты командировочных за месяц Х\
(вводится с клавиатуры)\n 3.Вывести список наиболее часто посещаемых городов с месяца X по месяц Y (значения X и Y вводятся с клавиатуры)\n\
 4.Найти данные;\n 5.Отсортировать данные\n 6.Изменить данные\n 0.Выйти в главное меню\n";
const string DATA_CHANGE_MENU_ROLE_1 = " 1.Добавить запись\n 2.Изменить запись\n 3.Удалить запись\n 0.Выйти в меню работы с командировочными данными\n";
const string EDIT_DATA_MENU = "Изменить:\n 1.Фамилию\n 2.Имя\n 3.Отчество\n 4.Год\n 5.Месяц\n 6.Кол-во дней командировки\n 7.Сумму на день\n\
 8.Валюту\n 9.Город назначения\n 10.Все данные о сотруднике\n 0.Вернуться в меню изменения данных\n";
const string SEARCH_MENU="Искать данные по:\n 1.Фамилии\n 2.Имени \n3.Отчеству\n 4.Городу назначения\n 5.Месяцу поездки\n 0.Выход в меню работы с командировочными данными\n";
const string SORT_MENU="Сортировать данные по:\n 1.Фамилии\n 2.Имени\n 3.Отчеству\n 4.Длительности командировки(в днях)\n\
 5.Сумме командировочных расходов в день\n 0.Выйти в меню работы с командировочными данными\n";
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
const string TABLE_TRIP_HEADER = "|-------|Ф.И.О.|-------|---|ГОД|---|---|МЕСЯЦ|---|-|КОЛ-ВО ДНЕЙ ПОЕЗДКИ|-|-|СУММА НА ДЕНЬ|-|-------|ГОРОД|-------|\n";

const string MONEY_RES = "Выделенная сумма за указанный месяц составила: ";

const string ENTER_MONTH_X = "Введите месяц X (название или номер месяца, с которого начнётся сортировка городов): \n";
const string ENTER_MONTH_Y = "Введите месяц Y (название или номер месяца, которым закончится сортировка городов): \n";
const string SORTED_TOWNS_P1 = "Наиболее посещаемые города с месяца \"";
const string SORTED_TOWNS_P2 = "\" ";
const string SORTED_TOWNS_P3 = " года по месяц \"";
const string SORTED_TOWNS_P4 = " года:\n";
const string TOWN_TABLE_HEADER = "|-------|ГОРОД|-------|-|КОЛ-ВО ПОСЕЩЕНИЙ|-|\n";

const string SORT_DIRECTION = "Сортировать по:\n 1.Возрастанию\n 2.Убыванию\n";
const string SORTED_BY = "Список работников, отстортированный по ";
const string SB_SURNAME="фамилии:\n";
const string SB_NAME="имени:\n";
const string SB_PATRONYMIC="отчеству:\n";
const string SB_DAYS="длительности командировки (в днях):\n";
const string SB_MONEY="сумме командировочных расходов в день\n";

const string WRONG_MONTH = "Название месяца введено неверно, попробуйте ещё раз:\n";

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