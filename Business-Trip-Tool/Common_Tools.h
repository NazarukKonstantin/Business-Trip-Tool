#pragma once

using namespace std;
#include <string>
#include <iostream>
#include <Windows.h>

const string YOU_SURE = "�� �������?\n 1.��\n 2. ���\n";
const string ERROR_INPUT = "�������� ����. ������� ��������, ��������������� ������������\n\
 (��������, ������ ����� � �����, ������ ����� � ����� ��� ����� �� �������������� ���������)\n";
const string GO_BACK_QUESTION = "������ ��������� �����?\n 1.��\n 2.���\n";
const string TOO_BIG_STRING = "���� ��������� ���������� ��� ���� ������������. ����������, ���������.\n";

const string CHOOSE_TO_EDIT = "������� ����� ������, ������� ������ ���������������: ";
const string CHOOSE_TO_DELETE = "������� ����� ������, ������� ������ �������: ";


bool wantToGoBack(string message=GO_BACK_QUESTION);
string check4TooBigString(int limit, string message,string(*inputCondition)());
void clearStream();
void clearScreen();
string justEnterString();
string onlyLettersInput();

int inputIntNumbers(int l_border, int r_border);
bool doesFitInRange(int temp, int l_border, int r_border);
int inputIntNumbers(int limit);
bool doesFitInRange(int temp, int limit);