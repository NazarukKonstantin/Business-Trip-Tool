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

const string NO_FILE_ACCESS = "Файл пуст или недоступен для чтения. Выберите дальнейшее действие:\n1.Вписать данные\n2.Использовать тестовый файл\n3.Работа с аккаунтами\n0.Выйти из программы\n";
//--------------------DATA INPUT MESSAGES-------------------------------------------------------------------------------------------------------------------------
const string ENTER_SURNAME="Введите фамилию работника:\n";
const string ENTER_NAME="Введите имя работника:\n";
const string ENTER_PATRONYMIC="Введите отчество работника(если у работника нет отчества, введите \"НЕТ\" или \"-\")\n";
const string ENTER_YEAR="Введите год командировки:\n";
const string ENTER_MONTH="Введите месяц командировки (номер):\n";
const string ENTER_MONTH_NAME = "Введите название месяца командировки:\n";
const string ENTER_TOWN="Введите город назначения командировки:\n";
const string ENTER_DAYS="Введите количество (только число) выделенных на командировку дней:\n";
const string ENTER_MONEY="Введите количество (только число) выделенной суммы в расчёте на день:\n";
const string ENTER_CURRENCY = "Введите валюту (в формате USD,EUR,RUB,BYN и т.д.):\n";
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
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
 4.Найти данные;\n 5.Отсортировать данные\n 6.Изменить данные (добавить,изменить,удалить)\n 0.Выйти в главное меню\n";
const string DATA_CHANGE_MENU_ROLE_1 =" 1.Добавить запись\n 2.Изменить запись\n 3.Удалить запись\n 0.Выйти в меню работы с командировочными данными\n";
const string EDIT_DATA_MENU = "Изменить:\n 1.Фамилию\n 2.Имя\n 3.Отчество\n 4.Год\n 5.Месяц\n 6.Кол-во дней командировки\n 7.Сумму на день\n\
 8.Валюту\n 9.Город назначения\n 10.Все данные о сотруднике\n 0.Вернуться в меню изменения данных\n";
const string SEARCH_MENU="Искать данные по:\n 1.Фамилии\n 2.Имени \n 3.Отчеству\n 4.Городу назначения\n 5.Месяцу поездки(Название месяца)\n\
 6.Месяцу поездки(Номер)\n 7.Году поездки\n 8.Сумме в день на поездку\n 9.Валюте\n 10.Длительности поездки(в днях)\n 0.Выход в меню работы с командировочными данными\n";
const string SORT_MENU="Сортировать данные по:\n 1.Фамилии\n 2.Имени\n 3.Отчеству\n 4.Длительности командировки(в днях)\n\
 5.Сумме командировочных расходов в день\n 6.Валюте\n 7.Месяцам\n 8.Годам\n 9.Городам\n 0.Выйти в меню работы с командировочными данными\n";
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
const string F_I_O_HEADER="-------|Ф.И.О.|-------";
const string YEAR_HEADER="-|ГОД|-";
const string MONTH_HEADER="---|МЕСЯЦ|---";
const string DAYS_HEADER="-|СРОК ПОЕЗДКИ|-";
const string MONEY_HEADER="-|СУММА НА ДЕНЬ|-";
const string TOWN_HEADER="-|ГОРОД НАЗНАЧЕНИЯ|-";
const string SURNAME_HEADER = "-------|ФАМИЛИЯ|------";
const string NAME_HEADER = "---------|ИМЯ|--------";
const string PATRONYMIC_HEADER = "------|ОТЧЕСТВО|------";
const string TABLE_TRIP_HEADER = { "|" + F_I_O_HEADER + "|" + YEAR_HEADER + "|" + MONTH_HEADER + "|" + DAYS_HEADER + "|" + MONEY_HEADER + "|" + TOWN_HEADER + "|\n" };

const string MONEY_RES_P1 = "Выделенная сумма за ";
const string MONEY_RES_P2 = "-го года составила: ";

const string ENTER_MONTH_X = "Введите месяц X (номер месяца, с которого начнётся сортировка городов): \n";
const string ENTER_MONTH_Y = "Введите месяц Y (номер месяца, которым закончится сортировка городов): \n";
const string SORTED_TOWNS_P1 = "Наиболее посещаемые города с месяца ";
const string SORTED_TOWNS_P2 = "-го года по месяц ";
const string SORTED_TOWNS_P3 = "-го года:\n";
const string TOWN_TABLE_HEADER = "|-------|ГОРОД|------|-|КОЛ-ВО ПОСЕЩЕНИЙ|-|\n";

const string SORT_DIRECTION = "Сортировать по:\n 1.Возрастанию\n 2.Убыванию\n";
const string SORTED_BY = "Список работников, отстортированный по ";
const string SB_SURNAME="фамилии:\n";
const string SB_NAME="имени:\n";
const string SB_PATRONYMIC="отчеству:\n";
const string SB_DAYS="длительности командировки (в днях):\n";
const string SB_MONEY="сумме командировочных расходов в день:\n";
const string SB_CURRENCY = "валюте:\n";
const string SB_MONTH="месяцам:\n";
const string SB_YEAR = "годам:\n";
const string SB_TOWN="городам:\n";

const vector<string> MONTH_SET = {"Январь","Февраль","Март","Апрель","Май","Июнь","Июль","Август","Сентябрь","Октябрь","Ноябрь","Декабрь"};

const string WRONG_DAYS_P1 = "Ошибка! В данном месяце ";
const string WRONG_DAYS_P2 = " не содержится такое кол-во дней\n";

const string NO_DATA_FOUND = "Данных, удовлетворяющих запросу, не найдено\n";

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