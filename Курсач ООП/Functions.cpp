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

extern string writeLogin(int& x, int& y) // функция правильного ввода логина
{
	int flOnUnique = 0; // временный счетчик(флаг)
	string tempLogin;

	while (1)
	{
		flOnUnique = 0;
		GoToXY(x, y);// указание координат
		cout << "Введите желаемый логин: ";
		cin >> tempLogin;

		for (auto& it : patients)
		{
			if (it->getLogin() == tempLogin)
				flOnUnique++;
		}

		for (auto& it : admins)
			if (it->getLogin() == tempLogin)
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

extern int authorization()
{
	char c = '1';// задание временных переменных
	string tempLogin;
	string tempPassword;
	string Login;
	string Password;
	string temp;

	int x = 90, y = 20;

	GoToXY(x, y);//установка координат
	cout << "Введите логин: ";

	GoToXY(x, ++y);
	cout << "Введите пароль: ";

	ConsoleCursorVisible(true, 20);//делает курсор видимым
	GoToXY(105, 20);
	cin >> Login;

	while (c != '\r') //ввод пароля пока не enter
	{
		GoToXY(++x + 15, y);
		c = _getch();
		if (c != '\r' && c != 8)// проверка на enter или backspace
		{
			Password += c;
			_putch('*');//вывод звездночки
		}
	}

	ConsoleCursorVisible(false, 100);// делает курсор невидимым

	Inform.open("InformationPatients.txt");
	pointOfUs = 0; //задание номера авторизованного аккаунта 0
	if (Inform.is_open())
	{
		while (!Inform.eof())
		{
			getline(Inform, tempLogin);// считывание из файла логина и пароля
			getline(Inform, tempPassword);
			for (int i = 0; i < size(tempPassword); i++)
			{
				tempPassword[i] -= 20;
			}

			pointOfUs++; // увелечение номера авторизованного аккаунта

			if (tempLogin == Login)// поиск логина из записаных логинов и паролей
				if (tempPassword == Password)
				{
					Inform.close();
					return 0;//указатель на вход в аккаунт пациента
				}

			for (int i = 0; i < 6; i++)// перевод курсора в файле 
				getline(Inform, temp);
		}
	}
	else
	{
		GoToXY(90, 26);
		cout << "Файл не открыт!!!";
		_getch();
	}
	Inform.close();

	Inform.open("InformationAdmins.txt");
	pointOfAdmin = 0; //задание номера авторизованного аккаунта 0
	if (Inform.is_open())
	{
		while (!Inform.eof())
		{
			getline(Inform, tempLogin);// считывание из файла логина и пароля
			getline(Inform, tempPassword);
			for (int i = 0; i < size(tempPassword); i++)
			{
				tempPassword[i] -= 20;
			}

			pointOfAdmin++; // увелечение номера авторизованного аккаунта

			if (tempLogin == Login)// поиск логина из записаных логинов и паролей
				if (tempPassword == Password)
				{
					Inform.close();
					return 1;//указатель на вход в аккаунт пациента
				}

			getline(Inform, temp);
		}
	}
	else
	{
		GoToXY(90, 26);
		cout << "Файл не открыт!!!";
		_getch();
	}
	Inform.close();

	pointOfUs = 0;
	GoToXY(x, ++y);
	cout << "Пароль или логин неверный!";
	Inform.close();

	return -1; // в случае неудачи возвращаем -1
}
