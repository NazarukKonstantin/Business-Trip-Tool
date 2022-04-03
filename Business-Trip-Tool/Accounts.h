#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <fstream>
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

	int search_counter = 1;
}; //структура содержит инф-цию отдельного аккаунта: логин, хэшированный пароль, соль, статус (пользователь или администратор) и также уровень доступа, определяемый админ-ом

//---------Строковые константы-----------------------
const string ACCOUNT_FILE_NAME = "accounts_list.txt";

const string NO_ACCOUNTS_CASE = "Ваш аккаунт - первый в системе.\nВы получили права администратора.\nВаш логин - Admin, ваш пароль - Admin.\n\
Логин и пароль можно изменить в соответствующем пункте меню.\n";
const string SIGN_UP_OR_LOG_IN ="1. Зарегестрироваться\n2.Войти\n0.Выход\n";
const string LOGIN_REQUEST = "Введите логин: ";
const string PASSWORD_REQUEST = "Введите пароль: ";

const string EXISTING_LOGIN_ERROR = "Такой логин уже существует. Пожалуйста, введите другой: ";
const string WEAK_PASSWORD = "Ваш пароль слишком слаб, безопасный пароль должен содержать от 8 до 16 символов,\n\
включая как минимум одну строчную и заглавную букву, одну цифру и один символ типа @ # $ % * и т.п.\n";
const string TOO_HARD_TO_REMEMBER = "Ваш пароль содержит слишком много символов.\n";
const string PASSWORD_CONFIRMATION = "Вы подтверждаете пароль ?\n\
(В дальнейшем можно изменить пароль в соответствующем пункте меню)\n1.Да\n2.Нет\n";

const string WRONG_ENTER = "Неверный логин или пароль. Попробуйте ещё раз.\n";

const string ROLE = "Установите роль этого аккаунта:\n1.Администратор;\n2.Пользователь.\n";
const string ACCESS = "Разрешить доступ данного аккаунта к системе?\n1.Да;\n2.Нет.\n";

const string EDIT_MENU = "Что вы хотите отредактировать?\n1. Логин\n2.Роль(Админ./Пользователь)\n\
3.Доступ к системе(Разрешён/Запрещён)\n0.Выход\n";
const string TO_EDIT = "Введите логин аккаунта, который хотите отредактировать: ";
const string CHOOSE_TO_EDIT = "Введите номер аккаунта, который хотите отредактировать: ";
const string DONT_DELETE_YOURSELF = "Извините, но вы не можете удалить свой аккаунт";
const string DONT_CHANGE_YOUR_ROLE = "Извините, вы не можете изменить свою роль";
const string DONT_CHANGE_YOUR_ACCESS = "Извините, вы не можете изменить свой уровень доступа";

//---------Числовые константы---------------
const int SALT_SIZE = 16;					// кол-во символов в соли
const int SYMBOLS_SIZE = 62;				// количество символов для генерации соли
const int SAFE_PASSWORD_LENGTH_LEFT = 8;	// левая граница безопасной длины пароля
const int SAFE_PASSWORD_LENGTH_RIGTH = 16;	// правая граница безопасной длины пароля
const int ALPHABET_AMOUNT = 26;				// кол-во букв в англ. алфавите, вынесенное в константу

//---------Функции начала программы-------------------------------------
void showOptionsOnEnter(vector<Account>acc);							// отображает вариант регистрации и входа при запуске программы
void proceedPickedOption(vector<Account>acc);							// принимает выбор пользователя и вызывает ф-ции входа и регистрации соответственно
void setDefaultAccount();												// создаёт аккаунт Login: Admin; Password: Admin; если файл аккаунтов не существует
//---------Функции регистрации--------------------------------------------------------------
void signUp(vector<Account>acc, void(*roleCase)(Account& new_acc));							// выполняет команды и вызывает ф-ции, непосредственно связанные с регистрацией в систему
bool isLoginUnique (vector<Account>acc, string input_login);								// проверяет логин на уникальность
bool isPasswordStrong(string input_password,int password_length);							//проверяет пароль на безопасность
string generateSalt();																		//генеруирует соль
string getSymbols4Salt();																	//создаёт набор символов, из которых генерируется соль
string makePasswordHashedAndSalty(string input_password, string salt);						// хэширует пароль с солью
void request4confirmation(string& input_password, bool& flag, int password_length);			//запрос на подтверждение/изменение пользователем слабого пароля
//---------Функции входа в систему--------------------------
void logIn(vector<Account>acc);								// выполняет команды и вызывает ф-ции, непосредственно связанные со входом в систему, где данный аккаунт зарегестрирован
bool isPasswordCorrect(vector<Account>acc, Account guest);	// проверяет правильность введённого пароля
//---------Функции опций администратора и пользователя--------------------------------------------------
void showAccountArray(vector<Account> acc);																// опция админа по просмотру аккаунтов
void addAccountInArray(vector<Account> acc, Account& new_acc);											// опция админа по добавлению аккаунта
void pickAccountInArray(vector<Account> acc,void (*changeAccount)(vector<Account>acc, int acc_num));	// позволяет админу выбрать аккаунт для редактирования
void editAccountInArray(vector<Account> acc, int acc_num);												// опция админа по редактированию аккаунта
void searchAccount(vector<Account>&acc,int& counter);													// поиск и вывод на экран похожих на введённый аккаунтов
void deleteAccountInArray(vector<Account> acc, int acc_num);											// опция админа по удалению аккаунта
void changeLogin(vector<Account> acc);																	// опция пользователя и админа по смене логина и пароля
//---------Функции работы с файлом аккаунтов------------------------------------------------
void readAccountFile(vector<Account> acc);													// считывает данные из файла аккаунтов
int countStructuresInFile();																// считает кол-во структур/аккаунтов в файле
void writeEndAccountFile(Account new_account, void (*roleCase)(Account& new_acc));			// записывает данные нового аккаунта в конец файла аккаунтов
void writeAccountFile(vector<Account> acc);													// записывает данные изменённого массива аккаунтов в файл
void adminCase(Account& new_acc);															// присваивает аккаунту роль админа
void userCase(Account& new_acc);															// присваивает аккаунту роль пользователя
void newAccCase(Account& new_acc);															// присваивает аккаунту роль пользователя, ожидающего подтверждения админа