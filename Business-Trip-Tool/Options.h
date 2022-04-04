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
	int money_per_day = 0;
};

const string TRIP_INFO = "trip_data.txt";

const string NO_FILE_ACCESS = "���� ���� ��� ���������� ��� ������. �������� ���������� ��������:\n1.������� ������.\n2.����� �� ���������\n";

const string ENTER_SURNAME="������� ������� ���������:\n";
const string ENTER_NAME="������� ��� ���������:\n";
const string ENTER_PATRONYMIC="������� �������� ���������(���� � ��������� ��� ��������, ������� \"No\")\n";
const string ENTER_YEAR="������� ��� ������������:\n";
const string ENTER_MONTH="������� ����� ������������:\n";
const string ENTER_TOWN="������� ����� ���������� ������������:\n";
const string ENTER_DAYS="������� ���������� (������ �����) ���������� �� ������������ ����:\n";
const string ENTER_MONEY="������� ���������� (������ �����) ���������� ����� � ������� �� ����:\n";

const string WANT_STOP = "������� ������������?\n1.��\n2.���\n";

const string ACCOUNT_MENU_ROLE_0 = "1.�������� ���� ����� � ������;\n0.����� � ������� ����\n";
const string TRIP_MENU_ROLE_0 = "1.����������� ��� ��������������� ������;\n2.���������� ����� ������� ��������������� �� ����� � (�������� � ����������);\n\
3.������� ������ �������� ����� ���������� ������� � ������ X �� ����� Y (�������� X � Y �������� � ����������);\n4.����� ������;\n5.������������� ������;\n\
0.����� � ������� ����\n";
const string MAIN_MENU = "1.������ � ����������;\n2.������ � ���������������� �������;\n0.�����\n";
const string ACCOUNT_MENU_ROLE_1 = "1.����������� ��� ������� ������;\n2.�������� ������� ������;\n3.�������� ������� ������;\n4.������� ������� ������;\n\
5.�������� ���� ����� � ������;\n0.����� � ������� ����\n";
const string TRIP_MENU_ROLE_1 = "1.����������� ��� ��������������� ������;\n2.�������� ������;\n3.���������� ����� ������� ��������������� �� ����� �\
(�������� � ����������);\n4.������� ������ �������� ����� ���������� ������� � ������ X �� ����� Y (�������� X � Y �������� � ����������);\n\
5.����� ������;\n6.������������� ������;\n0.����� � ������� ����\n";
const string DATA_CHANGE_MENU_ROLE_1 = "1.�������� ������;\n2.�������� ������;\n3.������� ������;\n0.����� � ���� ������ � ���������������� �������\n";

bool canUserContinue(Account& guest);

void checkPatronymic(Trip_Man& temp);

void processTripFile(vector <Trip_Man>& emp,bool is_file_open, bool& exit_token);
void readTripFile(vector <Trip_Man> emp, bool& is_file_open);
int countStructuresInTripFile(bool& is_file_open);
void writeTripFile(vector<Trip_Man> emp);
void writeEndTripFile(Trip_Man new_emp);

void processMenu(Account guest);