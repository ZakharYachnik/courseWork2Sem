#include "Functions.h"

int pointOfAdmin = 0;
int pointOfUs = 0;
fstream Inform;

vector<shared_ptr<Patient>> patients;
vector<shared_ptr<Administrator>> admins;

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

extern int getNumber()
{
    cin.unsetf(ios::skipws);
    while (true)
    {
        int tempVal;
        cin >> tempVal;

        if (cin.fail() || getchar() != '\n')
        {
            cout << "\n�� ����� �� �����!!!\n";
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "���������� ��� ���: ";
        }
        else
            return tempVal;
    }
}

extern void GoToXY(short x, short y)
{
    SetConsoleCursorPosition(hStdOut, { x, y });
}

extern void ConsoleCursorVisible(bool show, short size)
{
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hStdOut, &structCursorInfo);
    structCursorInfo.bVisible = show;
    structCursorInfo.dwSize = size;
    SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

extern string writeLogin(int& x, int& y) // ������� ����������� ����� ������
{
	int flOnUnique = 0; // ��������� �������(����)
	string tempLogin;

	while (1)
	{
		flOnUnique = 0;
		GoToXY(x, y);// �������� ���������
		cout << "������� �������� �����: ";
		cin >> tempLogin;

		for (auto& it : patients)
		{
			if (it->getLogin() == tempLogin)
				flOnUnique++;
		}

		for (auto& it : admins)
			if (it->getLogin() == tempLogin)
				flOnUnique++;


		if (flOnUnique == 0) //����� �� �������� �������� 
		{
			break;
		}
		else
		{
			system("cls");
			GoToXY(90, 23);
			cout << "���� ����� ��� �����!";
		}
	}

	return tempLogin;
}

extern int authorization()
{
	char c = '1';// ������� ��������� ����������
	string tempLogin;
	string tempPassword;
	string Login;
	string Password;
	string temp;

	int x = 90, y = 20;

	GoToXY(x, y);//��������� ���������
	cout << "������� �����: ";

	GoToXY(x, ++y);
	cout << "������� ������: ";

	ConsoleCursorVisible(true, 20);//������ ������ �������
	GoToXY(105, 20);
	cin >> Login;

	while (c != '\r') //���� ������ ���� �� enter
	{
		GoToXY(++x + 15, y);
		c = _getch();
		if (c != '\r' && c != 8)// �������� �� enter ��� backspace
		{
			Password += c;
			_putch('*');//����� ����������
		}
	}

	ConsoleCursorVisible(false, 100);// ������ ������ ���������

	Inform.open("InformationPatients.txt");
	pointOfUs = 0; //������� ������ ��������������� �������� 0
	if (Inform.is_open())
	{
		while (!Inform.eof())
		{
			getline(Inform, tempLogin);// ���������� �� ����� ������ � ������
			getline(Inform, tempPassword);
			for (int i = 0; i < size(tempPassword); i++)
			{
				tempPassword[i] -= 20;
			}

			pointOfUs++; // ���������� ������ ��������������� ��������

			if (tempLogin == Login)// ����� ������ �� ��������� ������� � �������
				if (tempPassword == Password)
				{
					Inform.close();
					return 0;//��������� �� ���� � ������� ��������
				}

			for (int i = 0; i < 6; i++)// ������� ������� � ����� 
				getline(Inform, temp);
		}
	}
	else
	{
		GoToXY(90, 26);
		cout << "���� �� ������!!!";
		_getch();
	}
	Inform.close();

	Inform.open("InformationAdmins.txt");
	pointOfAdmin = 0; //������� ������ ��������������� �������� 0
	if (Inform.is_open())
	{
		while (!Inform.eof())
		{
			getline(Inform, tempLogin);// ���������� �� ����� ������ � ������
			getline(Inform, tempPassword);
			for (int i = 0; i < size(tempPassword); i++)
			{
				tempPassword[i] -= 20;
			}

			pointOfAdmin++; // ���������� ������ ��������������� ��������

			if (tempLogin == Login)// ����� ������ �� ��������� ������� � �������
				if (tempPassword == Password)
				{
					Inform.close();
					return 1;//��������� �� ���� � ������� ��������
				}

			getline(Inform, temp);
		}
	}
	else
	{
		GoToXY(90, 26);
		cout << "���� �� ������!!!";
		_getch();
	}
	Inform.close();

	pointOfUs = 0;
	GoToXY(x, ++y);
	cout << "������ ��� ����� ��������!";
	Inform.close();

	return -1; // � ������ ������� ���������� -1
}
