#pragma once

using namespace std;
#include <string>
#include <iostream>

const string YOU_SURE = "�� �������?\n1.��\n������ �������. ���\n";
const string ERROR_INPUT = "�������� ����. ������� ��������, ��������������� ������������\n\
 (��������, ������ ����� � �����, ������ ����� � ����� ��� ����� �� ������� ���������)\n";
const string GO_BACK_QUESTION = "������ ��������� �����?\n1.��\n2.���\n";
const string TOO_BIG_STRING = "���� ��������� ���������� ��� ���� ������������. ����������, ���������.\n";

bool wantToGoBack();
string check4TooBigString(int limit);