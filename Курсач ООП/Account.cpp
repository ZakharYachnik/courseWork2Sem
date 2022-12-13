#include "Functions.h"

string Account::getLogin()
{
	return login;
}

string Account::getPassword()
{
	return password;
}

string Account::getFIO()
{
	return FIO;
}

void Account::setLogin(string login)
{
	this->login = login;
}

void Account::setPassword(string password)
{
	this->password = password;
}

void Account::setFIO(string FIO)
{
	this->FIO = FIO;
}

void Account::encryption()
{
    for (int i = 0; i < size(password); i++)
    {
        password[i] += 20;
    }
}

void Account::decryption()
{
    for (int i = 0; i < size(password); i++)
    {
        password[i] -= 20;
    }
}

void Account::writePassword(int& x, int& y)// функция введения пароля 
{
	password = "";
	char c = '1';
	GoToXY(x, ++y);
	cout << "Введите желаемый пароль: ";
	while (c != '\r')//вводим но нажатия клавиши Enter
	{
		c = _getch();
		if (c != '\r' && c != 8)//сравнение с enter и backspace
		{
			password += c;
			_putch('*');//вывод звездочки вместо символа
		}

		if (c == '\r' && size(password) < 5) // проверка на длину пароля
		{
			GoToXY(90, 22);
			cout << "Пароль слишком короткий!";
			GoToXY(115, 21);
			cout << "           ";
			GoToXY(115, 21);
			c = '1';
			password = "";
		}
	}
}

void Account::writeFIO(int& x, int& y)
{
	int flagSpace = 0; // флаг для пробелов
	int flagNum = 0; // флаг для чисел

	GoToXY(x, ++y);
	cout << "ФИО: ";

	while (1)
	{
		GoToXY(x + 5, y); // очистка поля ввода
		cout << "                                ";
		GoToXY(x + 5, y);
		flagSpace = 0;
		flagNum = 0;

		if(cin.peek() == '\n')
			cin.ignore(10000, '\n');
		getline(cin, FIO);

		for (int i = 0; i < size(FIO); i++) // поиск пробелов и цифр
		{
			if (FIO[i] == ' ')
				flagSpace++;

			if ((int)FIO[i] > 47 && (int)FIO[i] < 58)
				flagNum++;
		}

		if ((flagSpace != 1 && flagSpace != 2) || flagNum > 0) // сообщение о неправильном вводе
		{
			GoToXY(x, y + 1);
			cout << "ФИО введенно неверно!";
			FIO = "";
		}
		else break;
	}
}