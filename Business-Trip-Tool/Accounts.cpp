#include "Accounts.h"

void showOptionsOnEnter(vector<Account>&acc, Account& guest, bool& exit_token)
{
	clearScreen();
	int choice = inputIntNumbers(SIGN_UP_OR_LOG_IN, 0, 2,ERROR_NUM_RANGE_INPUT+"(0-2)\n");
	switch (choice)
	{
	case 1: changeAccActiceStatus(acc, guest, false); signUp(acc, newAccCase, guest); break;
	case 2: logIn(acc, guest,exit_token); break;
	case 0: exit_token = true; return;
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

void changeAccActiceStatus(vector<Account>&acc, Account& guest, bool state)
{
	guest.active = state;
	int acc_size = acc.size();
	for (int curr_acc = 0; curr_acc < acc_size; curr_acc++)
	{
		if (acc[curr_acc].login == guest.login) acc[curr_acc].active = guest.active;
	}
}

void signUp(vector<Account>&acc, void(*roleCase)(Account& new_acc), Account& guest)
{
	clearScreen();
	guest.login = check4TooBigString(LOGIN_LENGTH_LIMIT,justEnterChar,LOGIN_REQUEST,LOGIN_SIZE_EXCEEDED); //returns NO_INFO if user wants to go back
	if (guest.login==NO_INFO)
	{
		return;
	}
	while (!isLoginUnique(acc,guest.login))
	{
		cout << EXISTING_LOGIN_ERROR;
		guest.login = check4TooBigString(LOGIN_LENGTH_LIMIT, justEnterChar, LOGIN_REQUEST, LOGIN_SIZE_EXCEEDED); //returns NO_INFO if user wants to go back
		if (guest.login == NO_INFO)
		{
			return;
		}
	}
	clearScreen();
	cout << PASSWORD_REQUEST;
	string input_password = showOrHidePassword();
	int password_length = input_password.length();
	bool flag = true;
	while (flag&&(!isPasswordStrong(input_password,password_length)||password_length>SAFE_PASSWORD_LENGTH_RIGTH))	// cicle entering conditions: unsafe password or user didn't confirm it(flag=true) or password's too long
	{																												// confirmation request doesn't happen if the password is safe
		request4confirmation(input_password, flag, password_length);
		password_length = input_password.length();
	}
	guest.salt = generateSalt();
	guest.hashed_salty_password = makePasswordHashedAndSalty(input_password,guest.salt);
	roleCase(guest);
	acc.push_back(guest);
	writeEndAccountFile(guest, roleCase);
}
void request4confirmation(string& input_password, bool& flag, int password_length)
{
	if (password_length > SAFE_PASSWORD_LENGTH_RIGTH)
	{
		cout << TOO_HARD_TO_REMEMBER;
	}
	else
	{
		cout << WEAK_PASSWORD;
	}
	int choice = inputIntNumbers(PASSWORD_CONFIRMATION_P1 + " (" + input_password +")" + PASSWORD_CONFIRMATION_P2,1, 2,ERROR_NUM_RANGE_INPUT+"(1-2)\n");
	switch (choice)
	{
	case 1: flag = false; break;
	case 2: clearScreen(); cout << PASSWORD_REQUEST; input_password = showOrHidePassword(); break;
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
	for (int current_sign = 0; current_sign < password_length; current_sign++)					// checks special symbols in password
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
	for (int current_sign = 0; current_sign < password_length; current_sign++)								// checks for capital letters in password
	{
		if ((input_password[current_sign] >= 'A' && input_password[current_sign] <= 'Z') ||
			(input_password[current_sign] >= 'А' && input_password[current_sign] <= 'Я'))
		{
			capital_letters++;
		}
	}
	int small_letters = 0;
	for (int current_sign = 0; current_sign < password_length; current_sign++)								// checks for lower letters 
	{
		if ((input_password[current_sign] >= 'a' && input_password[current_sign] <= 'z') ||
			(input_password[current_sign] >= 'а' && input_password[current_sign] <= 'я'))
		{
			small_letters++;
		}
	}
	int numbers = 0;
	for (int current_sign = 0; current_sign < password_length; current_sign++)								// checks for numbers in password
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
	string symbols_set = getSymbols4Salt();
	srand(time(NULL));

	string salt;
	salt.reserve(SALT_SIZE);

	for (int i = 0; i < SALT_SIZE; i++)
	{
		salt.push_back(symbols_set[rand() % SYMBOLS_SIZE]);			// adds random symbol to salt from symbols_set
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

	for (int i = 0; i < ALPHABET_AMOUNT; i++)							//fills symbols_set with random symbols A-Z and 0-9
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
	clearScreen();
	int choice = inputIntNumbers(HIDE_OR_SHOW_PASSWORD,1, 2, ERROR_NUM_RANGE_INPUT + "(1-2)\n");
	switch (choice)
	{
	case 1: input_password = oneWordInput(justEnterChar); break; //shows password on enter
	case 2: //replaces input symbols with * but only on screen
		char temp;
		do
		{
			temp = _getch();
			if (temp == '\b'&&input_password.size()!=0) //removes * from the screen if backspace key's pressed
			{
				input_password.erase(input_password.end() - 1);
				cout << temp << " " << temp;
			}
			else if (temp!='\r') // if enter key isn't pressed writes symbol down in input_password
			{
				input_password.push_back(temp);
				cout << "*";
			}
		} while (temp != '\r'); cout << endl; //when enter key's pressed finishes input process
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

void logIn(vector<Account>&acc, Account& guest,bool&exit_token)
{
	clearScreen();
	while(true)
	{
		guest.login = check4TooBigString(LOGIN_LENGTH_LIMIT,justEnterChar, LOGIN_REQUEST, LOGIN_SIZE_EXCEEDED); //returns NO_INFO if user wants to go back
		if (guest.login == NO_INFO) return;
		clearScreen();
		cout << PASSWORD_REQUEST;
		string input_password = oneWordInput(justEnterChar);
		if (isLoginUnique(acc, guest.login)||!isPasswordCorrect(acc, guest, input_password)) //checks if guest.login exists in system and the following password mathes
		{
			if (wantToGoBack(WRONG_ENTER+GO_BACK_QUESTION))
			{
				if (!guest.access) //log-ins in system for the first time - guest.access==false
				{
					showOptionsOnEnter(acc,guest,exit_token);
					break;
				}
				else //if user with access tries to change own log-in, fails in verification and wants to return
				{
					guest.active = false; 
					break;
				}
			}
			clearScreen();
			cout << TRY_AGAIN_M;
			continue;
		}
		int acc_size = acc.size();
		for (int curr_acc = 0; curr_acc < acc_size; curr_acc++)
		{
			if (acc[curr_acc].login == guest.login)
				guest = acc[curr_acc];
		}
		changeAccActiceStatus(acc,guest,true);//successful log-in means you're active user in system
		break;
	}
}
bool isPasswordCorrect(vector<Account>acc, Account& guest, string input_password)
{
	int vec_size = acc.size();
	for (int current_account = 0; current_account < vec_size; current_account++)
	{
		//comparing input_password to all passwords in system preliminary using appropriate salt
		if (makePasswordHashedAndSalty(input_password,acc[current_account].salt) == acc[current_account].hashed_salty_password)
		{
			//assigning matched account with guest account
			guest.hashed_salty_password = acc[current_account].hashed_salty_password;
			guest.salt = acc[current_account].salt;
			guest.role = acc[current_account].role;
			guest.access = acc[current_account].access;
			return true;
		}
	}
	return false;
}
void accHeaderOutput(int c_length, string counter)
{
	cout << counter << TABLE_ACCOUNTS_HEADER;
	string counter_length_div(c_length, '-');
	string divider(TABLE_ACCOUNTS_HEADER.size() - 3, '-');
	cout << counter_length_div << "|" << divider << "|\n";
}
void showAccountArray(vector<Account>acc)
{
	int vec_size = acc.size();
	string temp_role, temp_access;
	string divider(TABLE_ACCOUNTS_HEADER.size() - 3, '-');
	
	clearScreen();
	accHeaderOutput();
	for (int curr_acc = 0; curr_acc < vec_size; curr_acc++)
	{
		roleAccessConverter(acc, curr_acc, temp_role, temp_access);
		cout << "|" << setw(LOGIN_LENGTH_LIMIT) << acc[curr_acc].login << "|" << setw(ROLE_LENGTH_LIMIT) << temp_role << "|" << setw(ACCESS_LENGTH_LIMIT) << temp_access << "|\n";
		cout << "|" << divider << "|\n";
	}
}
void roleAccessConverter(vector<Account> acc, int curr_acc, string& temp_role, string& temp_access)
{
	if (acc[curr_acc].role==1)
	{
		temp_role = "Администратор";
	}
	else
	{
		temp_role = "Пользователь";
	}
	if (acc[curr_acc].access==1 && acc[curr_acc].new_acc==0)
	{
		temp_access = "Разрешён";
	}
	else if (acc[curr_acc].new_acc==1)
	{
		temp_access = "Ожидает подтверждения";
	}
	else if (acc[curr_acc].access==0 && acc[curr_acc].new_acc==0)
	{
		temp_access = "Запрещён";
	}
}
void addAccountInArray(vector<Account>& acc, Account guest)
{
	int role_choice = inputIntNumbers(ROLE,1, 2, ERROR_NUM_RANGE_INPUT + "(1-2)\n");
	int access_choice = inputIntNumbers(ACCESS,1, 2, ERROR_NUM_RANGE_INPUT + "(1-2)\n");
	if (access_choice == 1 && role_choice == 1)
	{
		signUp(acc, adminCase, guest); //signing account up as an admin
	}
	else if (access_choice == 2 && role_choice == 1)
	{
		signUp(acc, blockedAdminCase, guest); //signing account up as a blocked admin
	}
	else if (access_choice == 1 && role_choice == 2)
	{
		signUp(acc, userCase, guest); //signing account up as a user
	}
	else if (access_choice == 2 && role_choice == 2)
	{
		signUp(acc, newAccCase, guest); //signing account up as a new user
	}
}
void changeAccountInArray(string message, vector<Account>&acc, Account guest,
							void (*changeAccount)(vector<Account>&acc, Account guest, int acc_num, string edit_message),string edit_message)
{
	int counter = 1; //stores amount of accounts to choose from
	int choice = pickAccount(message,acc,counter);
	clearScreen();
	int vec_size = acc.size();
	for (int acc_num = 0; acc_num < vec_size; acc_num++)
	{
		if (choice == acc[acc_num].search_counter)
		{
			changeAccount(acc,guest,acc_num,edit_message);
			break;
		}
	}
}
void editAccountMenu(vector<Account>& acc,Account guest,int acc_num,string edit_message)
{
	clearScreen();
	showAccountArray(acc);
	int choice = inputIntNumbers(edit_message,0,2, ERROR_NUM_RANGE_INPUT + "(0-2)\n");
	if (!choice) return;
	int sure = inputIntNumbers(YOU_SURE_TO_EDIT, 1, 2, ERROR_NUM_RANGE_INPUT + "(1-2)\n");
	if (sure == 1)
	{
		switch (choice)
		{
			case 1: edit(acc, guest, acc_num, &Account::role, DONT_CHANGE_YOUR_ROLE, ROLE); break; //edit role
			case 2: edit(acc, guest, acc_num, &Account::access, DONT_CHANGE_YOUR_ACCESS, ACCESS); break; //edit access
			case 0: break;
		}
	}
	writeAccountFile(acc);
}

template <typename T>
void edit(vector<Account>& acc,Account guest, int acc_num, T Account::*field, string dont_message, string input_message)
{
	int field_choice = 0;
	clearScreen();
	showAccountArray(acc);
	if (acc[acc_num].login==guest.login) //if current user tries to change own role/access
	{
		cout << dont_message; //prints changing own role is forbidden
		return;
	}
	field_choice = inputIntNumbers(input_message,1, 2, ERROR_NUM_RANGE_INPUT + "(1-2)\n");
	if (field_choice == 1)
	{
		acc[acc_num].*field = 1;
	}
	else
	{
		acc[acc_num].*field = 0; //default role/access
	}
	if (acc[acc_num].access == 1)
		acc[acc_num].new_acc = 0;
	clearScreen();
	showAccountArray(acc);
	cout << SUCC_EDIT;
}

int pickAccount(string message,vector<Account>& acc, int&counter)
{
	string temp_role, temp_access;
	int amount_of_accounts = acc.size();
	string divider(TABLE_ACCOUNTS_HEADER.size() - 3, '-');
	string counter_length_div(COUNTER_LENGTH_LIMIT, '-');
	clearScreen();
	accHeaderOutput(COUNTER_LENGTH_LIMIT,"--№--");
	for (int current_account = 0; current_account < amount_of_accounts; current_account++) //goes through all accounts
	{
		acc[current_account].search_counter = counter;
		roleAccessConverter(acc, current_account, temp_role, temp_access);
		cout << setw(COUNTER_LENGTH_LIMIT) << acc[current_account].search_counter << "|" << setw(LOGIN_LENGTH_LIMIT) << acc[current_account].login << "|" <<
				setw(ROLE_LENGTH_LIMIT) << temp_role << "|" << setw(ACCESS_LENGTH_LIMIT) << temp_access << "|\n";
		cout << counter_length_div << "|" << divider << "|\n";
		counter++; //increasing counter of accounts in list
	}
	int choice = inputIntNumbers(message, 1, counter, ERROR_NUM_RANGE_INPUT + "(1-" + to_string(counter) + ")\n");
	return choice;
}
void deleteAccountInArray(vector<Account>& acc,Account guest,int acc_num,string you_sure)
{
	if ((acc[acc_num].login == guest.login)&&you_sure!=YOU_SURE_TO_EDIT)
	{
		cout << DONT_DELETE_YOURSELF;
		return;
	}
	int sure = inputIntNumbers(you_sure, 1, 2, ERROR_NUM_RANGE_INPUT + "(1-2)\n");
	if (sure == 1)
	{
		acc.erase(acc.begin() + acc_num);
		if(you_sure!=YOU_SURE_TO_EDIT) //YOU_SURE_TO_EDIT is transferred to delete function if user wants to change own login 
			cout << SUCC_DELETE;		//and password; in that case there's no need to print SUCC_DELETE
	}
	writeAccountFile(acc);
}
void changeLogin(vector<Account>& acc, Account& guest, bool& exit_token)
{
	clearScreen();
	cout << LOGIN_CONFIRM;
	_getch();
	logIn(acc, guest,exit_token); //you need to verify own log-in to be able to change it - safety measure
	if(guest.active) //logIn() makes guest.active=false if unsuccessful
	{
		clearScreen();
		cout << SUCC_CONF;
		int vec_size = acc.size();
		for (int curr_acc = 0; curr_acc < vec_size; curr_acc++) //searching for current (active) account in system
		{
			if (acc[curr_acc].active == 1) 
			{
				if (acc[curr_acc].role == 1) //saving previous role of account
				{
					deleteAccountInArray(acc, guest, curr_acc, YOU_SURE_TO_EDIT);
					cout << ENTER_NEW_LOG;
					_getch();
					signUp(acc, adminCase, guest);
				}
				else
				{
					deleteAccountInArray(acc, guest, curr_acc, YOU_SURE_TO_EDIT);
					cout << ENTER_NEW_LOG;
					_getch();
					signUp(acc, userCase, guest);
				}
				changeAccActiceStatus(acc, guest, true);
				break;
			}
		}
		cout << SUCC_EDIT;
	}
	else
	{
		guest.active = true; //if log-in verification is unsuccessful (returns guest.active=false) makes guest.active=true again
	}
}

void readAccountFile(vector<Account>&acc)
{
	int amount_of_accounts = countStructuresInAccountFile();
	acc.reserve(amount_of_accounts);	
	ifstream f_in(ACCOUNT_FILE_NAME, ios::in);
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
	ofstream f_add(ACCOUNT_FILE_NAME, ios::app);
	if(f_add.tellp()!=NULL) //tellp() returns the current position in the stream; so if it returns 0 it means the file is empty
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
		if (i < vec_size - 1) //adds endl to every structure in file except the last one
		{
			f_out <<endl;
		}
	}
	f_out.close();
}
int countStructuresInAccountFile()
{
	ifstream f_in(ACCOUNT_FILE_NAME, ios::in);
	int amount_of_accounts = 0;
	if (f_in.is_open())
	{
		string temp;
		while (getline(f_in, temp))	//reads file by lines
		{
			amount_of_accounts++;	//if line's read successfuly increases amount_of_accounts
		}
		f_in.close();
	}
	else //if file is not opening
	{
		clearScreen();
		cout << NO_ACCOUNTS_CASE;
		_getch();
		f_in.close();
		setDefaultAccount();
	}
	return amount_of_accounts;
}