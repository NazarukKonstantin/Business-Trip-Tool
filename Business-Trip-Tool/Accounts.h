#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <fstream>
#include <conio.h>
#include <ctime>
#include "sha256.h"
#include <iomanip>
#include "Common_Tools.h"

using namespace std;
struct Account
{
	string login;
	string hashed_salty_password;				
	string salt;					// salt - string of randomly generated symbols, individual 4 each account
	bool role = false;				// defines account role (0 - registered user or new user, 1 - admin)
	bool access = false;			// defines account's access level (0 - access denied, 1 - has access)
	bool active = false;			// defines whether the user logged in or not
	bool new_acc = true;			// defines if the account is new to system for admin to confirm
	int search_counter = 1;			// necessary for search; is used like indexes for search
}; //the structure contains the info of individual account

//---------String constants-----------------------
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
const string PASSWORD_CONFIRMATION_P1 = "Вы подтверждаете пароль";
const string PASSWORD_CONFIRMATION_P2 = "?\n(В дальнейшем можно изменить пароль в соответствующем пункте меню)\n 1.Да\n 2.Нет\n";
const string HIDE_OR_SHOW_PASSWORD = "Показывать пароль?\n 1.Да\n 2.Нет\n";

const string WRONG_ENTER = "Неверный логин или пароль\n";
const string TRY_AGAIN_M = "Попробуйте ещё раз\n";

const string TABLE_ACCOUNTS_HEADER = "|-------|ЛОГИН|-------|-------|РОЛЬ|-------|-------|ДОСТУП|-------|\n";
const string ROLE = "Установите роль этого аккаунта:\n 1.Администратор\n 2.Пользователь\n";
const string ACCESS = "Разрешить доступ данного аккаунта к системе?\n 1.Да\n 2.Нет\n";

const string NO_ACC_FOUND = "Аккаунтов, удовлетворяющих запросу не найдено\n";

const string LOGIN_CONFIRM = "Пожалуйста, подтвердите свой текущий логин\n";
const string ENTER_NEW_LOG = "Пожалуйста, введите ваш новый логин и пароль:\n";
const string EDIT_ACCOUNT_MENU = "Что вы хотите отредактировать?\n 1.Роль(Админ/Пользователь)\n 2.Доступ к системе(Разрешён/Запрещён)\n 0.Выход\n";
const string TO_EDIT = "Введите логин аккаунта, который хотите отредактировать: ";
const string TO_DELETE = "Введите логин аккаунта, который хотите удалить: ";
const string DONT_DELETE_YOURSELF = "Извините, но вы не можете удалить свой аккаунт\n";
const string DONT_CHANGE_YOUR_ROLE = "Извините, вы не можете изменить свою роль\n";
const string DONT_CHANGE_YOUR_ACCESS = "Извините, вы не можете изменить свой уровень доступа\n";

//---------Numeric constants---------------
const int SALT_SIZE = 16;					// amount of symbols in salt
const int SYMBOLS_SIZE = 62;				// size of set of symbols for salt generation
const int SAFE_PASSWORD_LENGTH_LEFT = 8;	// min amount of letters for safe password
const int SAFE_PASSWORD_LENGTH_RIGTH = 16;	// max reasonable amount of letters for safe password
const int ALPHABET_AMOUNT = 26;				// amount of letters in English alphabet
const int LOGIN_LENGTH_LIMIT = 21;			// max login length to fit in the output table 
const int ROLE_LENGTH_LIMIT = 20;			// max (title of) role length to fit in the output table 
const int ACCESS_LENGTH_LIMIT = 22;			// max (title of) access level length to fit in the output table 
const int COUNTER_LENGTH_LIMIT = 5;			// max index length to fit in the output table 

//---------Program starting functions---------------------------------------------------
void showOptionsOnEnter(vector<Account>&acc, Account& guest, bool& exit_token);			// shows sign-in/ log-in options,takes user's choice (sign-in or log-in) and calls appropriate function
void setDefaultAccount();																// creates default account (Login: Admin; Password: Admin;) if none exists
//---------Registration functions-----------------------------------------------------------
void signUp(vector<Account>&acc, void(*roleCase)(Account& new_acc), Account& guest);		// executes commands and calls functions connected to registration process
bool isLoginUnique (vector<Account>acc, string input_login);
bool isPasswordStrong(string input_password,int password_length);							// checks if password is safe 
string generateSalt();
string getSymbols4Salt();																	// creates symbols set for salt generation
string makePasswordHashedAndSalty(string input_password, string salt);						// hash-function
string showOrHidePassword();																// password input function (hide or show password while entering)
void request4confirmation(string& input_password, bool& flag, int password_length);			// reguests user to change a weak password
//---------Log-in functions---------------------------------------------------------
void logIn(vector<Account>&acc, Account& guest, bool& exit_token);					// executes commands and calls functions connected to log-in process
void changeAccActiceStatus(vector<Account>& acc, Account& guest,bool state);		// changes active status to the opposite
bool isPasswordCorrect(vector<Account>acc, Account& guest, string input_password);	// checks if password mathes the one saved in the system
bool doesAccountHaveAccess(Account temp);											// checks if user got access to keep on working with program
bool isLogInSuccessful(Account temp);
bool areYouNew(Account temp);														// checks if a user is new to system and haven't been confirmed by admin yet
//---------Admin and user options functions-----------------------------------------------------------------------------------------------------
void accHeaderOutput(int c_length=0, string counter="");
void showAccountArray(vector<Account> acc);																	// show accounts (for Admin Only)
void roleAccessConverter(vector<Account> acc, int curr_acc, string& temp_role, string& temp_access);											// converts role and access numbers (0 & 1) to words for output
void addAccountInArray(vector<Account>& acc, Account guest);
void changeAccountInArray(string message, vector<Account>& acc, Account guest, // choose account to edit (for Admin Only)
						void (*changeAccount)(vector<Account>& acc,Account guest,int acc_num, string edit_message), string edit_message=YOU_SURE_TO_DELETE);	
void editAccountMenu(vector<Account>& acc,Account guest,int acc_num, string edit_message);
template <typename T>
void edit(vector<Account>& acc,Account guest, int acc_num, T Account::* field, string dont_message, string input_message);									// change role or access (for Admin Only)
int pickAccount(string message,vector<Account>& acc, int& counter);																			// searching and showing accounts similar 2 input
void deleteAccountInArray(vector<Account>& acc,Account guest,int acc_num,string you_sure);												// delete account (for Admin Only)
void changeLogin(vector<Account>& acc, Account& guest, bool& exit_token);																		// change own log-in and password
//---------File proccessing functions------------------------------------------------
void readAccountFile(vector<Account>&acc);
int countStructuresInAccountFile();															// counts amount of structures in file
void writeEndAccountFile(Account new_account, void (*roleCase)(Account& new_acc));			// adds acccount to the end of file
void writeAccountFile(vector<Account> acc);
void adminCase(Account& new_acc);															// assign admin role to account
void blockedAdminCase(Account& new_acc);                                                    // assign admin with access restricted role to account
void userCase(Account& new_acc);															// assign registered user role to account
void newAccCase(Account& new_acc);															// assign new user role to account