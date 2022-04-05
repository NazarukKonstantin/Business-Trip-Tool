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

	int search_counter = 1;
}; //��������� �������� ���-��� ���������� ��������: �����, ������������ ������, ����, ������ (������������ ��� �������������) � ����� ������� �������, ������������ �����-��

//---------��������� ���������-----------------------
const string ACCOUNT_FILE_NAME = "accounts_list.txt";

const string NO_ACCOUNTS_CASE = "��� ������� - ������ � �������.\n�� �������� ����� ��������������.\n��� ����� - Admin, ��� ������ - Admin.\n\
����� � ������ ����� �������� � ��������������� ������ ����.\n";
const string SIGN_UP_OR_LOG_IN ="1. ������������������\n2.�����\n0.�����\n";
const string LOGIN_REQUEST = "������� �����: ";
const string LOGIN_SIZE_EXCEEDED = "��� ����� ������� �������. ����������, ���������� ��� ���.\n";
const string PASSWORD_REQUEST = "������� ������: ";
const string WAIT_4_CONFIRMATION = "��� ������� ��������������� � �������.\n�������� ��������� �������\
 � ������� �� �������������� ��� ���������� ��������.\n";
const string BAN_CONDITION = "��� ������� ������������. ��� ������������� ���������� � ��������������\n";

const string EXISTING_LOGIN_ERROR = "����� ����� ��� ����������. ����������, ������� ������: ";
const string WEAK_PASSWORD = "��� ������ ������� ����, ���������� ������ ������ ��������� �� 8 �� 16 ��������,\n\
������� ��� ������� ���� �������� � ��������� �����, ���� ����� � ���� ������ ���� @ # $ % * � �.�.\n";
const string TOO_HARD_TO_REMEMBER = "��� ������ �������� ������� ����� ��������.\n";
const string PASSWORD_CONFIRMATION = "�� ������������� ������ ?\n\
(� ���������� ����� �������� ������ � ��������������� ������ ����)\n1.��\n2.���\n";
const string HIDE_OR_SHOW_PASSWORD = "���������� ������?\n1.��;\n2.���.\n";

const string WRONG_ENTER = "�������� ����� ��� ������. ���������� ��� ���.\n";

const string TABLE_ACCOUNTS_HEADER = "|-------|�����|-------|-------|����|-------|-------|������|-------|\n";
const string ROLE = "���������� ���� ����� ��������:\n1.�������������;\n2.������������.\n";
const string ACCESS = "��������� ������ ������� �������� � �������?\n1.��;\n2.���.\n";

const string EDIT_MENU = "��� �� ������ ���������������?\n1. �����\n2.����(�����./������������)\n\
3.������ � �������(��������/��������)\n0.�����\n";
const string TO_EDIT = "������� ����� ��������, ������� ������ ���������������: ";
const string CHOOSE_TO_EDIT = "������� ����� ��������, ������� ������ ���������������: ";
const string DONT_DELETE_YOURSELF = "��������, �� �� �� ������ ������� ���� �������";
const string DONT_CHANGE_YOUR_ROLE = "��������, �� �� ������ �������� ���� ����";
const string DONT_CHANGE_YOUR_ACCESS = "��������, �� �� ������ �������� ���� ������� �������";

//---------�������� ���������---------------
const int SALT_SIZE = 16;					// ���-�� �������� � ����
const int SYMBOLS_SIZE = 64;				// ���������� �������� ��� ��������� ����
const int SAFE_PASSWORD_LENGTH_LEFT = 8;	// ����� ������� ���������� ����� ������
const int SAFE_PASSWORD_LENGTH_RIGTH = 16;	// ������ ������� ���������� ����� ������
const int ALPHABET_AMOUNT = 26;				// ���-�� ���� � ����. ��������, ���������� � ���������
const int LOGIN_LENGTH_LIMIT = 21;
const int ROLE_LENGTH = 20;
const int ACCESS_LENGTH = 22;

//---------������� ������ ���������-------------------------------------
void showOptionsOnEnter(vector<Account>acc, Account& guest);							// ���������� ������� ����������� � ����� ��� ������� ���������
void proceedPickedOption(vector<Account>acc, Account& guest);							// ��������� ����� ������������ � �������� �-��� ����� � ����������� ��������������
void setDefaultAccount();												// ������ ������� Login: Admin; Password: Admin; ���� ���� ��������� �� ����������
//---------������� �����������--------------------------------------------------------------
void signUp(vector<Account>acc, void(*roleCase)(Account& new_acc), Account& guest);			// ��������� ������� � �������� �-���, ��������������� ��������� � ������������ � �������
bool isLoginUnique (vector<Account>acc, string input_login);								// ��������� ����� �� ������������
bool isPasswordStrong(string input_password,int password_length);							//��������� ������ �� ������������
string generateSalt();																		//����������� ����
string getSymbols4Salt();																	//������ ����� ��������, �� ������� ������������ ����
string makePasswordHashedAndSalty(string input_password, string salt);						// �������� ������ � �����
string showOrHidePassword();																// ��������� �������: ���������� ������ ��� ��� ��� �����
void request4confirmation(string& input_password, bool& flag, int password_length);			//������ �� �������������/��������� ������������� ������� ������
//---------������� ����� � �������--------------------------
void logIn(vector<Account>acc, Account& guest);								// ��������� ������� � �������� �-���, ��������������� ��������� �� ������ � �������, ��� ������ ������� ���������������
bool isPasswordCorrect(vector<Account>acc, Account& guest, string input_password);	// ��������� ������������ ��������� ������
bool doesAccountHaveAccess(Account temp);
bool isLogInSuccessful(Account temp);
//---------������� ����� �������������� � ������������--------------------------------------------------
void showAccountArray(vector<Account> acc);																// ����� ������ �� ��������� ���������
void roleAccessConverter(vector<Account> acc, int curr_acc, string& temp_role, string& temp_access);
void addAccountInArray(vector<Account>& acc, Account& guest);											// ����� ������ �� ���������� ��������
void pickAccountInArray(vector<Account> acc,void (*changeAccount)(vector<Account>&acc, int acc_num));	// ��������� ������ ������� ������� ��� ��������������
void editAccountInArray(vector<Account>& acc, int acc_num);												// ����� ������ �� �������������� ��������
void searchAccount(vector<Account>&acc);													// ����� � ����� �� ����� ������� �� �������� ���������
void deleteAccountInArray(vector<Account>& acc, int acc_num);											// ����� ������ �� �������� ��������
void changeLogin(vector<Account>& acc, Account& guest);																	// ����� ������������ � ������ �� ����� ������ � ������
//---------������� ������ � ������ ���������------------------------------------------------
void readAccountFile(vector<Account> acc);													// ��������� ������ �� ����� ���������
int countStructuresInAccountFile();																// ������� ���-�� ��������/��������� � �����
void writeEndAccountFile(Account new_account, void (*roleCase)(Account& new_acc));			// ���������� ������ ������ �������� � ����� ����� ���������
void writeAccountFile(vector<Account> acc);													// ���������� ������ ���������� ������� ��������� � ����
void adminCase(Account& new_acc);															// ����������� �������� ���� ������
void blockedAdminCase(Account& new_acc);
void userCase(Account& new_acc);															// ����������� �������� ���� ������������
void newAccCase(Account& new_acc);															// ����������� �������� ���� ������������, ���������� ������������� ������