#pragma once

using namespace std;
#include <string>
#include <iostream>

const string YOU_SURE = "Вы уверены?\n1.Да\nДругая клавиша. Нет\n";
const string ERROR_INPUT = "Неверный ввод. Введите значение, соответствующее запрошенному\n\
 (например, только букву в слове, только цифры в числе или число из данного диапазона)\n";
const string GO_BACK_QUESTION = "Хотите вернуться назад?\n1.Да\n2.Нет\n";
const string TOO_BIG_STRING = "Ввод превышает выделенное под него пространство. Пожалуйста, сократите.\n";

bool wantToGoBack();
string check4TooBigString(int limit);