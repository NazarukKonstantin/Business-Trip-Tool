#include "Common_Tools.h"

bool wantToGoBack(string message,int yes)
{
	int choice = inputIntNumbers(message,1, 2, ERROR_NUM_RANGE_INPUT + "(1-2)\n");
	if (choice == yes)
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
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); //handle is an abstract reference to a resource that is used when application 
													  //software references blocks of memory or objects that are managed by another system like a database or an operating system
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
			cout << ERROR_NOT_NUM;
			clearStream();
		}
	}
}
bool doesFitInRange(int temp, int l_border, int r_border)
{
	return ((temp >= l_border) && (temp <= r_border));
}
int inputIntNumbers(string message,int limit,string error_message)
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
				cout << error_message;
			}
		}
		else
		{
			cout << ERROR_NOT_NUM;
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
	int comma_index = 0;
	cout << message;
	do
	{
		temp = onlyNumInput();
		if (temp == '\b' && st.size() != 0) //removes symb from the screen if backspace key's pressed
		{
			st.erase(st.end() - 1);
			cout << temp << " " << temp;
			if (none_of(st.begin(), st.end(), [](char a) {return a == ',';})) //if no commas in string
				comma_index=0;
		}
		else if (temp != '\r') // if enter key isn't pressed writes symbol down in input_password
		{
			int st_size = st.size();
			if (!st_size)
			{
				comma_index = 0;
				if (temp >= '0' && temp <= '9')
				{
					cout << temp;
					st.push_back(temp);
					if (temp == '0')
					{
						temp = ',';
						cout << temp;
						st.push_back(temp);
						comma_index++;
					}
				}
			}
			else if(st_size==1&&st.at(0)=='0')
			{
				cout << ',' << temp;
				st.push_back(',');
				st.push_back(temp);
				comma_index++;
			}
			else
			{
				if (temp >= '0' && temp <= '9')
				{
					cout << temp;
					st.push_back(temp);
				}
				else if ((temp == ',') && !comma_index)
				{
					comma_index++;
					cout << temp;
					st.push_back(temp);
				}
			}
		}
		if (st.size()>limit)
		{
			cout << endl;
			cout << TOO_BIG_STRING;
			system("pause");
			st.clear();
		}

	} while (temp != '\r'||!st.size()); cout << endl; //when enter key's pressed finishes input process
	if (st[st.size() - 1] == '.' || st[st.size() - 1] == ',') st.push_back('0');
	return stod(st);
}


char justEnterChar()
{
	return _getch();
}
char onlyLetterInput()
{
	while (true)
	{
		char temp = _getch();
		if ((temp >= 'À' && temp <= 'ß') || (temp >= 'à' && temp <= 'ÿ')||temp=='¸'||temp=='¨'||
			temp=='_'||temp=='-' || temp == '\b' || temp == '\r')
		{
			return temp;
		}
	}
}
char currencyInput()
{
	while (true)
	{
		char temp = _getch();
		if ((temp >= 'A' && temp <= 'Z') ||
			temp == '_' || temp == '-' || temp == '\b' || temp == '\r')
		{
			return temp;
		}
		if (temp >= 'a' && temp <= 'z')
		{
			return toupper(temp);
		}
	}
}
char onlyNumInput()
{
	while (true)
	{
		char temp = _getch();
		if ((temp >= '0' && temp <= '9') ||
			temp == ',' || temp == '\b' || temp == '\r')
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
		else if (symb != '\r'&& symb != ' '&& symb!='\b') // if enter key isn't pressed writes symbol down in input_password
		{
			cout << symb;
			temp.push_back(symb);
		}
	} while (symb != '\r'||!temp.size()); cout << endl; //when enter key's pressed finishes input process
	return temp;
}