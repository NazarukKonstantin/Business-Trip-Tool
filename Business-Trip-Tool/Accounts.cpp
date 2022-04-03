#include "Accounts.h"

void showOptionsOnEnter(vector<Account>acc)
{
	cout << SIGN_UP_OR_LOG_IN;
	proceedPickedOption(acc);
}
void proceedPickedOption(vector<Account>acc)
{
	int choice = 0;
	cin >> choice;
	switch (choice)
	{
	case 1: signUp(acc); break;
	case 2: logIn(acc); break;
	case 0: break;
	}
}
void setDefaultAccount()
{
	Account def;
	def.login = "Admin";
	string input_password = "Admin";
	def.salt = generateSalt();
	def.hashed_salty_password = makePasswordHashedAndSalty(input_password, def.salt);
	def.role = 1;
	def.access = 1;
	writeEndAccountFile(def,newAccCase);
}


void signUp(vector<Account>acc, void(*roleCase)(Account& new_acc))
{
	cout << LOGIN_REQUEST;
	Account new_acc;
	getline(cin,new_acc.login);
	while (!isLoginUnique(acc,new_acc.login))
	{
		cout << EXISTING_LOGIN_ERROR;
		getline(cin,new_acc.login);
	}
	cout << PASSWORD_REQUEST;
	string input_password;
	getline(cin, input_password);
	int password_length = input_password.length();															// считает длину строки
	bool flag = true;
	while ((!isPasswordStrong(input_password,password_length)||password_length>SAFE_PASSWORD_LENGTH_RIGTH) && flag)	// условие захода в цикл: небезопасный пароль или пользователь его не подтвердил или пароль слишком длинный
	{																												// запрос на подтверждение не происходит, если пароль безопасен
		request4confirmation(input_password, flag, password_length);
	}
	string new_salt = generateSalt();
	new_acc.hashed_salty_password = makePasswordHashedAndSalty(input_password,new_salt);
	writeEndAccountFile(new_acc, roleCase);
}
void request4confirmation(string& input_password, bool& flag, int password_length)
{
	if (password_length > SAFE_PASSWORD_LENGTH_RIGTH)
	{
		cout << TOO_HARD_TO_REMEMBER;				// если пароль слишком длинный, выводит предупреждение
	}
	else
	{
		cout << WEAK_PASSWORD;						// если пароль небезопасный, выводит предупреждение
	}
	cout << PASSWORD_CONFIRMATION;				// запрос на подтверждение пароля пользователем
	int choice = 0;
	cin >> choice;								// выбор пользователя
	switch (choice)
	{
	case 1: flag = false; break;
	case 2: cout << PASSWORD_REQUEST; getline(cin, input_password); break;
	}
}
bool isLoginUnique(vector<Account>acc, string input_login)
{
	int vec_size = acc.size();
	for (int current_account = 0; current_account < vec_size; current_account++)
	{
		if (acc[current_account].login == input_login)
		{
			return true;
		}
	}
	return false;
}
bool isPasswordStrong(string input_password, int password_length)
{
	int special_symbols = 0;
	for (int current_sign = 0; current_sign < password_length; current_sign++)					// считает кол-во спец. символов в пароле
	{
		if ((input_password[current_sign] >= 33 && input_password[current_sign] <= 47) ||
			(input_password[current_sign] >= 58 && input_password[current_sign] <= 64) ||
			(input_password[current_sign] >= 91 && input_password[current_sign] <= 96) ||
			(input_password[current_sign] >= 123 && input_password[current_sign] <= 126))
		{
			special_symbols++;
		}
	}

	int capital_letters = 0;
	for (int current_sign = 0; current_sign < password_length; current_sign++)								// считает кол-во заглавных букв в пароле
	{
		if ((input_password[current_sign] >= 'A' && input_password[current_sign] <= 'Z') ||
			(input_password[current_sign] >= 'А' && input_password[current_sign] <= 'Я'))
		{
			capital_letters++;
		}
	}

	int small_letters = 0;
	for (int current_sign = 0; current_sign < password_length; current_sign++)								// считает кол-во строчных букв в пароле
	{
		if ((input_password[current_sign] >= 'a' && input_password[current_sign] <= 'z') ||
			(input_password[current_sign] >= 'а' && input_password[current_sign] <= 'я'))
		{
			small_letters++;
		}
	}

	int numbers = 0;
	for (int current_sign = 0; current_sign < password_length; current_sign++)								// считает кол-во цифр в пароле
	{
		if (input_password[current_sign] >= '0' && input_password[current_sign] <= '9')
		{
			numbers++;
		}
	}
	if (password_length < SAFE_PASSWORD_LENGTH_LEFT || capital_letters == 0 || small_letters == 0 || numbers == 0 || special_symbols == 0)
	{
		return false;
	}
	return true;
}
string generateSalt()
{
	string symbols_set = getSymbols4Salt();							// собирает набор символов для генерации соли
	srand(time(NULL));

	string salt;
	salt.reserve(SALT_SIZE);

	for (int i = 0; i < SALT_SIZE; i++)
	{
		salt.push_back(symbols_set[rand() % SYMBOLS_SIZE]);			//добавляет в строку соли случайный символ из ранее отобранных
	}
	return salt;
}
string getSymbols4Salt()
{
	string symbols_set;
	symbols_set.reserve(SYMBOLS_SIZE);

	char capital_letter = 'A';
	char small_letter = 'a';
	char num = '0';

	for (int i = 0; i < ALPHABET_AMOUNT; i++)							//собирает набор символов для соли из A-Z, a-z и 0-9 
	{
		symbols_set.push_back(capital_letter++);
		symbols_set.push_back(small_letter++);
		if (i < 10) { symbols_set.push_back(num++); };
	}
	return symbols_set;
}
string makePasswordHashedAndSalty(string input_password, string salt)
{
	return sha256(sha256(input_password + salt) + sha256(input_password));
}

void logIn(vector<Account>acc)
{
	bool flag = true;
	do
	{
		cout << LOGIN_REQUEST;
		Account guest;
		getline(cin, guest.login);
		cout << PASSWORD_REQUEST;
		string input_password;
		getline(cin, input_password);
		if (isLoginUnique(acc, guest.login))
		{
			cout << WRONG_ENTER;
			continue;
		}
		string salt = generateSalt();
		guest.hashed_salty_password = makePasswordHashedAndSalty(input_password, salt);
		if (!isPasswordCorrect(acc, guest))
		{
			cout << WRONG_ENTER;
			continue;
		}
		guest.active = true;
	} while (!flag);
}
bool isPasswordCorrect(vector<Account>acc, Account guest)
{
	int vec_size = acc.size();
	for (int current_account = 0; current_account < vec_size; current_account++)
	{
		if (acc[current_account].hashed_salty_password == guest.hashed_salty_password)
		{
			return true;
		}
	}
	return false;
}

void showAccountArray(vector<Account>acc)
{
	for (vector<Account>::iterator it = acc.begin(); it != acc.end(); it++)
	{
		cout<<"|"<< it->login << "|" << it->role << "|" << it->access<<"|\n";
	}
}
void addAccountInArray(vector<Account> acc, Account& new_acc)
{
	cout << ROLE;
	int role_choice = 0;
	cin >> role_choice;
	cout << ACCESS;
	int access_choice = 0;
	if (role_choice == 1) { new_acc.role = 1; };
	if (access_choice == 1) { new_acc.access = 1; };
	writeAccountFile(acc);
}
void pickAccountInArray(vector<Account> acc, void (*changeAccount)(vector<Account>acc,int acc_num))
{
	int counter = 0;
	searchAccount(acc, counter);
	cout << CHOOSE_TO_EDIT;
	int choice = 0;
	cin >> choice;
	while (choice > counter)
	{
		cout << ERROR_INPUT;
		cin >> choice;
	}
	int vec_size = acc.size();
	for (int acc_num = 0; acc_num < vec_size; acc_num++)
	{
		if (choice == acc[acc_num].search_counter)
		{
			changeAccount(acc,acc_num);
			break;
		}
	}
}
void editAccountInArray(vector<Account> acc, int acc_num)
{
	int access_choice = 0;
	int role_choice = 0;
	cout << EDIT_MENU;
	int choice = 0;
	cin >> choice;
	cout << YOU_SURE;
	int sure = 0;
	cin >> sure;
	if (sure == 1)
	{
		switch (choice)
		{
		case 1:
			cout << LOGIN_REQUEST;
			getline(cin, acc[acc_num].login);
			while (!isLoginUnique(acc, acc[acc_num].login))
			{
				cout << EXISTING_LOGIN_ERROR;
				getline(cin, acc[acc_num].login);
			} break;
		case 2:
			if (acc[acc_num].active)
			{
				cout << DONT_CHANGE_YOUR_ROLE;
				break;
			}
			cout << ROLE;
			cin >> role_choice;
			if (role_choice == 1) { acc[acc_num].role = 1; }; break;
		case 3:
			if (acc[acc_num].active)
			{
				cout << DONT_CHANGE_YOUR_ACCESS;
				break;
			}
			cout << ACCESS;
			if (access_choice == 1) { acc[acc_num].access = 1; }; break;
		case 0: break;
		}
	}
	writeAccountFile(acc);
}
void searchAccount(vector<Account>& acc,int& counter)
{
	cout << TO_EDIT;
	string search_to_edit;
	getline(cin, search_to_edit);
	int amount_of_accounts = acc.size();
	int search_size = search_to_edit.size();
	for (int current_account = 0; current_account < amount_of_accounts; current_account++)
	{
		for (int current_letter = 0; current_letter < search_size; current_letter++)
		{
			if (search_to_edit[current_letter] != acc[current_account].login[current_letter])
			{
				break;
			}
			cout <<acc[current_account].search_counter++<< " |" << acc[current_account].login << "|" << acc[current_account].role 
				<< "|" << acc[current_account].access << "|\n";
		}
	}
}
void deleteAccountInArray(vector<Account> acc,int acc_num)
{
	cout << YOU_SURE;
	int sure = 0;
	cin >> sure;
	if (sure == 1)
	{
		acc.erase(acc.begin() + acc_num);
	}
	writeAccountFile(acc);
}
void changeLogin(vector<Account> acc)
{
	logIn(acc);
	int vec_size = acc.size();
	for (int curr_acc = 0; curr_acc < vec_size; curr_acc++)
	{
		if (acc[curr_acc].active == 1)
		{
			cout << YOU_SURE;
			int sure = 0;
			cin >> sure;
			if (sure == 1)
			{
				if (acc[curr_acc].role == 1)
				{
					deleteAccountInArray(acc, curr_acc);
					signUp(acc,adminCase);
					break;
				}
				else
				{
					deleteAccountInArray(acc, curr_acc);
					signUp(acc, userCase);
					break;
				}
			
			}
		}
	}
}

void readAccountFile(vector<Account> acc)
{
	int amount_of_accounts = countStructuresInFile();
	acc.reserve(amount_of_accounts);				// резервируется память под массив аккаунтов
	ifstream f_in(ACCOUNT_FILE_NAME, ios::in);			//открывает файл в режиме чтения
	while (!f_in.eof())
	{
		Account temp;
		f_in >> temp.login >> temp.hashed_salty_password >> temp.salt >> temp.role >> temp.access;
		acc.push_back(temp);
	}
	f_in.close();
}
void writeEndAccountFile(Account new_account, void (*roleCase)(Account& new_acc))
{
	roleCase(new_account);
	ofstream f_add(ACCOUNT_FILE_NAME, ios::app);			// открывает файл для дозаписи
	f_add << endl;
	f_add << new_account.login << " "
		<< new_account.hashed_salty_password << " "
		<< new_account.salt << " "
		<< new_account.role << " "
		<< new_account.access;
	f_add.close();
}
void adminCase(Account& new_acc)
{
	new_acc.role = 1;
	new_acc.access = 1;
}
void userCase(Account& new_acc)
{
	new_acc.role = 0;
	new_acc.access = 1;
}
void newAccCase(Account& new_acc)
{
	new_acc.role = 0;
	new_acc.access = 0;
}
void writeAccountFile(vector<Account> acc)
{
	int vec_size = acc.size();
	ofstream f_out(ACCOUNT_FILE_NAME, ios::out);
	for(int i=0; i<vec_size; i++)
	{
		f_out << acc.at(i).login << " " <<
			acc.at(i).hashed_salty_password << " " <<
			acc.at(i).salt << " " <<
			acc.at(i).role << " " <<
			acc.at(i).access;
		if (i < vec_size - 1)
		{
			f_out <<endl;
		}
	}
	f_out.close();
}
int countStructuresInFile()
{
	ifstream f_in(ACCOUNT_FILE_NAME, ios::in);
	int amount_of_accounts = 0;							//кол-во аккаунтов в массиве, считываемом из файла
	if (f_in.is_open())
	{
		string temp;
		while (getline(f_in, temp))						//считывает текстовый файл построчно
		{
			amount_of_accounts++;						//если удалось считать строку, инкриментирует кол-во аккаунтов
		}
	}
	else
	{
		cout << NO_ACCOUNTS_CASE;						// в случае невозможности считать файл в режиме чтения выводится сообщение
		f_in.close();
		setDefaultAccount();
	}
	f_in.close();
	return amount_of_accounts;
}