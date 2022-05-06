#pragma once

using namespace std;
#include <string>
#include <iostream>
#include <Windows.h>

const string YOU_SURE = "Вы уверены?\n 1.Да\n 2. Нет\n";
const string ERROR_INPUT = "Неверный ввод. Введите значение, соответствующее запрошенному\n\
 (например, только буквы в слове, только цифры в числе или число из запрашиваемого диапазона)\n";
const string GO_BACK_QUESTION = "Хотите вернуться назад?\n 1.Да\n 2.Нет\n";
const string TOO_BIG_STRING = "Ввод превышает выделенное под него пространство. Пожалуйста, сократите.\n";

const string CHOOSE_TO_EDIT = "Введите номер строки, которую хотите отредактировать: ";
const string CHOOSE_TO_DELETE = "Введите номер строки, которую хотите удалить: ";


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