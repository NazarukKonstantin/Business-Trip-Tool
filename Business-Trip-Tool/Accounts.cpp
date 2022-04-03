#include "Accounts.h"

void showOptionsOnEnter()
{
	cout << SIGN_UP_OR_LOG_IN;
	proceedPickedOption();
}
void proceedPickedOption()
{
	int choice = 0;
	cin >> choice;
	switch (choice)
	{
	case 1: signUp(); break;
	case 2: logIn(); break;
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
	writeEndAccountFile(def);
}


void signUp();
bool isLoginUnique();
bool isPasswordStrong();
string generateSalt();
string getSymbols4Salt();
string makePasswordHashedAndSalty(string input_password, string salt); 
void addAccountInArray(Account* arr, int& amount_of_accounts);	


void logIn();		
bool doesLoginExist();		
bool isPasswordCorrect();	

bool readAccountFile()
{
	vector <Account> acc;								//������ ���������
	int amount_of_accounts = countStructuresInFile();
	acc.reserve(amount_of_accounts);				// ������������� ������ ��� ������ ���������
	ifstream f_in(ACCOUNT_FILE_NAME, ios::in);			//��������� ���� � ������ ������
	int i = 0;											//������� ��� ���������� �� �����
	while (!f_in.eof())
	{
		f_in >> acc.at(i).login >> acc.at(i).hashed_salty_password >> acc.at(i).salt >> acc.at(i).role >> acc.at(i).access;
		i++;
	}
	f_in.close();
	showOptionsOnEnter();
}
void writeEndAccountFile(Account new_account)
{
	ofstream f_add(ACCOUNT_FILE_NAME, ios::app);			// ��������� ���� ��� ��������
	f_add << endl;
	f_add << new_account.login << " "
		<< new_account.hashed_salty_password << " "
		<< new_account.salt << " "
		<< new_account.role << " "
		<< new_account.access;
	f_add.close();
}
int countStructuresInFile()
{
	ifstream f_in(ACCOUNT_FILE_NAME, ios::in);
	int amount_of_accounts = 0;							//���-�� ��������� � �������, ����������� �� �����
	if (f_in.is_open())
	{
		string temp;
		while (getline(f_in, temp))						//��������� ��������� ���� ���������
		{
			amount_of_accounts++;						//���� ������� ������� ������, �������������� ���-�� ���������
		}
	}
	else
	{
		cout << NO_ACCOUNTS_CASE;						// � ������ ������������� ������� ���� � ������ ������ ��������� ���������
		f_in.close();
		setDefaultAccount();
	}
	f_in.close();
	return amount_of_accounts;
}