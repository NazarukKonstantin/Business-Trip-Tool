#include "Common_Tools.h"

bool wantToGoBack()
{
	cout << GO_BACK_QUESTION;
	int choice = inputIntNumbers(1, 2);
	if (choice == 1)
	{
		return true;
	}
	return false;
}

string check4TooBigString(int limit,string message,string(*inputCondition)())
{
	string temp = inputCondition();
	while (temp.size() > limit)
	{
		cout << message;
		if(!wantToGoBack())
		{ 
			temp = inputCondition();
		}
		else
		{
			return "0";
		}
	}
	return temp;
}

void clearStream()
{
	if (cin.fail()) cin.clear();
	cin.ignore(numeric_limits <streamsize>::max(), '\n');
}

int inputIntNumbers(int l_border, int r_border)
{
	int temp=0;
	while(true)
	{
		cin >> temp;
		if (cin.get() == '\n')
		{
			if (doesFitInRange(temp, l_border, r_border))
			{
				return temp;
			}
			else
			{
				cout << ERROR_INPUT;
			}
		}
		else
		{
			clearStream();
			cout << ERROR_INPUT;
		}
	}
}
bool doesFitInRange(int temp, int l_border, int r_border)
{
	return ((temp >= l_border) && (temp <= r_border));
}
int inputIntNumbers(int limit)
{
	int temp = 0;
	while (true)
	{
		cin >> temp;
		if (cin.get() == '\n')
		{
			if (doesFitInRange(temp, limit))
			{
				return temp;
			}
			else
			{
				cout << ERROR_INPUT;
			}
		}
		else
		{
			clearStream();
			cout << ERROR_INPUT;
		}
	}
}
bool doesFitInRange(int temp, int limit)
{
	if (to_string(temp).size() <= limit)
	{
		return true;
	}
	return false;
}

string justEnterString()
{
	string temp;
	clearStream();
	getline(cin, temp);
	return temp;
}
string onlyLettersInput()
{
	string temp;
	while (true)
	{
		clearStream();
		getline(cin, temp);
		int str_size = temp.size();
		int amount_of_letters = 0;
		for (int curr_symbol = 0; curr_symbol < str_size; curr_symbol++)
		{
			char curr_symb = temp.at(curr_symbol);
			if ((curr_symb >= 'A' && curr_symb <= 'Z') || (curr_symb >= 'a' && curr_symb <= 'z') ||
				(curr_symb >= 'À' && curr_symb <= 'ß' || (curr_symb >= 'à' && curr_symb <= 'ÿ')))
			{
				amount_of_letters++;
			}
		}
		if (amount_of_letters == str_size)
		{
			return temp;
		}
		else
		{
			cout << ERROR_INPUT;
		}
	}
}
