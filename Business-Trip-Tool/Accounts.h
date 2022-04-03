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
}; //��������� �������� ���-��� ���������� ��������: �����, ������������ ������, ����, ������ (������������ ��� �������������) � ����� ������� �������, ������������ �����-��

//---------��������� ���������-----------------------
const string ACCOUNT_FILE_NAME = "accounts_list.txt";

const string NO_ACCOUNTS_CASE = "��� ������� - ������ � �������.\n�� �������� ����� ��������������.\n��� ����� - Admin, ��� ������ - Admin.\n\
����� � ������ ����� �������� � ��������������� ������ ����.\n";
const string SIGN_UP_OR_LOG_IN ="1. ������������������\n2.�����\n0.�����\n";
const string LOGIN_REQUEST = "������� �����: ";
const string PASSWORD_REQUEST = "������� ������: ";

const string EXISTING_LOGIN_ERROR = "����� ����� ��� ����������. ����������, ������� ������: ";
const string WEAK_PASSWORD = "��� ������ ������� ����, ���������� ������ ������ ��������� �� 8 �� 16 ��������,\n\
������� ��� ������� ���� �������� � ��������� �����, ���� ����� � ���� ������ ���� @ # $ % * � �.�.\n";
const string TOO_HARD_TO_REMEMBER = "��� ������ �������� ������� ����� ��������.\n";
const string PASSWORD_CONFIRMATION = "�� ������������� ������ ?\n\
(� ���������� ����� �������� ������ � ��������������� ������ ����)\n1.��\n2.���\n";

const string WRONG_ENTER = "�������� ����� ��� ������. ���������� ��� ���.\n";

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
const int SYMBOLS_SIZE = 62;				// ���������� �������� ��� ��������� ����
const int SAFE_PASSWORD_LENGTH_LEFT = 8;	// ����� ������� ���������� ����� ������
const int SAFE_PASSWORD_LENGTH_RIGTH = 16;	// ������ ������� ���������� ����� ������
const int ALPHABET_AMOUNT = 26;				// ���-�� ���� � ����. ��������, ���������� � ���������

//---------������� ������ ���������-------------------------------------
void showOptionsOnEnter(vector<Account>acc);							// ���������� ������� ����������� � ����� ��� ������� ���������
void proceedPickedOption(vector<Account>acc);							// ��������� ����� ������������ � �������� �-��� ����� � ����������� ��������������
void setDefaultAccount();												// ������ ������� Login: Admin; Password: Admin; ���� ���� ��������� �� ����������
//---------������� �����������--------------------------------------------------------------
void signUp(vector<Account>acc, void(*roleCase)(Account& new_acc));							// ��������� ������� � �������� �-���, ��������������� ��������� � ������������ � �������
bool isLoginUnique (vector<Account>acc, string input_login);								// ��������� ����� �� ������������
bool isPasswordStrong(string input_password,int password_length);							//��������� ������ �� ������������
string generateSalt();																		//����������� ����
string getSymbols4Salt();																	//������ ����� ��������, �� ������� ������������ ����
string makePasswordHashedAndSalty(string input_password, string salt);						// �������� ������ � �����
void request4confirmation(string& input_password, bool& flag, int password_length);			//������ �� �������������/��������� ������������� ������� ������
//---------������� ����� � �������--------------------------
void logIn(vector<Account>acc);								// ��������� ������� � �������� �-���, ��������������� ��������� �� ������ � �������, ��� ������ ������� ���������������
bool isPasswordCorrect(vector<Account>acc, Account guest);	// ��������� ������������ ��������� ������
//---------������� ����� �������������� � ������������--------------------------------------------------
void showAccountArray(vector<Account> acc);																// ����� ������ �� ��������� ���������
void addAccountInArray(vector<Account> acc, Account& new_acc);											// ����� ������ �� ���������� ��������
void pickAccountInArray(vector<Account> acc,void (*changeAccount)(vector<Account>acc, int acc_num));	// ��������� ������ ������� ������� ��� ��������������
void editAccountInArray(vector<Account> acc, int acc_num);												// ����� ������ �� �������������� ��������
void searchAccount(vector<Account>&acc,int& counter);													// ����� � ����� �� ����� ������� �� �������� ���������
void deleteAccountInArray(vector<Account> acc, int acc_num);											// ����� ������ �� �������� ��������
void changeLogin(vector<Account> acc);																	// ����� ������������ � ������ �� ����� ������ � ������
//---------������� ������ � ������ ���������------------------------------------------------
void readAccountFile(vector<Account> acc);													// ��������� ������ �� ����� ���������
int countStructuresInFile();																// ������� ���-�� ��������/��������� � �����
void writeEndAccountFile(Account new_account, void (*roleCase)(Account& new_acc));			// ���������� ������ ������ �������� � ����� ����� ���������
void writeAccountFile(vector<Account> acc);													// ���������� ������ ���������� ������� ��������� � ����
void adminCase(Account& new_acc);															// ����������� �������� ���� ������
void userCase(Account& new_acc);															// ����������� �������� ���� ������������
void newAccCase(Account& new_acc);															// ����������� �������� ���� ������������, ���������� ������������� ������