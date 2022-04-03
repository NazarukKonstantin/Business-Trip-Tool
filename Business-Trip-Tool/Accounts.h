#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "sha256.h"

using namespace std;
struct Account
{
	string login;					
	string hashed_salty_password;							
	string salt;
	bool role = false;
	int access = -1;
}; //структура содержит инф-цию отдельного аккаунта: логин, хэшированный пароль, соль, статус (пользователь или администратор) и также уровень доступа, определяемый админ-ом

const string ACCOUNT_FILE_NAME = "accounts_list.txt";
const string SIGN_UP_OR_LOG_IN ="1. Зарегестрироваться\n2.Войти\n0.Выход\n";
const string LOGIN_REQUEST = "Введите логин: ";
const string PASSWORD_REQUEST = "Введите пароль: ";
const string EXISTING_LOGIN_ERROR = "Такой логин уже существует. Пожалуйста, введите другой: ";
const string WRONG_ENTER = "Неверный логин или пароль. Попробуйте ещё раз.\n";
const string NO_ACCOUNTS_CASE = "Ваш аккаунт - первый в системе.\nВы получили права администратора.\nВаш логин - Admin, ваш пароль - Admin.\n\
Логин и пароль можно изменить в соответствующем пункте меню.\n";
const string WEAK_PASSWORD = "Ваш пароль слишком слаб, безопасный пароль должен содержать от 8 до 16 символов,\n\
включая как минимум одну строчную и заглавную букву, одну цифру и один символ типа @ # $ % * и т.п.\n";
const string PASSWORD_CONFIRMATION = "Вы подтверждаете пароль?\n\
(В дальнейшем можно изменить пароль в соответствующем пункте меню)\n1.Да\n2.Нет\n";

const int SALT_SIZE = 16; // кол-во символов в соли
const int SYMBOLS_SIZE = 62; // количество символов для генерации соли


void showOptionsOnEnter(); // отображает вариант регистрации и входа при запуске программы
void proceedPickedOption(); // принимает выбор пользователя и вызывает ф-ции входа и регистрации соответственно
void setDefaultAccount();	// создаёт аккаунт Login: Admin; Password: Admin; если файл аккаунтов не существует

void signUp();		// выполняет команды и вызывает ф-ции, непосредственно связанные с регистрацией в систему
bool isLoginUnique(); // проверяет логин на уникальность
bool isPasswordStrong(); //проверяет пароль на безопасность
string generateSalt(); //генеруирует соль
string getSymbols4Salt(); //создаёт набор символов, из которых генерируется соль
string makePasswordHashedAndSalty(string input_password, string salt); // хэширует пароль с солью
void addAccountInArray(Account* arr, int& amount_of_accounts);	//добавляет логин и захэшированный пароль в массив структур; первонач. role=0, access=-1;


void logIn();		// выполняет команды и вызывает ф-ции, непосредственно связанные со входом в систему, где данный аккаунт зарегестрирован
bool doesLoginExist();		// проверяет, существует ли логин в системе
bool isPasswordCorrect();	// проверяет правильность введённого пароля

bool readAccountFile();		// считывает данные из файла аккаунтов
int countStructuresInFile();		// считает кол-во структур/аккаунтов в файле
void writeEndAccountFile(Account new_account);		// записывает данные нового аккаунта в конец файла аккаунтов


