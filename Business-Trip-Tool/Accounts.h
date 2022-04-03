#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "sha256.h"

using namespace std;
struct Account
{
	string login;					
	string hashed_salty_password;							
	string salt;
	bool role = false;
	int access = -1;
}; //��������� �������� ���-��� ���������� ��������: �����, ������������ ������, ����, ������ (������������ ��� �������������) � ����� ������� �������, ������������ �����-��

const string ACCOUNT_FILE_NAME = "accounts_list.txt";
const string SIGN_UP_OR_LOG_IN ="1. ������������������\n2.�����\n0.�����\n";
const string LOGIN_REQUEST = "������� �����: ";
const string PASSWORD_REQUEST = "������� ������: ";
const string EXISTING_LOGIN_ERROR = "����� ����� ��� ����������. ����������, ������� ������: ";
const string WRONG_ENTER = "�������� ����� ��� ������. ���������� ��� ���.\n";
const string NO_ACCOUNTS_CASE = "��� ������� - ������ � �������.\n�� �������� ����� ��������������.\n��� ����� - Admin, ��� ������ - Admin.\n\
����� � ������ ����� �������� � ��������������� ������ ����.\n";
const string WEAK_PASSWORD = "��� ������ ������� ����, ���������� ������ ������ ��������� �� 8 �� 16 ��������,\n\
������� ��� ������� ���� �������� � ��������� �����, ���� ����� � ���� ������ ���� @ # $ % * � �.�.\n";
const string PASSWORD_CONFIRMATION = "�� ������������� ������?\n\
(� ���������� ����� �������� ������ � ��������������� ������ ����)\n1.��\n2.���\n";

const int SALT_SIZE = 16; // ���-�� �������� � ����
const int SYMBOLS_SIZE = 62; // ���������� �������� ��� ��������� ����


void showOptionsOnEnter(); // ���������� ������� ����������� � ����� ��� ������� ���������
void proceedPickedOption(); // ��������� ����� ������������ � �������� �-��� ����� � ����������� ��������������
void setDefaultAccount();	// ������ ������� Login: Admin; Password: Admin; ���� ���� ��������� �� ����������

void signUp();		// ��������� ������� � �������� �-���, ��������������� ��������� � ������������ � �������
bool isLoginUnique(); // ��������� ����� �� ������������
bool isPasswordStrong(); //��������� ������ �� ������������
string generateSalt(); //����������� ����
string getSymbols4Salt(); //������ ����� ��������, �� ������� ������������ ����
string makePasswordHashedAndSalty(string input_password, string salt); // �������� ������ � �����
void addAccountInArray(Account* arr, int& amount_of_accounts);	//��������� ����� � �������������� ������ � ������ ��������; ��������. role=0, access=-1;


void logIn();		// ��������� ������� � �������� �-���, ��������������� ��������� �� ������ � �������, ��� ������ ������� ���������������
bool doesLoginExist();		// ���������, ���������� �� ����� � �������
bool isPasswordCorrect();	// ��������� ������������ ��������� ������

bool readAccountFile();		// ��������� ������ �� ����� ���������
int countStructuresInFile();		// ������� ���-�� ��������/��������� � �����
void writeEndAccountFile(Account new_account);		// ���������� ������ ������ �������� � ����� ����� ���������


