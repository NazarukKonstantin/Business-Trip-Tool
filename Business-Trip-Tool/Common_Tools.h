#pragma once

#include <string>
#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

const string FINISHED_SEARCHING = "��������� �����?\n 1.��\n 2.���\n";

const string YOU_SURE = "�� �������?\n 1.��\n 2.���\n";
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

const string NO_INFO = "NO_INFO";

bool wantToGoBack(string message=GO_BACK_QUESTION, int yes=1);
string check4TooBigString(int limit, char(*inputCond)(), string input_message,string error_message = TOO_BIG_STRING);
void clearStream();
void clearScreen();
//string justEnterString(char(*inputCondition)());
//string onlyLettersInput(char(*inputCondition)());
string oneWordInput(char(*inputCondition)());
char justEnterChar();
char onlyLetterInput();
char currencyInput();
char onlyNumInput();

int inputIntNumbers(string message, int l_border, int r_border,string error_message);
bool doesFitInRange(int temp, int l_border, int r_border);
int inputIntNumbers(string message,int limit,string error_message);
bool doesFitInRange(int temp, int limit);
double inputDouble(string message, int limit);