#include "Accounts.h"

void showOptionsOnEnter(vector<Account>acc, Account& guest)
{
	cout << SIGN_UP_OR_LOG_IN;
	proceedPickedOption(acc,guest);
}
void proceedPickedOption(vector<Account>acc, Account& guest)
{
	int choice = inputIntNumbers(0, 2);
	switch (choice)
	{
	case 1: signUp(acc,newAccCase, guest); break;
	case 2: logIn(acc, guest); break;
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
	writeEndAccountFile(def,adminCase);
}


void signUp(vector<Account>acc, void(*roleCase)(Account& new_acc), Account& guest)
{
	cout << LOGIN_REQUEST;
	Account new_acc;
	new_acc.login = check4TooBigString(LOGIN_LENGTH_LIMIT,LOGIN_SIZE_EXCEEDED,justEnterString);
	if (new_acc.login=="0")
	{
		showOptionsOnEnter(acc, guest);
		return;
	}
	while (!isLoginUnique(acc,new_acc.login))
	{
		cout << EXISTING_LOGIN_ERROR;
		new_acc.login = check4TooBigString(LOGIN_LENGTH_LIMIT, LOGIN_SIZE_EXCEEDED, justEnterString);
		if (new_acc.login == "0")
		{
			showOptionsOnEnter(acc, guest);
			return;
		}
	}
	cout << PASSWORD_REQUEST;
	string input_password = showOrHidePassword();
	int password_length = input_password.length();															// считает длину строки
	bool flag = true;
	while ((!isPasswordStrong(input_password,password_length)||password_length>SAFE_PASSWORD_LENGTH_RIGTH) && flag)	// условие захода в цикл: небезопасный пароль или пользователь его не подтвердил или пароль слишком длинный
	{																												// запрос на подтверждение не происходит, если пароль безопасен
		request4confirmation(input_password, flag, password_length);
		password_length = input_password.length();
	}
	new_acc.salt = generateSalt();
	new_acc.hashed_salty_password = makePasswordHashedAndSalty(input_password,new_acc.salt);
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
	cout << PASSWORD_CONFIRMATION;				// запрос на подтверждение парол€ пользователем
	int choice = inputIntNumbers(1, 2);							// выбор пользовател€
	switch (choice)
	{
	case 1: flag = false; break;
	case 2: cout << PASSWORD_REQUEST; input_password = showOrHidePassword(); break;
	}
}
bool isLoginUnique(vector<Account>acc, string input_login)
{
	int vec_size = acc.size();
	for (int current_account = 0; current_account < vec_size; current_account++)
	{
		if (acc[current_account].login == input_login)
		{
			return false;
		}
	}
	return true;
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
			(input_password[current_sign] >= 'ј' && input_password[current_sign] <= 'я'))
		{
			capital_letters++;
		}
	}
	int small_letters = 0;
	for (int current_sign = 0; current_sign < password_length; current_sign++)								// считает кол-во строчных букв в пароле
	{
		if ((input_password[current_sign] >= 'a' && input_password[current_sign] <= 'z') ||
			(input_password[current_sign] >= 'а' && input_password[current_sign] <= '€'))
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
	string symbols_set = getSymbols4Salt();							// набор символов дл€ генерации соли
	srand(time(NULL));

	string salt;
	salt.reserve(SALT_SIZE);

	for (int i = 0; i < SALT_SIZE; i++)
	{
		salt.push_back(symbols_set[rand() % SYMBOLS_SIZE]);			// добавл€ет в строку соли случайный символ из ранее отобранных
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

	for (int i = 0; i < ALPHABET_AMOUNT; i++)							//собирает набор символов дл€ соли из A-Z, a-z и 0-9 
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
string showOrHidePassword()
{
	string input_password;
	cout << HIDE_OR_SHOW_PASSWORD;
	int choice = inputIntNumbers(1, 2);
	switch (choice)
	{
	case 1: input_password=justEnterString(); break;
	case 2: 
		clearStream();
		char temp;
		getchar();
		do
		{
			temp = _getch();
			if (temp == '\b')
			{
				input_password.erase(input_password.end() - 1);
				cout << temp << " " << temp;
			}
			else
			{
				input_password.push_back(temp);
				cout << "*";
			}
		} while (temp != '\r'); cout << endl;
	}
	return input_password;
}
bool doesAccountHaveAccess(Account temp)
{
	return temp.access == true;
}
bool isLogInSuccessful(Account temp)
{
	return temp.active == true;
}
bool areYouNew(Account temp)
{
	return temp.new_acc == true;
}

void logIn(vector<Account>acc, Account& guest)
{
	bool flag = true;
	do
	{
		cout << LOGIN_REQUEST;
		guest.login = check4TooBigString(LOGIN_LENGTH_LIMIT,LOGIN_SIZE_EXCEEDED,justEnterString);
		cout << PASSWORD_REQUEST;
		string input_password = justEnterString();
		if (isLoginUnique(acc, guest.login)||!isPasswordCorrect(acc, guest, input_password))
		{
			cout << WRONG_ENTER;
			if (wantToGoBack())
			{
				if (!guest.access)
				{
					showOptionsOnEnter(acc, guest);
				}
				else
				{
					guest.active = false;
				}
				break;
			}
			continue;
		}
		guest.active = true;
	} while (!flag);
}
bool isPasswordCorrect(vector<Account>acc, Account& guest, string input_password)
{
	int vec_size = acc.size();
	for (int current_account = 0; current_account < vec_size; current_account++)
	{
		if (makePasswordHashedAndSalty(input_password,acc[current_account].salt) == acc[current_account].hashed_salty_password)
		{
			guest.hashed_salty_password = acc[current_account].hashed_salty_password;
			guest.salt = acc[current_account].salt;
			guest.role = acc[current_account].role;
			guest.access = acc[current_account].access;
			return true;
		}
	}
	return false;
}

void showAccountArray(vector<Account>acc)
{
	int vec_size = acc.size();
	string temp_role, temp_access;
	cout << TABLE_ACCOUNTS_HEADER;
	for (int curr_acc = 0; curr_acc < vec_size; curr_acc++)
	{
		roleAccessConverter(acc, curr_acc,temp_role,temp_access);
		string temp_4_login(LOGIN_LENGTH_LIMIT - acc[curr_acc].login.size(), ' ');
		string role_length(ROLE_LENGTH_LIMIT - temp_role.size(), ' ');
		string access_length(ACCESS_LENGTH_LIMIT - temp_access.size(), ' ');
		cout << "|" << acc[curr_acc].login << temp_4_login << "|" << temp_role << role_length << "|" << temp_access << access_length << "|\n";
	}
}
void roleAccessConverter(vector<Account> acc, int curr_acc, string& temp_role, string& temp_access)
{
	if (acc[curr_acc].role)
	{
		temp_role = "јдминистратор";
	}
	else
	{
		temp_role = "ѕользователь";
	}
	if (acc[curr_acc].access && !acc[curr_acc].new_acc)
	{
		temp_access = "–азрешЄн";
	}
	else if (acc[curr_acc].new_acc)
	{
		temp_access = "ќжидает подтверждени€";
	}
	else if (!acc[curr_acc].access && !acc[curr_acc].new_acc)
	{
		temp_access = "«апрещЄн";
	}
}
void addAccountInArray(vector<Account>& acc, Account& guest)
{
	cout << ROLE;
	int role_choice = inputIntNumbers(1, 2);
	cout << ACCESS;
	int access_choice = inputIntNumbers(1, 2);
	if (access_choice == 1 && role_choice == 1)
	{
		signUp(acc, adminCase, guest);
	}
	else if (access_choice == 2 && role_choice == 1)
	{
		signUp(acc, blockedAdminCase, guest);
	}
	else if (access_choice == 1 && role_choice == 2)
	{
		signUp(acc, userCase, guest);
	}
	else if (access_choice == 2 && role_choice == 2)
	{
		signUp(acc, newAccCase, guest);
	}
}
void pickAccountInArray(string message4search,string message, vector<Account>&acc, void (*changeAccount)(vector<Account>&acc,int acc_num))
{
	int counter = 0;
	string search_to_edit;
	searchAccount(search_to_edit,message4search,acc,counter);
	if (search_to_edit == "0") return;
	cout << message;
	int choice = inputIntNumbers(1, counter);
	int vec_size = acc.size();
	for (int acc_num = 0; acc_num < vec_size; acc_num++)
	{
		if (choice == acc[acc_num].search_counter)
		{
			changeAccount(acc,acc_num);
		}
		acc[acc_num].search_counter = 1;
	}
}
void editAccountMenu(vector<Account>& acc, int acc_num)
{
	cout << EDIT_ACCOUNT_MENU;
	int choice = inputIntNumbers(0,3);
	cout << YOU_SURE;
	char sure = _getch();
	cout << sure;
	getchar();
	string login_savespot = acc[acc_num].login;
	if (sure == '1')
	{
		switch (choice)
		{
		case 1: editLogin(login_savespot,acc,acc_num); break;
		case 2:	editRole(acc,acc_num); break;
		case 3: editAccess(acc,acc_num); break;
		case 0: break;
		}
	}
	writeAccountFile(acc);
}

void editLogin(string login_savespot, vector<Account>&acc, int acc_num)
{
	cout << LOGIN_REQUEST;
	acc[acc_num].login = check4TooBigString(LOGIN_LENGTH_LIMIT, LOGIN_SIZE_EXCEEDED, justEnterString);
	if (acc[acc_num].login == "0")
	{
		acc[acc_num].login = login_savespot;
		return;
	}
	while (!isLoginUnique(acc, acc[acc_num].login))
	{
		cout << EXISTING_LOGIN_ERROR;
		acc[acc_num].login = check4TooBigString(LOGIN_LENGTH_LIMIT, LOGIN_SIZE_EXCEEDED, justEnterString);
		if (acc[acc_num].login == "0")
		{
			acc[acc_num].login = login_savespot;
			break;
		}
	}
}
void editRole(vector<Account>& acc, int acc_num)
{
	int role_choice = 0;
	if (acc[acc_num].active)
	{
		cout << DONT_CHANGE_YOUR_ROLE;
		return;
	}
	cout << ROLE;
	role_choice = inputIntNumbers(1, 2);
	if (role_choice == 1)
	{
		acc[acc_num].role = 1;
	}
	else
	{
		acc[acc_num].role = 0;
	}
}
void editAccess(vector<Account>& acc, int acc_num)
{
	int access_choice = 0;
	if (acc[acc_num].active)
	{
		cout << DONT_CHANGE_YOUR_ACCESS;
		return;
	}
	cout << ACCESS;
	access_choice = inputIntNumbers(1, 2);
	if (access_choice == 1)
	{
		acc[acc_num].access = 1;
	}
	else
	{
		acc[acc_num].access = 0;
	}
}

void searchAccount(string& search_to_edit,string message,vector<Account>& acc, int&counter)
{
	cout << message;
	string temp_role, temp_access;
	search_to_edit= check4TooBigString(LOGIN_LENGTH_LIMIT, LOGIN_SIZE_EXCEEDED, justEnterString);
	if (search_to_edit == "0") return;
	int amount_of_accounts = acc.size();
	int search_size = search_to_edit.size();
	cout <<"--є--|"<< TABLE_ACCOUNTS_HEADER;
	for (int current_account = 0; current_account < amount_of_accounts; current_account++)
	{
		for (int current_letter = 0; current_letter < search_size; current_letter++)
		{
			if (search_to_edit[current_letter] != acc[current_account].login[current_letter])
			{
				break;
			}
			roleAccessConverter(acc, current_account, temp_role, temp_access);
			string temp_4_login(LOGIN_LENGTH_LIMIT - acc[current_account].login.size(), ' ');
			string role_length(ROLE_LENGTH_LIMIT - temp_role.size(), ' ');
			string access_length(ACCESS_LENGTH_LIMIT - temp_access.size(), ' ');
			string counter_length(5 - to_string(acc[current_account].search_counter).size(), ' ');
			cout <<counter_length<<acc[current_account].search_counter++ << "|" << acc[current_account].login << temp_4_login << "|" <<
				temp_role << role_length << "|" << temp_access << access_length << "|\n";
			counter++;
		}
	}

}
void deleteAccountInArray(vector<Account>& acc,int acc_num)
{
	cout << YOU_SURE;
	char sure;
	sure = _getch();
	cout << sure;
	getchar();
	if (sure == '1')
	{
		acc.erase(acc.begin() + acc_num);
	}
	writeAccountFile(acc);
}
void changeLogin(vector<Account>& acc, Account& guest)
{
	logIn(acc, guest);
	if(guest.active)
	{
		int vec_size = acc.size();
		for (int curr_acc = 0; curr_acc < vec_size; curr_acc++)
		{
			if (acc[curr_acc].active == 1)
			{
				cout << YOU_SURE;
				char sure= _getch();
				cout << sure;
				getchar();
				if (sure == '1')
				{
					if (acc[curr_acc].role == 1)
					{
						deleteAccountInArray(acc, curr_acc);
						signUp(acc, adminCase, guest);
						break;
					}
					else
					{
						deleteAccountInArray(acc, curr_acc);
						signUp(acc, userCase, guest);
						break;
					}
	
				}
			}
		}
	}
	else
	{
		guest.active = true;
	}
}

void readAccountFile(vector<Account>&acc)
{
	int amount_of_accounts = countStructuresInAccountFile();
	acc.reserve(amount_of_accounts);				// резервируетс€ пам€ть под массив аккаунтов
	ifstream f_in(ACCOUNT_FILE_NAME, ios::in);			//открывает файл в режиме чтени€
	while (!f_in.eof())
	{
		Account temp;
		f_in >> temp.login >> temp.hashed_salty_password >> temp.salt >> temp.role >> temp.access>>temp.new_acc;
		acc.push_back(temp);
	}
	f_in.close();
}
void writeEndAccountFile(Account new_account, void (*roleCase)(Account& new_acc))
{
	roleCase(new_account);
	ofstream f_add(ACCOUNT_FILE_NAME, ios::app);			// открывает файл дл€ дозаписи
	if(f_add.tellp()!=NULL)
	{
		f_add << endl;
	}
	f_add << new_account.login << " "
		<< new_account.hashed_salty_password << " "
		<< new_account.salt << " "
		<< new_account.role << " "
		<< new_account.access << " "
		<< new_account.new_acc;
	f_add.close();
}
void adminCase(Account& new_acc)
{
	new_acc.role = 1;
	new_acc.access = 1;
	new_acc.new_acc = 0;
}
void blockedAdminCase(Account& new_acc)
{
	new_acc.role = 1;
	new_acc.access = 0;
	new_acc.new_acc = 0;
}
void userCase(Account& new_acc)
{
	new_acc.role = 0;
	new_acc.access = 1;
	new_acc.new_acc = 0;
}
void newAccCase(Account& new_acc)
{
	new_acc.role = 0;
	new_acc.access = 0;
	new_acc.new_acc = 1;
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
			acc.at(i).access << " " <<
			acc.at(i).new_acc;
		if (i < vec_size - 1)
		{
			f_out <<endl;
		}
	}
	f_out.close();
}
int countStructuresInAccountFile()
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
		cout << NO_ACCOUNTS_CASE;						// в случае невозможности считать файл в режиме чтени€ выводитс€ сообщение
		f_in.close();
		setDefaultAccount();
	}
	f_in.close();
	return amount_of_accounts;
}