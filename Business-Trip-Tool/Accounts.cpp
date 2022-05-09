#include "Accounts.h"

void showOptionsOnEnter(vector<Account>acc, Account& guest)
{
	clearScreen();
	int choice = inputIntNumbers(SIGN_UP_OR_LOG_IN,0, 2);
	switch (choice)
	{
	case 1: signUp(acc, newAccCase, guest); break;
	case 2: logIn(acc, guest); break;
	case 0: break;
	}
}
void showOptionsOnEnter(vector<Account>acc, Account& guest, bool& exit_token)
{
	clearScreen();
	int choice = inputIntNumbers(SIGN_UP_OR_LOG_IN,0, 2);
	switch (choice)
	{
	case 1: signUp(acc,newAccCase, guest); break;
	case 2: logIn(acc, guest); break;
	case 0: exit_token=true;break;
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


void signUp(vector<Account>&acc, void(*roleCase)(Account& new_acc), Account& guest)
{
	clearScreen();
	Account new_acc;
	new_acc.login = check4TooBigString(LOGIN_LENGTH_LIMIT,justEnterChar,LOGIN_REQUEST,LOGIN_SIZE_EXCEEDED); //returns "0" if user wants to go back
	if (new_acc.login==NO_INFO)
	{
		return;
	}
	while (!isLoginUnique(acc,new_acc.login))
	{
		cout << EXISTING_LOGIN_ERROR;
		new_acc.login = check4TooBigString(LOGIN_LENGTH_LIMIT, justEnterChar, LOGIN_REQUEST, LOGIN_SIZE_EXCEEDED); //returns "0" if user wants to go back
		if (new_acc.login == NO_INFO)
		{
			return;
		}
	}
	clearScreen();
	cout << PASSWORD_REQUEST;
	string input_password = showOrHidePassword();
	int password_length = input_password.length();
	bool flag = true;
	while ((!isPasswordStrong(input_password,password_length)||password_length>SAFE_PASSWORD_LENGTH_RIGTH) && flag)	// cicle entering conditions: unsafe password or user didn't confirm it(flag=true) or password's too long
	{																												// confirmation request doesn't happen if the password is safe
		request4confirmation(input_password, flag, password_length);
		password_length = input_password.length();
	}
	new_acc.salt = generateSalt();
	new_acc.hashed_salty_password = makePasswordHashedAndSalty(input_password,new_acc.salt);
	acc.push_back(new_acc);
	writeEndAccountFile(new_acc, roleCase);
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
	int choice = inputIntNumbers(PASSWORD_CONFIRMATION_P1 + " (" + input_password +")" + PASSWORD_CONFIRMATION_P2,1, 2);
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
	for (int current_sign = 0; current_sign < password_length; current_sign++)								// checks 4 capital letters in password
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
	for (int current_sign = 0; current_sign < password_length; current_sign++)								// checks 4 numbers in password
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
	int choice = inputIntNumbers(HIDE_OR_SHOW_PASSWORD,1, 2);
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

void logIn(vector<Account>acc, Account& guest)
{
	clearScreen();
	while(true)
	{
		guest.login = check4TooBigString(LOGIN_LENGTH_LIMIT,justEnterChar, LOGIN_REQUEST, LOGIN_SIZE_EXCEEDED);
		if (guest.login == NO_INFO) return;
		clearScreen();
		cout << PASSWORD_REQUEST;
		string input_password = oneWordInput(justEnterChar);
		if (isLoginUnique(acc, guest.login)||!isPasswordCorrect(acc, guest, input_password)) //checks if guest.login exists in system and the following password mathes
		{
			if (wantToGoBack(WRONG_ENTER+GO_BACK_QUESTION))
			{
				if (!guest.access) //log-ins in system 4 the first time - guest.access==false
				{
					showOptionsOnEnter(acc, guest);
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
		guest.active = true; //successful log-in means you're active user in system
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

void showAccountArray(vector<Account>acc)
{
	int vec_size = acc.size();
	string temp_role, temp_access;
	clearScreen();
	cout << TABLE_ACCOUNTS_HEADER;
	for (int curr_acc = 0; curr_acc < vec_size; curr_acc++)
	{
		roleAccessConverter(acc, curr_acc,temp_role,temp_access);
		//making strings with spaces to format output in table
		string temp_4_login(LOGIN_LENGTH_LIMIT - acc[curr_acc].login.size(), ' ');
		string role_length(ROLE_LENGTH_LIMIT - temp_role.size(), ' ');
		string access_length(ACCESS_LENGTH_LIMIT - temp_access.size(), ' ');
		cout << "|" << acc[curr_acc].login << temp_4_login << "|" << temp_role << role_length << "|" << temp_access << access_length << "|\n";
	}
	cout << endl;
}
void roleAccessConverter(vector<Account> acc, int curr_acc, string& temp_role, string& temp_access)
{
	if (acc[curr_acc].role)
	{
		temp_role = "Администратор";
	}
	else
	{
		temp_role = "Пользователь";
	}
	if (acc[curr_acc].access && !acc[curr_acc].new_acc)
	{
		temp_access = "Разрешён";
	}
	else if (acc[curr_acc].new_acc)
	{
		temp_access = "Ожидает подтверждения";
	}
	else if (!acc[curr_acc].access && !acc[curr_acc].new_acc)
	{
		temp_access = "Запрещён";
	}
}
void addAccountInArray(vector<Account>& acc, Account& guest)
{
	int role_choice = inputIntNumbers(ROLE,1, 2);
	int access_choice = inputIntNumbers(ACCESS,1, 2);
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
void pickAccountInArray(string message4search,string message, vector<Account>&acc, void (*changeAccount)(vector<Account>&acc,int acc_num))
{
	int counter = 1; //stores amount of accounts to choose from
	string search_to_edit;
	searchAccount(search_to_edit,message4search,acc,counter);
	if (search_to_edit == "0") return; //search_to_edit's assigned "0" if user wants to go back
	clearScreen();
	int choice = inputIntNumbers(message,1, counter);
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
	clearScreen();
	showAccountArray(acc);
	int choice = inputIntNumbers(EDIT_ACCOUNT_MENU,0,3);
	cout << YOU_SURE;
	char sure = _getch();
	cout << sure;
	system("pause");
	string login_savespot = acc[acc_num].login; //saves login in case to undo its change
	if (sure == '1')
	{
		switch (choice)
		{
		case 1: editLogin(login_savespot,acc,acc_num); break;
		case 2: edit(acc,acc_num,&Account::role,DONT_CHANGE_YOUR_ROLE,ROLE); break; //edit role
		case 3: edit(acc,acc_num,&Account::access, DONT_CHANGE_YOUR_ACCESS, ACCESS); break; //edit access
		//case 2:	editRole(acc,acc_num); break;
		//case 3: editAccess(acc,acc_num); break;
		case 0: break;
		}
	}
	writeAccountFile(acc);
}

void editLogin(string login_savespot, vector<Account>&acc, int acc_num)
{
	while (true)
	{
		clearScreen();
		showAccountArray(acc);
		acc[acc_num].login = check4TooBigString(LOGIN_LENGTH_LIMIT, justEnterChar, LOGIN_REQUEST, LOGIN_SIZE_EXCEEDED);
		if (acc[acc_num].login == NO_INFO) //if user wants to undo/go back
		{
			acc[acc_num].login = login_savespot;
			return;
		}
		while (!isLoginUnique(acc, acc[acc_num].login))
		{
			cout << EXISTING_LOGIN_ERROR;
		}
	}
}

template <typename T>
void edit(vector<Account>& acc, int acc_num, T Account::*field, string dont_message, string input_message)
{
	int field_choice = 0;
	clearScreen();
	showAccountArray(acc);
	if (acc[acc_num].*field) //if current user tries to change own role/access
	{
		cout << dont_message; //prints changing own role is forbidden
		return;
	}
	field_choice = inputIntNumbers(input_message,1, 2);
	if (field_choice == 1)
	{
		acc[acc_num].*field = 1;
	}
	else
	{
		acc[acc_num].*field = 0; //default role/access
	}
}

//void editRole(vector<Account>& acc, int acc_num)
//{
//	int role_choice = 0;
//	clearScreen();
//	showAccountArray(acc);
//	if (acc[acc_num].active) //if current user tries to change own role
//	{
//		cout << DONT_CHANGE_YOUR_ROLE; //prints changing own role is forbidden
//		return;
//	}
//	cout << ROLE;
//	role_choice = inputIntNumbers(1, 2);
//	if (role_choice == 1)
//	{
//		acc[acc_num].role = 1;
//	}
//	else
//	{
//		acc[acc_num].role = 0; //default role
//	}
//}
//void editAccess(vector<Account>& acc, int acc_num)
//{
//	int access_choice = 0;
//	clearScreen();
//	showAccountArray(acc);
//	if (acc[acc_num].active)
//	{
//		cout << DONT_CHANGE_YOUR_ACCESS;
//		return;
//	}
//	cout << ACCESS;
//	access_choice = inputIntNumbers(1, 2);
//	if (access_choice == 1)
//	{
//		acc[acc_num].access = 1;
//	}
//	else
//	{
//		acc[acc_num].access = 0;
//	}
//}

void searchAccount(string& search_to_edit,string message,vector<Account>& acc, int&counter)
{
	clearScreen();
	showAccountArray(acc);
	string temp_role, temp_access;
	search_to_edit= check4TooBigString(LOGIN_LENGTH_LIMIT, justEnterChar, message, LOGIN_SIZE_EXCEEDED); //returns "0" if user wants to go back
	if (search_to_edit == NO_INFO) return; //if user wants to go back
	int amount_of_accounts = acc.size();
	int search_size = search_to_edit.size();
	clearScreen();
	cout <<"--№--|"<< TABLE_ACCOUNTS_HEADER;
	for (int current_account = 0; current_account < amount_of_accounts; current_account++) //goes through all accounts
	{
		for (int current_letter = 0; current_letter < search_size; current_letter++) //compares letters in search_input and each account
		{
			if (search_to_edit[current_letter] != acc[current_account].login[current_letter]) //if any letter in account doesn't match
			{
				break; //moves on to the next account
			}
			//found accounts output (more info in showAccountArray function)
			roleAccessConverter(acc, current_account, temp_role, temp_access);
			string temp_4_login(LOGIN_LENGTH_LIMIT - acc[current_account].login.size(), ' ');
			string role_length(ROLE_LENGTH_LIMIT - temp_role.size(), ' ');
			string access_length(ACCESS_LENGTH_LIMIT - temp_access.size(), ' ');
			string counter_length(COUNTER_LENGTH_LIMIT - to_string(acc[current_account].search_counter).size(), ' ');
			cout <<counter_length<<acc[current_account].search_counter++ << "|" << acc[current_account].login << temp_4_login << "|" <<
				temp_role << role_length << "|" << temp_access << access_length << "|\n";
			counter++; //increasing counter of accounts in list
		}
	}
}
void deleteAccountInArray(vector<Account>& acc,int acc_num)
{
	clearScreen();
	showAccountArray(acc);
	cout << YOU_SURE;
	char sure;
	sure = _getch();
	cout << sure;
	system("pause");
	if (sure == '1')
	{
		acc.erase(acc.begin() + acc_num);
	}
	writeAccountFile(acc);
}
void changeLogin(vector<Account>& acc, Account& guest)
{
	logIn(acc, guest); //you need to verify own log-in to be able to change it - safety measure
	if(guest.active) //log in makes guest.active=false if unsuccessful
	{
		int vec_size = acc.size();
		for (int curr_acc = 0; curr_acc < vec_size; curr_acc++) //searching for current (active) account in system
		{
			if (acc[curr_acc].active == 1) 
			{
				clearScreen();
				cout << YOU_SURE;
				char sure= _getch();
				cout << sure;
				system("pause");
				if (sure == '1')
				{
					if (acc[curr_acc].role == 1) //saving previous role of account
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
	}
	else //if file is not opening
	{
		clearScreen();
		cout << NO_ACCOUNTS_CASE;
		system("pause");
		f_in.close();
		setDefaultAccount();
	}
	f_in.close();
	return amount_of_accounts;
}