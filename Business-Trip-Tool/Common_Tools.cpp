#include "Common_Tools.h"

bool wantToGoBack(string message)
{
	int choice = inputIntNumbers(message,1, 2);
	if (choice == 1)
	{
		return true;
	}
	return false;
}

string check4TooBigString(int limit,char(*inputCond)(), string input_message,string error_message)
{
	cout << input_message;
	string temp = oneWordInput(inputCond);
	while (temp.size() > limit)
	{
		cout << error_message;
		if(!wantToGoBack())
		{ 
			cout << input_message;
			temp = oneWordInput(inputCond);
		}
		else
		{
			return NO_INFO;
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
	if (!GetConsoleScreenBufferInfo(hStdout, &csbi)) //returns false if an error occurs
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
	if (!GetConsoleScreenBufferInfo(hStdout, &csbi)) //returns false if an error occurs
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

int inputIntNumbers(string message,int l_border, int r_border,string error_message)
{
	int temp=0;
	while(true)
	{
		cout << message;
		cin >> temp;
		if (cin.get() == '\n') //checks int input till enter key
		{
			if (doesFitInRange(temp, l_border, r_border)) //if input is successfuly read checks it to fit the range
			{
				return temp;
			}
			else
			{
				cout <<error_message;
			}
		}
		else
		{
			cout << error_message;
			clearStream();
		}
	}
}
bool doesFitInRange(int temp, int l_border, int r_border)
{
	return ((temp >= l_border) && (temp <= r_border));
}
int inputIntNumbers(string message,int limit)
{
	int temp = 0;
	while (true)
	{
		cout << message;
		cin >> temp;
		if (cin.get() == '\n') //checks int input till enter key
		{
			if (doesFitInRange(temp, limit)) //if input is successfuly read checks it to fit the max limit of symbols
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
			clearStream();
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
double inputDouble(string message, int limit)
{
	string st;
	char temp;
	do
	{
		temp = _getch();
		if (temp == '\b' && st.size() != 0) //removes * from the screen if backspace key's pressed
		{
			st.erase(st.end() - 1);
			cout << temp << " " << temp;
		}
		else if (temp != '\r' && temp != ' ') // if enter key isn't pressed writes symbol down in input_password
		{
			if (temp >= '0' && temp <= '9')
			{
				cout << temp;
				st.push_back(temp);
			}
			else if ((temp=='.'||temp==',')&&stoi(st))
			{ 
				cout << temp;
				st.push_back(temp);
				for (int i = 0; i < 2; i++)
				{
					temp = _getch();
					if (temp >= '0' && temp <= '9')
					{
						cout << temp;
						st.push_back(temp);
					}
				}
				getchar();
				temp = '\r';
			}
		}
	} while (temp != '\r'); cout << endl; //when enter key's pressed finishes input process
	return stod(st);
}

//string justEnterString(char(*inputCondition)())
//{
//	string temp;
//	getline(cin, temp);
//	return temp;
//}
//string onlyLettersInput(char(*inputCondition)())
//{
//	string temp;
//	while (true)
//	{
//		getline(cin, temp);
//		int str_size = temp.size();
//		int amount_of_letters = 0;
//		for (int curr_symbol = 0; curr_symbol < str_size; curr_symbol++)
//		{
//			char curr_symb = temp.at(curr_symbol);
//			if ((curr_symb >= 'A' && curr_symb <= 'Z') || (curr_symb >= 'a' && curr_symb <= 'z') ||
//				(curr_symb >= 'À' && curr_symb <= 'ß' || (curr_symb >= 'à' && curr_symb <= 'ÿ')))
//			{
//				amount_of_letters++;
//			}
//		}
//		if (amount_of_letters == str_size)
//		{
//			return temp;
//		}
//		else
//		{
//			cout << ERROR_INPUT;
//		}
//	}
//}

char justEnterChar()
{
	return _getch();
}
char onlyLetterInput()
{
	while (true)
	{
		char temp = _getch();
		if ((temp >= 'A' && temp <= 'Z') || (temp >= 'a' && temp <= 'z') ||
			(temp >= 'À' && temp <= 'ß') || (temp >= 'à' && temp <= 'ÿ')||
			temp=='_'||temp=='-' || temp == '\b' || temp == '\r')
		{
			return temp;
		}
	}
}
char numberOrLetterInput()
{
	while (true)
	{
		char temp = _getch();
		if ((temp >= 'A' && temp <= 'Z') || (temp >= 'a' && temp <= 'z') ||
			(temp >= 'À' && temp <= 'ß') || (temp >= 'à' && temp <= 'ÿ') ||
			(temp>='0'&&temp<='9') || temp == '_' || temp == '-'||
			temp=='\b'|| temp=='\r')
		{
			return temp;
		}
	}
}

string oneWordInput(char(*inputCondition)())
{
	string temp;
	char symb;
	do
	{
		symb = inputCondition();
		if (symb == '\b'&& temp.size() != 0) //removes * from the screen if backspace key's pressed
		{
			temp.erase(temp.end() - 1);
			cout << symb << " " << symb;
		}
		else if (symb != '\r'&& symb != ' ') // if enter key isn't pressed writes symbol down in input_password
		{
			cout << symb;
			temp.push_back(symb);
		}
	} while (symb != '\r'); cout << endl; //when enter key's pressed finishes input process
	return temp;
}