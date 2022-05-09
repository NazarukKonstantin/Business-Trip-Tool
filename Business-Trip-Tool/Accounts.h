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
	string salt;					// salt - string of randomly generated symbols, individual 4 each account
	bool role = false;				// defines account role (0 - registered user or new user, 1 - admin)
	bool access = false;			// defines account's access level (0 - access denied, 1 - has access)
	bool active = false;			// defines whether the user logged in or not
	bool new_acc = true;			// defines if the account is new to system 4 admin to confirm
	int search_counter = 1;			// necessary for search; is used like indexes for search
}; //the structure contains the info of individual account

//---------String constants-----------------------
const string ACCOUNT_FILE_NAME = "accounts_list.txt";

const string NO_ACCOUNTS_CASE = "��� ������� - ������ � �������.\n�� �������� ����� ��������������.\n��� ����� - Admin, ��� ������ - Admin.\n\
����� � ������ ����� �������� � ��������������� ������ ����.\n";
const string SIGN_UP_OR_LOG_IN =" 1.������������������(������� ����� �������)\n 2.�����\n 0.�����\n";
const string LOGIN_REQUEST = "������� �����:\n";
const string LOGIN_SIZE_EXCEEDED = "��� ����� ������� �������. ����������, ���������� ��� ���.\n";
const string PASSWORD_REQUEST = "������� ������:\n";
const string WAIT_4_CONFIRMATION = "��� ������� ��������������� � �������.\n�������� ��������� �������\
 � ������� �� �������������� ��� ���������� ��������.\n";
const string BAN_CONDITION = "��� ������� ������������. ��� ������������� ���������� � ��������������\n";

const string EXISTING_LOGIN_ERROR = "����� ����� ��� ����������. ����������, ������� ������: ";
const string WEAK_PASSWORD = "��� ������ ������� ����, ���������� ������ ������ ��������� �� 8 �� 16 ��������,\n\
������� ��� ������� ���� �������� � ��������� �����, ���� ����� � ���� ������ ���� @ # $ % * � �.�.\n";
const string TOO_HARD_TO_REMEMBER = "��� ������ �������� ������� ����� ��������.\n";
const string PASSWORD_CONFIRMATION_P1 = "�� ������������� ������";
const string PASSWORD_CONFIRMATION_P2 = "?\n(� ���������� ����� �������� ������ � ��������������� ������ ����)\n 1.��\n 2.���\n";
const string HIDE_OR_SHOW_PASSWORD = "���������� ������?\n 1.��\n 2.���\n";

const string WRONG_ENTER = "�������� ����� ��� ������\n";
const string TRY_AGAIN_M = "���������� ��� ���\n";

const string TABLE_ACCOUNTS_HEADER = "|-------|�����|-------|-------|����|-------|-------|������|-------|\n";
const string ROLE = "���������� ���� ����� ��������:\n 1.�������������\n 2.������������\n";
const string ACCESS = "��������� ������ ������� �������� � �������?\n 1.��\n 2.���\n";

const string EDIT_ACCOUNT_MENU = "��� �� ������ ���������������?\n 1. �����\n 2.����(�����/������������)\n\
 3.������ � �������(��������/��������)\n 0.�����\n";
const string TO_EDIT = "������� ����� ��������, ������� ������ ���������������: ";
const string TO_DELETE = "������� ����� ��������, ������� ������ �������: ";
const string DONT_DELETE_YOURSELF = "��������, �� �� �� ������ ������� ���� �������";
const string DONT_CHANGE_YOUR_ROLE = "��������, �� �� ������ �������� ���� ����";
const string DONT_CHANGE_YOUR_ACCESS = "��������, �� �� ������ �������� ���� ������� �������";

//---------Numeric constants---------------
const int SALT_SIZE = 16;					// amount of symbols in salt
const int SYMBOLS_SIZE = 62;				// size of set of symbols 4 salt generation
const int SAFE_PASSWORD_LENGTH_LEFT = 8;	// min amount of letters 4 safe password
const int SAFE_PASSWORD_LENGTH_RIGTH = 16;	// max reasonable amount of letters 4 safe password
const int ALPHABET_AMOUNT = 26;				// amount of letter in English alphabet
const int LOGIN_LENGTH_LIMIT = 21;			// max login length to fit in the output table 
const int ROLE_LENGTH_LIMIT = 20;			// max (title of) role length to fit in the output table 
const int ACCESS_LENGTH_LIMIT = 22;			// max (title of) access level length to fit in the output table 
const int COUNTER_LENGTH_LIMIT = 5;			// max index length to fit in the output table 

//---------Program starting functions---------------------------------------------------
void showOptionsOnEnter(vector<Account>acc, Account& guest);							// shows sign-in/ log-in options,takes user's choice (sign-in or log-in) and calls appropriate function
void showOptionsOnEnter(vector<Account>acc, Account& guest, bool& exit_token);			// shows sign-in/ log-in options,takes user's choice (sign-in or log-in) and calls appropriate function
void setDefaultAccount();																// creates defaulr account (Login: Admin; Password: Admin;) if none exists
//---------Registration functions-----------------------------------------------------------
void signUp(vector<Account>&acc, void(*roleCase)(Account& new_acc), Account& guest);			// executes commands and calls functions connected to registration process
bool isLoginUnique (vector<Account>acc, string input_login);								// checks if login is unique
bool isPasswordStrong(string input_password,int password_length);							// checks if password is safe 
string generateSalt();																		// generates salt
string getSymbols4Salt();																	// creates symbols set 4 salt generation
string makePasswordHashedAndSalty(string input_password, string salt);						// hash-function
string showOrHidePassword();																// password input function (hide or show password while entering)
void request4confirmation(string& input_password, bool& flag, int password_length);			// reguests 4 user to change a weak password
//---------Log-in functions---------------------------------------------------------
void logIn(vector<Account>acc, Account& guest);										// executes commands and calls functions connected to log-in process
bool isPasswordCorrect(vector<Account>acc, Account& guest, string input_password);	// checks if password mathes the one saved in the system
bool doesAccountHaveAccess(Account temp);											// checks if user got access to keep on working with program
bool isLogInSuccessful(Account temp);												// checks if log-in process is successful
bool areYouNew(Account temp);														// checks if a user is new to system and haven't been confirmed by admin yet
//---------Admin and user options functions-----------------------------------------------------------------------------------------------------
void showAccountArray(vector<Account> acc);																										// show accounts (4 Admin Only)
void roleAccessConverter(vector<Account> acc, int curr_acc, string& temp_role, string& temp_access);											// converts role and access numbers (0&1) to words 4 output
void addAccountInArray(vector<Account>& acc, Account& guest);																					// add account (4 Admin Only)
void pickAccountInArray(string message4search, string message, vector<Account>& acc, void (*changeAccount)(vector<Account>& acc, int acc_num));	// choose account to edit (4 Admin Only)
void editAccountMenu(vector<Account>& acc, int acc_num);																						// edit account (4 Admin Only)
void editLogin(string login_savespot, vector<Account>& acc, int acc_num);																		// change log-in (4 Admin Only)
template <typename T>
void edit(vector<Account>& acc, int acc_num, T Account::* field, string dont_message, string input_message);									// change role or access (4 Admin Only)
//void editRole(vector<Account>& acc, int acc_num);																								// change role (4 Admin Only)
//void editAccess(vector<Account>& acc, int acc_num);																								// change access (4 Admin Only)
void searchAccount(string& search_to_edit,string message, vector<Account>& acc, int& counter);													// searching and showing accounts similar 2 input
void deleteAccountInArray(vector<Account>& acc, int acc_num);																					// delete account (4 Admin Only)
void changeLogin(vector<Account>& acc, Account& guest);																							// change ones log-in and password
//---------File proccessing functions------------------------------------------------
void readAccountFile(vector<Account>&acc);													// reads account file
int countStructuresInAccountFile();															// counts amount of structures in file
void writeEndAccountFile(Account new_account, void (*roleCase)(Account& new_acc));			// adds acccount to the end of file
void writeAccountFile(vector<Account> acc);													// write account file
void adminCase(Account& new_acc);															// assign admin role to account
void blockedAdminCase(Account& new_acc);                                                    // assign admin with access restricted role to account
void userCase(Account& new_acc);															// assign registered user role to account
void newAccCase(Account& new_acc);															// assign new user role to account