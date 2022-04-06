#pragma once

#include "Accounts.h"

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
};
struct Month_Money
{
	string currency;
	double money_per_day;
	bool unique = true;
};

const string TRIP_INFO = "trip_data.txt";

const string NO_FILE_ACCESS = "Файл пуст или недоступен для чтения. Выберите дальнейшее действие:\n1.Вписать данные.\n2.Выйти из программы\n";

const string ENTER_SURNAME="Введите фамилию работника:\n";
const string ENTER_NAME="Введите имя работника:\n";
const string ENTER_PATRONYMIC="Введите отчество работника(если у работника нет отчества, введите \"No\")\n";
const string ENTER_YEAR="Введите год командировки:\n";
const string ENTER_MONTH="Введите месяц командировки:\n";
const string ENTER_TOWN="Введите город назначения командировки:\n";
const string ENTER_DAYS="Введите количество (только число) выделенных на командировку дней:\n";
const string ENTER_MONEY="Введите количество (только число) выделенной суммы в расчёте на день:\n";
const string ENTER_CURRENCY = "Введите валюту (в формате USD,EUR,RUB,BYN и т.д.):\n";

const string WANT_STOP = "Желаете остановиться?\n1.Да\n2.Нет\n";

const string ACCOUNT_MENU_ROLE_0 = "1.Изменить свой логин и пароль;\n0.Выйти в главное меню\n";
const string TRIP_MENU_ROLE_0 = "1.Просмотреть все командировочные данные;\n2.Определить общие выплаты командировочных за месяц Х (вводится с клавиатуры);\n\
3.Вывести список наиболее часто посещаемых городов с месяца X по месяц Y (значения X и Y вводятся с клавиатуры);\n4.Найти данные;\n5.Отсортировать данные;\n\
0.Выйти в главное меню\n";
const string SORT_MENU = "Сортировка:\n1.По фамилии;\n2.По длительности командировки в днях;\n3.По сумме командировочных расходов на день.\n";
const string FIND_MENU = "Поиск:\n1.По фамилии;\n2.По городу назначения;\n3.По месяцу.\n";
const string MAIN_MENU = "1.Работа с аккаунтами;\n2.Работа с командировочными данными;\n0.Выход\n";
const string ACCOUNT_MENU_ROLE_1 = "1.Изменить свой логин и пароль;\n2.Просмотреть все учётные записи;\n3.Добавить учётную запись;\n4.Изменить учётную запись;\n\
5.Удалить учётную запись;\n0.Выйти в главное меню\n";
const string TRIP_MENU_ROLE_1 = "1.Просмотреть все командировочные данные;\n2.Определить общие выплаты командировочных за месяц Х\
(вводится с клавиатуры);\n3.Вывести список наиболее часто посещаемых городов с месяца X по месяц Y (значения X и Y вводятся с клавиатуры);\n\
4.Найти данные;\n5.Отсортировать данные;\n6.Изменить данные;\n0.Выйти в главное меню\n";
const string DATA_CHANGE_MENU_ROLE_1 = "1.Добавить запись;\n2.Изменить запись;\n3.Удалить запись;\n0.Выйти в меню работы с командировочными данными\n";

const string TABLE_TRIP_HEADER = "|-------|Ф.И.О.|-------|---|ГОД|---|---|МЕСЯЦ|---|-|КОЛ-ВО ДНЕЙ ПОЕЗДКИ|-|-|СУММА НА ДЕНЬ|-|-------|ГОРОД|-------|\n";

const string MONEY_RES = "Выделенная сумма за указанный месяц составила: ";

const int F_I_O_LINE_LIMIT = 22;
const int YEAR_LINE_LIMIT = 11;
const int MONTH_LINE_LIMIT = 13;
const int DAYS_LINE_LIMIT = 21;
const int MONEY_LINE_LIMIT = 14;
const int TOWN_LINE_LIMIT = 21;
const int CURRENCY_LIMIT = 3;

bool canUserContinue(Account& guest);

void checkPatronymic(Trip_Man& temp);

void processTripFile(vector <Trip_Man>& emp,bool is_file_open, bool& exit_token);
void readTripFile(vector <Trip_Man> emp, bool& is_file_open);
int countStructuresInTripFile(bool& is_file_open);
void writeTripFile(vector<Trip_Man> emp);
void writeEndTripFile(Trip_Man new_emp);

void processMainMenu(vector <Trip_Man>& emp,vector<Account>& acc, Account& guest);
void processAccountMenu(vector<Account>& acc, Account& guest);
void processTripMenu(vector<Trip_Man> emp, Account guest);
void processDataChangeMenu();

void showTripArray(vector<Trip_Man>emp);
void countMoney4MonthX(vector<Trip_Man> emp);
string countMoney(vector<Month_Money> value);