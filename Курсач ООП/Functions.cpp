#include "Functions.h"

int pointOfAdmin = 0;
int pointOfUs = 0;
fstream Inform;

vector<Doctor> doctors(0);
vector<Patient> patients(0);
vector<Administrator> admins(0);

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
            cout << "\nВы ввели не число!!!\n";
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Попробуйте еще раз: ";
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

extern void activeMenu()
{
	system("cls");
	pointOfAdmin = 0;
	pointOfUs = 0;
	string firstMenu[] = { "Авторизация", "Регистрация", "Выход" };
	int active_menu = 0;

	char ch;
	while (true)
	{
		int x = 90, y = 20;
		GoToXY(x, y);

		for (int i = 0; i < size(firstMenu); i++)
		{
			if (i == active_menu)
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			else
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			GoToXY(x, y++);
			cout << firstMenu[i];
		}

		ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case ESC:
			exit(0);

		case UP:
			if (active_menu != 0)
				--active_menu;
			break;

		case DOWN:
			if (active_menu < size(firstMenu) - 1)
				++active_menu;
			break;

		case ENTER:
			system("cls");

			switch (active_menu)
			{
			case 0:
			{
				int j = -1, flag = 0;
				while (j != 0 && j != 1)
				{
					system("cls");
					if (flag != 0)
					{
						GoToXY(90, 22);
						cout << "Неверный парол или логин!";
					}
					flag++;
					//j = authorization();
				}
				if (j == 0)
				{
					system("cls");
					menuForUser();
				}
				else
				{
					system("cls");
					menuForAdmin();
				}
				break;
			}

			case 1:
			{
				Patient temp;
				patients.push_back(temp);
				patients[patients.size() - 1].registration();
				pointOfUs =	patients.size() - 1    ; // задание позиции пациента
				system("cls");
				menuForUser();
				break;
			}

			case 2:
				exit(0);
			}
			break;
		}
	}
}

void menuForAdmin()
{
	cout << "Hi";
}

void menuForUser()
{
	cout << "Hi";
}

string writeLogin(int& x, int& y) // функция правильного ввода логина
{
	int flOnUnique = 0; // временный счетчик(флаг)
	string tempLogin;

	while (1)
	{
		flOnUnique = 0;
		GoToXY(x, y);// указание координат
		cout << "Введите желаемый логин: ";
		cin >> tempLogin;

		for(auto& it: patients)
		{
			if (it.getLogin() == tempLogin)
				flOnUnique++;
		}

		for(auto& it: doctors)
		{
			if (it.getLogin() == tempLogin)
				flOnUnique++;
		}

		for (auto& it : admins)
			if (it.getLogin() == tempLogin)
				flOnUnique++;


		if (flOnUnique == 0) //вывод об неверном введении 
		{
			break;
		}
		else
		{
			system("cls");
			GoToXY(90, 23);
			cout << "Этот логин уже занят!";
		}
	}

	return tempLogin;
}


