#pragma once

#include <string>
#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

const string YOU_SURE = "Вы уверены?\n 1.Да\n 2.Нет\n";
const string ERROR_INPUT = "Неверный ввод. Введите значение, соответствующее запрошенному\n\
 (например, только буквы в слове, только цифры в числе или число из запрашиваемого диапазона)\n";
const string GO_BACK_QUESTION = "Хотите вернуться назад?\n 1.Да\n 2.Нет\n";
const string TOO_BIG_STRING = "Ввод превышает выделенное под него пространство. Пожалуйста, сократите.\n";

const string CHOOSE_TO_EDIT = "Введите номер строки, которую хотите отредактировать: ";
const string CHOOSE_TO_DELETE = "Введите номер строки, которую хотите удалить: ";

const string NO_INFO = "NO_INFO";

bool wantToGoBack(string message=GO_BACK_QUESTION);
string check4TooBigString(int limit, char(*inputCond)(), string input_message,string error_message = TOO_BIG_STRING);
void clearStream();
void clearScreen();
//string justEnterString(char(*inputCondition)());
//string onlyLettersInput(char(*inputCondition)());
string oneWordInput(char(*inputCondition)());
char justEnterChar();
char onlyLetterInput();
char numberOrLetterInput();

int inputIntNumbers(string message, int l_border, int r_border,string error_message= ERROR_INPUT);
bool doesFitInRange(int temp, int l_border, int r_border);
int inputIntNumbers(string message,int limit);
bool doesFitInRange(int temp, int limit);
double inputDouble(string message, int limit);