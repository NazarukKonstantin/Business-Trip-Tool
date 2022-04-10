#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <fstream>
#include <conio.h>
#include <ctime>
#include "sha256.h"
#include "Common_Tools.h"

using namespace std;
struct Account
{
	string login;					
	string hashed_salty_password;							
	string salt;
	bool role = false;
	bool access = false;
	bool active = false;
	bool new_acc = true;
	int search_counter = 1;
}; //структура содержит инф-цию отдельного аккаунта: логин, хэшированный пароль, соль, статус (пользователь или администратор) и также уровень доступа, определяемый админ-ом

//---------Строковые константы-----------------------
const string ACCOUNT_FILE_NAME = "accounts_list.txt";

const string NO_ACCOUNTS_CASE = "Ваш аккаунт - первый в системе.\nВы получили права администратора.\nВаш логин - Admin, ваш пароль - Admin.\n\
Логин и пароль можно изменить в соответствующем пункте меню.\n";
const string SIGN_UP_OR_LOG_IN =" 1.Зарегистрироваться(Создать новый аккаунт)\n 2.Войти\n 0.Выход\n";
const string LOGIN_REQUEST = "Введите логин:\n";
const string LOGIN_SIZE_EXCEEDED = "Ваш логин слишком длинный. Пожалуйста, попробуйте ещё раз.\n";
const string PASSWORD_REQUEST = "Введите пароль:\n";
const string WAIT_4_CONFIRMATION = "Ваш аккаунт зарегестрирован в системе.\nОжидайте получения доступа\
 к системе от администратора для дальнейших действий.\n";
const string BAN_CONDITION = "Ваш аккаунт заблокирован. Для разблокировки обратитесь к администратору\n";

const string EXISTING_LOGIN_ERROR = "Такой логин уже существует. Пожалуйста, введите другой: ";
const string WEAK_PASSWORD = "Ваш пароль слишком слаб, безопасный пароль должен содержать от 8 до 16 символов,\n\
включая как минимум одну строчную и заглавную букву, одну цифру и один символ типа @ # $ % * и т.п.\n";
const string TOO_HARD_TO_REMEMBER = "Ваш пароль содержит слишком много символов.\n";
const string PASSWORD_CONFIRMATION = "Вы подтверждаете пароль ?\n\
(В дальнейшем можно изменить пароль в соответствующем пункте меню)\n 1.Да\n 2.Нет\n";
const string HIDE_OR_SHOW_PASSWORD = "Показывать пароль?\n 1.Да\n 2.Нет\n";

const string WRONG_ENTER = "Неверный логин или пароль. Попробуйте ещё раз.\n";

const string TABLE_ACCOUNTS_HEADER = "|-------|ЛОГИН|-------|-------|РОЛЬ|-------|-------|ДОСТУП|-------|\n";
const string ROLE = "Установите роль этого аккаунта:\n 1.Администратор\n 2.Пользователь\n";
const string ACCESS = "Разрешить доступ данного аккаунта к системе?\n 1.Да\n 2.Нет\n";

const string EDIT_ACCOUNT_MENU = "Что вы хотите отредактировать?\n 1. Логин\n 2.Роль(Админ/Пользователь)\n\
 3.Доступ к системе(Разрешён/Запрещён)\n 0.Выход\n";
const string TO_EDIT = "Введите логин аккаунта, который хотите отредактировать: ";
const string TO_DELETE = "Введите логин аккаунта, который хотите удалить: ";
const string DONT_DELETE_YOURSELF = "Извините, но вы не можете удалить свой аккаунт";
const string DONT_CHANGE_YOUR_ROLE = "Извините, вы не можете изменить свою роль";
const string DONT_CHANGE_YOUR_ACCESS = "Извините, вы не можете изменить свой уровень доступа";

//---------Числовые константы---------------
const int SALT_SIZE = 16;					// кол-во символов в соли
const int SYMBOLS_SIZE = 62;				// количество символов для генерации соли
const int SAFE_PASSWORD_LENGTH_LEFT = 8;	// левая граница безопасной длины пароля
const int SAFE_PASSWORD_LENGTH_RIGTH = 16;	// правая граница безопасной длины пароля
const int ALPHABET_AMOUNT = 26;				// кол-во букв в англ. алфавите, вынесенное в константу
const int LOGIN_LENGTH_LIMIT = 21;
const int ROLE_LENGTH_LIMIT = 20;
const int ACCESS_LENGTH_LIMIT = 22;
const int COUNTER_LENGTH_LIMIT = 5;

//---------Функции начала программы-------------------------------------
void showOptionsOnEnter(vector<Account>acc, Account& guest);							// отображает вариант регистрации и входа при запуске программы
void proceedPickedOption(vector<Account>acc, Account& guest);							// принимает выбор пользователя и вызывает ф-ции входа и регистрации соответственно
void setDefaultAccount();												// создаёт аккаунт Login: Admin; Password: Admin; если файл аккаунтов не существует
//---------Функции регистрации--------------------------------------------------------------
void signUp(vector<Account>acc, void(*roleCase)(Account& new_acc), Account& guest);			// выполняет команды и вызывает ф-ции, непосредственно связанные с регистрацией в систему
bool isLoginUnique (vector<Account>acc, string input_login);								// проверяет логин на уникальность
bool isPasswordStrong(string input_password,int password_length);							//проверяет пароль на безопасность
string generateSalt();																		//генеруирует соль
string getSymbols4Salt();																	//создаёт набор символов, из которых генерируется соль
string makePasswordHashedAndSalty(string input_password, string salt);						// хэширует пароль с солью
string showOrHidePassword();																// позволяет выбрать: показывать пароль или нет при вводе
void request4confirmation(string& input_password, bool& flag, int password_length);			//запрос на подтверждение/изменение пользователем слабого пароля
//---------Функции входа в систему--------------------------
void logIn(vector<Account>acc, Account& guest);								// выполняет команды и вызывает ф-ции, непосредственно связанные со входом в систему, где данный аккаунт зарегестрирован
bool isPasswordCorrect(vector<Account>acc, Account& guest, string input_password);	// проверяет правильность введённого пароля
bool doesAccountHaveAccess(Account temp);
bool isLogInSuccessful(Account temp);
bool areYouNew(Account temp);
//---------Функции опций администратора и пользователя--------------------------------------------------
void showAccountArray(vector<Account> acc);																// опция админа по просмотру аккаунтов
void roleAccessConverter(vector<Account> acc, int curr_acc, string& temp_role, string& temp_access);
void addAccountInArray(vector<Account>& acc, Account& guest);											// опция админа по добавлению аккаунта
void pickAccountInArray(string message4search, string message, vector<Account>& acc, void (*changeAccount)(vector<Account>& acc, int acc_num));	// позволяет админу выбрать аккаунт для редактирования
void editAccountMenu(vector<Account>& acc, int acc_num);												// опция админа по редактированию аккаунта
void editLogin(string login_savespot, vector<Account>& acc, int acc_num);
void editRole(vector<Account>& acc, int acc_num);
void editAccess(vector<Account>& acc, int acc_num);
void searchAccount(string& search_to_edit,string message, vector<Account>& acc, int& counter);													// поиск и вывод на экран похожих на введённый аккаунтов
void deleteAccountInArray(vector<Account>& acc, int acc_num);											// опция админа по удалению аккаунта
void changeLogin(vector<Account>& acc, Account& guest);																	// опция пользователя и админа по смене логина и пароля
//---------Функции работы с файлом аккаунтов------------------------------------------------
void readAccountFile(vector<Account>&acc);													// считывает данные из файла аккаунтов
int countStructuresInAccountFile();																// считает кол-во структур/аккаунтов в файле
void writeEndAccountFile(Account new_account, void (*roleCase)(Account& new_acc));			// записывает данные нового аккаунта в конец файла аккаунтов
void writeAccountFile(vector<Account> acc);													// записывает данные изменённого массива аккаунтов в файл
void adminCase(Account& new_acc);															// присваивает аккаунту роль админа
void blockedAdminCase(Account& new_acc);
void userCase(Account& new_acc);															// присваивает аккаунту роль пользователя
void newAccCase(Account& new_acc);															// присваивает аккаунту роль пользователя, ожидающего подтверждения админа