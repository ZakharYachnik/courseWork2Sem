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

void Account::writePassword(int& x, int& y)// ������� �������� ������ 
{
	password = "";
	char c = '1';
	GoToXY(x, ++y);
	cout << "������� �������� ������: ";
	while (c != '\r')//������ �� ������� ������� Enter
	{
		c = _getch();
		if (c != '\r' && c != 8)//��������� � enter � backspace
		{
			password += c;
			_putch('*');//����� ��������� ������ �������
		}

		if (c == '\r' && size(password) < 5) // �������� �� ����� ������
		{
			GoToXY(90, 22);
			cout << "������ ������� ��������!";
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
	int flagSpace = 0; // ���� ��� ��������
	int flagNum = 0; // ���� ��� �����

	GoToXY(x, ++y);
	cout << "���: ";

	while (1)
	{
		GoToXY(x + 5, y); // ������� ���� �����
		cout << "                                ";
		GoToXY(x + 5, y);
		flagSpace = 0;
		flagNum = 0;

		if(cin.peek() == '\n')
			cin.ignore(10000, '\n');
		getline(cin, FIO);

		for (int i = 0; i < size(FIO); i++) // ����� �������� � ����
		{
			if (FIO[i] == ' ')
				flagSpace++;

			if ((int)FIO[i] > 47 && (int)FIO[i] < 58)
				flagNum++;
		}

		if ((flagSpace != 1 && flagSpace != 2) || flagNum > 0) // ��������� � ������������ �����
		{
			GoToXY(x, y + 1);
			cout << "��� �������� �������!";
			FIO = "";
		}
		else break;
	}
}