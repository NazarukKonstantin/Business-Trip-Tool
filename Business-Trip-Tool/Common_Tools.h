#pragma once

#include <string>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <Algorithm>

using namespace std;

const string FINISHED_SEARCHING = "Повторить поиск?\n 1.Да\n 2.Нет\n";
const string REPEAT_SORT = "Повторить сортировку?\n 1.Да\n 2.Нет\n";

const string YOU_SURE_TO_DELETE = "Вы уверены, что хотите продолжить процесс удаления?\n 1.Да\n 2.Нет\n";
const string YOU_SURE_TO_EDIT = "Вы уверены, что хотите продолжить процесс изменения?\n 1.Да\n 2.Нет\n";

const string ERROR_NUM_RANGE_INPUT= "Неверный ввод. Введите цифру из данного диапазона ";
const string ERROR_LIMIT_INPUT_P1="Неверный ввод. Введите запрошенное, меньше ";
const string ERROR_LIMIT_INPUT_P2 = " символов\n";
const string ERROR_NOT_NUM = "Неверный ввод. Пожалуйста, вводите только цифры\n";

const string GO_BACK_QUESTION = "Хотите вернуться назад?\n 1.Да\n 2.Нет\n";
const string TOO_BIG_STRING = "Ввод превышает выделенное под него пространство. Пожалуйста, сократите.\n";

const string CHOOSE_TO_EDIT = "Введите номер строки, которую хотите отредактировать: ";
const string CHOOSE_TO_DELETE = "Введите номер строки, которую хотите удалить: ";
const string SUCC_EDIT = "Изменение прошло успешно\n";
const string SUCC_DELETE = "Удаление прошло успешно\n";
const string SUCC_CONF = "Подтверждение аккаунта прошло успешно\n";

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