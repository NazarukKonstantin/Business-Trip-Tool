#include "Common_Tools.h"

bool wantToGoBack(string message)
{
	cout << message;
	int choice = inputIntNumbers(1, 2);
	if (choice == 1)
	{
		clearScreen();
		return true;
	}
	clearScreen();
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
	cin.clear();
	cin.ignore(1000, '\n');
}
void clearScreen()
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordScreen = { 0, 0 };    // home for the cursor
	DWORD cCharsWritten;			 // number of characters written
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	// Get the number of character cells in the current buffer.
	if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
	{
		return;
	}
	
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	// Fill the entire screen with blanks.
	if (!FillConsoleOutputCharacter(hStdout,        // Handle to console screen buffer
									(TCHAR)' ',      // Character to write to the buffer
									dwConSize,       // Number of cells to write
									coordScreen,     // Coordinates of first cell
									&cCharsWritten)) // Receive number of characters written
	{
		return;
	}

	// Get the current text attribute.
	if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
	{
		return;
	}

	// Set the buffer's attributes accordingly.
	if (!FillConsoleOutputAttribute(hStdout,         // Handle to console screen buffer
									csbi.wAttributes, // Character attributes to use
									dwConSize,        // Number of cells to set attribute
									coordScreen,      // Coordinates of first cell
									&cCharsWritten))  // Receive number of characters written
	{
		return;
	}

	// Put the cursor at its home coordinates.
	SetConsoleCursorPosition(hStdout, coordScreen);
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
	getline(cin, temp);
	return temp;
}
string onlyLettersInput()
{
	string temp;
	while (true)
	{
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