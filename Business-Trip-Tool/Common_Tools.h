#pragma once

#include <string>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <Algorithm>

using namespace std;

const string FINISHED_SEARCHING = "��������� �����?\n 1.��\n 2.���\n";
const string REPEAT_SORT = "��������� ����������?\n 1.��\n 2.���\n";

const string YOU_SURE_TO_DELETE = "�� �������, ��� ������ ���������� ������� ��������?\n 1.��\n 2.���\n";
const string YOU_SURE_TO_EDIT = "�� �������, ��� ������ ���������� ������� ���������?\n 1.��\n 2.���\n";

const string ERROR_NUM_RANGE_INPUT= "�������� ����. ������� ����� �� ������� ��������� ";
const string ERROR_LIMIT_INPUT_P1="�������� ����. ������� �����������, ������ ";
const string ERROR_LIMIT_INPUT_P2 = " ��������\n";
const string ERROR_NOT_NUM = "�������� ����. ����������, ������� ������ �����\n";

const string GO_BACK_QUESTION = "������ ��������� �����?\n 1.��\n 2.���\n";
const string TOO_BIG_STRING = "���� ��������� ���������� ��� ���� ������������. ����������, ���������.\n";

const string CHOOSE_TO_EDIT = "������� ����� ������, ������� ������ ���������������: ";
const string CHOOSE_TO_DELETE = "������� ����� ������, ������� ������ �������: ";
const string SUCC_EDIT = "��������� ������ �������\n";
const string SUCC_DELETE = "�������� ������ �������\n";
const string SUCC_CONF = "������������� �������� ������ �������\n";

const string NO_INFO = "NO_INFO";

bool wantToGoBack(string message=GO_BACK_QUESTION, int yes=1); //asks user if one wants to procceed or go back
string check4TooBigString(int limit, char(*inputCond)(), string input_message,string error_message = TOO_BIG_STRING);
void clearStream();
void clearScreen();
string oneWordInput(char(*inputCondition)()); //allows to input in one word (no " " allowed)
char justEnterChar();
char onlyLetterInput();
char currencyInput(); //only input capital English letters
char onlyNumInput();

int inputIntNumbers(string message, int l_border, int r_border,string error_message); //checks for numeric input in range from l_border to r_border
bool doesFitInRange(int temp, int l_border, int r_border);
int inputIntNumbers(string message,int limit,string error_message); //checks for numeric input to be no more than limit amount of symbols
bool doesFitInRange(int temp, int limit);
double inputDouble(string message, int limit); //checks for double input