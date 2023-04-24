#include "Functions.h"
#include <algorithm>

Administrator::Administrator(string FIO)
{
	this->FIO = FIO;
}

Administrator::Administrator()
{
}

void Administrator::registration()
{
	int x = 90, y = 20; //задание координат курсора
	Administrator admin;
	admin.login = writeLogin(x, y);// функция правильного ввода логина

	admin.writePassword(x, y); // Функция правильного ввода пароля

	system("cls");

	try
	{
		Inform.open("InformationAdmins.txt", ofstream::app);

		Inform.seekg(0, ios_base::end);//перенос курсора в конец файла

		if (Inform.tellg() != 0) // проверка на пустоту файла
			Inform << '\n';

		x = 90;
		y = 20;

		GoToXY(x, y);
		cout << "Введите ваши данные";

		admin.writeFIO(x, y); // правильный ввод ФИО
		GoToXY(90, y + 1);
		cout << "                          "; // очистка строки ввода ФИО

		Inform << admin.login;//запись данных в файл
		Inform << '\n';
		admin.encryption(); //функция шифрования пароля
		Inform << admin.password << '\n';
		admin.decryption(); //расшифрование пароля
		Inform << admin.FIO << '\n';

		admins.push_back(make_shared<Administrator>(admin));
		Inform.close();
	}
	catch (const exception& ex)
	{
		GoToXY(90, 12);
		cout << ex.what();
		GoToXY(90, 13);
		cout << "Ошибка открытия файла!!!";
	}

	system("cls");
	GoToXY(90, 20);
	cout << "Регистрация аккаунта администратора прошла успешно!!!";
	_getch();
}

void Administrator::deleteAccount()
{
	char ch = 0;
	int tempInt = 0;
	GoToXY(90, 20);
	cout << "Вы уверены, что хотите удалить аккаунт?";
	while (tempInt != 3)
	{
		if (tempInt == 0)
			SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		else
			SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
		GoToXY(90, 22);
		cout << "Да";

		if (tempInt == 1)
			SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		else
			SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
		GoToXY(90, 23);
		cout << "Нет";

		ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP:
			if (tempInt != 0)
				--tempInt;
			break;

		case DOWN:
			if (tempInt < 1)
				++tempInt;
			break;

		case ENTER:
			if (tempInt == 1)
				Menu::menuForAdmin();
			else
				tempInt = 3;
			break;
		}
	}

	admins.erase(admins.begin() + pointOfAdmin - 1);
	writeAdminFile();
	system("cls");
	GoToXY(90, 20);
	cout << "Аккаунт успешно удален!";
}

void Administrator::changeAdminInf()
{
	GoToXY(90, 20);
	cout << "Что вы хотите изменить";
	int activeMenu = 0;
	string changes[] = { "Изменить логин", "Изменить пароль", "Изменить ФИО" };
	char ch;

	while (true)
	{
		int x = 90, y = 21;
		GoToXY(x, y);

		for (int i = 0; i < size(changes); i++)
		{
			if (i == activeMenu)
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			else
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			GoToXY(x, y++);
			cout << changes[i];
		}

		ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP:
			if (activeMenu != 0)
				--activeMenu;
			break;

		case DOWN:
			if (activeMenu < size(changes) - 1)
				++activeMenu;
			break;

		case ENTER:
			system("cls");
			enterForChanges(activeMenu);
			Menu::menuForAdmin();
			break;
		}
	}
}

void Administrator::enterForChanges(int activeMenu)
{
	int x = 90, y = 20;

	switch (activeMenu)
	{
	case 0:
	{
		string tempLogin = writeLogin(x, y);
		this->setLogin(tempLogin);
		writeAdminFile();
		break;
	}

	case 1: {
		this->writePassword(x, y);
		writeAdminFile();
		break;
	}
	case 2:
	{
		this->writeFIO(x, y);
		writeAdminFile();
		break;
	}
	}
}

void Administrator::sortPatients()
{
	system("cls");
	string menu[] = { "ФИО", "Дата рождения", "Пол", "Город", "Номер телефона", "Диагноз", "Вернуться назад" };
	int active_menu = 0;
	if (patients.size() < 2)
	{
		GoToXY(90,20);
		cout << "Недостаточно элементов для сортировки!!!";
		_getch();
		return;
	}
	GoToXY(90, 19);
	cout << "Выберите параметр для сортировки";

	char ch;
	while (true)
	{
		int x = 90, y = 21;
		GoToXY(x, y);

		for (int i = 0; i < size(menu); i++)
		{
			if (i == active_menu)
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			else
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			GoToXY(x, y++);

			cout << menu[i];
		}

		ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP:
			if (active_menu != 0)
				--active_menu;
			break;

		case DOWN:
			if (active_menu < size(menu) - 1)
				++active_menu;
			break;

		case ENTER:
			system("cls");
			switch (active_menu)
			{
			case 0:
				sort(patients.begin(), patients.end(), [](std::shared_ptr<Patient>& prod1, std::shared_ptr<Patient>& prod2) {
					return prod1->getFIO() < prod2->getFIO();
					});
				break;

			case 1:
				sort(patients.begin(), patients.end(), [](std::shared_ptr<Patient>& prod1, std::shared_ptr<Patient>& prod2) {
					return prod1->getBirthday() < prod2->getBirthday();
					});
				break;

			case 2:
				sort(patients.begin(), patients.end(), [](std::shared_ptr<Patient>& prod1, std::shared_ptr<Patient>& prod2) {
					return prod1->getGender() < prod2->getGender();
					});
				break;

			case 3:
				sort(patients.begin(), patients.end(), [](std::shared_ptr<Patient>& prod1, std::shared_ptr<Patient>& prod2) {
					return prod1->getCity() < prod2->getCity();
					});
				break;

			case 4:
				sort(patients.begin(), patients.end(), [](std::shared_ptr<Patient>& prod1, std::shared_ptr<Patient>& prod2) {
					return prod1->getNumber() < prod2->getNumber();
					});
				break;

			case 5:
				sort(patients.begin(), patients.end(), [](std::shared_ptr<Patient>& prod1, std::shared_ptr<Patient>& prod2) {
					return prod1->getDiagnosis() < prod2->getDiagnosis();
					});
				break;

			case 6:
				return;
			}
			showAllPatients();
			_getch();
			return;
		}

	}
}

void Administrator::writeAdminFile()
{
	try
	{
		Inform.open("InformationAdmins.txt", ios_base::out);
		for (auto i : admins)
		{
			if (Inform.tellg() != 0) // проверка на пустоту файла
				Inform << '\n';
			Inform << i->login;
			Inform << '\n';
			i->encryption();
			Inform << i->password;
			i->decryption();
			Inform << '\n' << i->FIO;
		}
		Inform.close();
	}
	catch (const exception& ex)
	{
		GoToXY(90, 12);
		cout << ex.what();
		GoToXY(90, 13);
		cout << "Ошибка открытия файла!!!";
	}
}

void Administrator::outputListRecords()
{
	fstream patientsReports;
	string tempStr;
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	try
	{
		patientsReports.open("allReports.txt", ios_base::in);

		int x = 5, y = 10;
		int i = 0;
		int flagOnOutput = 0;
		while (patientsReports.tellg() != EOF)
		{
			if (i == 7)
			{
				i = 0;
				x += 50;
				if (++flagOnOutput == 4)
				{
					x = 5;
					y += 10;
					flagOnOutput = 0;
				}
				else 
					y -=7;
			}
			GoToXY(x, ++y);
			getline(patientsReports, tempStr);
			cout << tempStr;
			i++;
		}

		patientsReports.close();
	}
	catch (const exception& ex)
	{
		GoToXY(90, 12);
		cout << ex.what();
		GoToXY(90, 13);
		cout << "Ошибка открытия файла!!!";
	}

	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
}

void Administrator::searchStructure()
{
	string Menu[] = { "ФИО", "Дата рождения", "Пол", "Город", "Номер телефона", "Диагноз", "Вернуться назад" };
	int active_menu = 0;

	GoToXY(90, 19);
	cout << "Выберите параметр для поиска";

	char ch;
	while (true)
	{
		int x = 90, y = 21;
		GoToXY(x, y);

		for (int i = 0; i < size(Menu); i++)
		{
			if (i == active_menu)
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			else
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			GoToXY(x, y++);

			cout << Menu[i];
		}

		ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP:
			if (active_menu != 0)
				--active_menu;
			break;

		case DOWN:
			if (active_menu < size(Menu) - 1)
				++active_menu;
			break;

		case ENTER:
			system("cls");
			switch (active_menu)
			{
			case 0:
				findFIO();
				break;

			case 1:
				findBirthday();
				break;

			case 2:
				findGender();
				break;

			case 3:
				findCity();
				break;

			case 4:
				findNumber();
				break;

			case 5:
				findDiagnosis();
				break;

			case 6:
				return;
			}
			return;
			break;
		}
	}
}

void Administrator::findFIO()
{
	string tempFIO;
	GoToXY(90, 18);
	cout << "Введите ФИО: ";
	if (cin.peek() == '\n')
		cin.ignore(10000, '\n');

	getline(cin, tempFIO);
	int flagOnFirst = 0;
	int x = 20, y = 22;//задание переменных курсора
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	for (auto i : patients)
	{
		if (i->getFIO() == tempFIO)//если совпадают
		{
			if (flagOnFirst == 0)//вывод только перед первым элементом
			{
				GoToXY(x, 20);//задание положения курсора
				cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------";
				GoToXY(x, 21);
				cout << "|               ФИО                |      Дата рождения      |         Пол           |           Город           |        Номер телефона       |        Диагноз       |";
				GoToXY(x, 22);
				cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------";
			}

			GoToXY(x, ++y);
			cout << "| " << setw(32) << i->getFIO() << " | " << setw(18) << i->getBirthday() << setw(8) << " | " << setw(12)
				<< i->getGender() << setw(12) << " | " << setw(16) << i->getCity() << setw(12) << " | "
				<< setw(20) << i->getNumber() << setw(10) << " | " << setw(14) << i->getDiagnosis() << setw(8) << " |";			GoToXY(20, ++y);
			cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------";
			flagOnFirst++;
		}
	}
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);

	if (flagOnFirst == 0)//вывод о неудаче поиска
	{
		GoToXY(90, 20);
		cout << "Человек с таким ФИО не найден!";
	}
}

void Administrator::findBirthday()
{
	string tempBirthday;
	GoToXY(90, 18);
	cout << "Введите дату рождения: ";
	if (cin.peek() == '\n')
		cin.ignore(10000, '\n');
	getline(cin, tempBirthday);

	int flagOnFirst = 0;
	int x = 20, y = 22;//задание переменных курсора
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	for (auto i : patients)
	{
		if (i->getBirthday() == tempBirthday)//если совпадают
		{
			if (flagOnFirst == 0)//вывод только перед первым элементом
			{
				GoToXY(x, 20);//задание положения курсора
				cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------";
				GoToXY(x, 21);
				cout << "|               ФИО                |      Дата рождения      |         Пол           |           Город           |        Номер телефона       |        Диагноз       |";
				GoToXY(x, 22);
				cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------";
			}

			GoToXY(x, ++y);
			cout << "| " << setw(32) << i->getFIO() << " | " << setw(18) << i->getBirthday() << setw(8) << " | " << setw(12)
				<< i->getGender() << setw(12) << " | " << setw(16) << i->getCity() << setw(12) << " | "
				<< setw(20) << i->getNumber() << setw(10) << " | " << setw(14) << i->getDiagnosis() << setw(8) << " |";			GoToXY(20, ++y);
			cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------";
			flagOnFirst++;
		}
	}
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);

	if (flagOnFirst == 0)
	{
		GoToXY(90, 20);
		cout << "Человек с такой датой рождения не найден!";
	}
}

void Administrator::findGender()
{
	string tempGender;
	GoToXY(90, 18);
	cout << "Введите пол: ";
	if (cin.peek() == '\n')
		cin.ignore(10000, '\n');

	getline(cin, tempGender);
	int flagOnFirst = 0;
	int x = 20, y = 22;//задание переменных курсора
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	for (auto i : patients)
	{
		if (i->getGender() == tempGender)//если совпадают
		{
			if (flagOnFirst == 0)//вывод только перед первым элементом
			{
				GoToXY(x, 20);//задание положения курсора
				cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------";
				GoToXY(x, 21);
				cout << "|               ФИО                |      Дата рождения      |         Пол           |           Город           |        Номер телефона       |        Диагноз       |";
				GoToXY(x, 22);
				cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------";
			}

			GoToXY(x, ++y);
			cout << "| " << setw(32) << i->getFIO() << " | " << setw(18) << i->getBirthday() << setw(8) << " | " << setw(12)
				<< i->getGender() << setw(12) << " | " << setw(16) << i->getCity() << setw(12) << " | "
				<< setw(20) << i->getNumber() << setw(10) << " | " << setw(14) << i->getDiagnosis() << setw(8) << " |";			GoToXY(20, ++y);
			cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------";
			flagOnFirst++;
		}
	}
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);

	if (flagOnFirst == 0)
	{
		GoToXY(90, 20);
		cout << "Человек такого пола не найден!";
	}
}

void Administrator::findNumber()
{
	string tempNumber;
	GoToXY(90, 18);
	cout << "Введите номер телефона: ";
	if (cin.peek() == '\n')
		cin.ignore(10000, '\n');

	getline(cin, tempNumber);
	int flagOnFirst = 0;
	int x = 20, y = 22;//задание переменных курсора
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	for (auto i : patients)
	{
		if (i->getNumber() == tempNumber)//если совпадают
		{
			if (flagOnFirst == 0)//вывод только перед первым элементом
			{
				GoToXY(x, 20);//задание положения курсора
				cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------";
				GoToXY(x, 21);
				cout << "|               ФИО                |      Дата рождения      |         Пол           |           Город           |        Номер телефона       |        Диагноз       |";
				GoToXY(x, 22);
				cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------";
			}

			GoToXY(x, ++y);
			cout << "| " << setw(32) << i->getFIO() << " | " << setw(18) << i->getBirthday() << setw(8) << " | " << setw(12)
				<< i->getGender() << setw(12) << " | " << setw(16) << i->getCity() << setw(12) << " | "
				<< setw(20) << i->getNumber() << setw(10) << " | " << setw(14) << i->getDiagnosis() << setw(8) << " |";			GoToXY(20, ++y);
			cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------";
			flagOnFirst++;
		}
	}
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);

	if (flagOnFirst == 0)
	{
		GoToXY(90, 20);
		cout << "Человек с таким номером не найден!";
	}
}

void Administrator::findCity()
{
	string tempCity;
	GoToXY(90, 18);
	cout << "Введите город: ";
	if (cin.peek() == '\n')
		cin.ignore(10000, '\n');

	getline(cin, tempCity);
	int flagOnFirst = 0;
	int x = 20, y = 22;//задание переменных курсора
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	for (auto i : patients)
	{
		if (i->getCity() == tempCity)//если совпадают
		{
			if (flagOnFirst == 0)//вывод только перед первым элементом
			{
				GoToXY(x, 20);//задание положения курсора
				cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------";
				GoToXY(x, 21);
				cout << "|               ФИО                |      Дата рождения      |         Пол           |           Город           |        Номер телефона       |        Диагноз       |";
				GoToXY(x, 22);
				cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------";
			}

			GoToXY(x, ++y);
			cout << "| " << setw(32) << i->getFIO() << " | " << setw(18) << i->getBirthday() << setw(8) << " | " << setw(12)
				<< i->getGender() << setw(12) << " | " << setw(16) << i->getCity() << setw(12) << " | "
				<< setw(20) << i->getNumber() << setw(10) << " | " << setw(14) << i->getDiagnosis() << setw(8) << " |";			GoToXY(20, ++y);
			cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------";
			flagOnFirst++;
		}
	}
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);

	if (flagOnFirst == 0)
	{
		GoToXY(90, 20);
		cout << "Человек из этого города не найден!";
	}
}

void Administrator::findDiagnosis()
{
	string tempDiagnosis;
	GoToXY(90, 18);
	cout << "Введите диагноз: ";
	if (cin.peek() == '\n')
		cin.ignore(10000, '\n');

	getline(cin, tempDiagnosis);
	int flagOnFirst = 0;
	int x = 20, y = 22;//задание переменных курсора
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	for (auto i : patients)
	{
		if (i->getDiagnosis() == tempDiagnosis)//если совпадают
		{
			if (flagOnFirst == 0)//вывод только перед первым элементом
			{
				GoToXY(x, 20);//задание положения курсора
				cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------";
				GoToXY(x, 21);
				cout << "|               ФИО                |      Дата рождения      |         Пол           |           Город           |        Номер телефона       |        Диагноз       |";
				GoToXY(x, 22);
				cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------";
			}

			GoToXY(x, ++y);
			cout << "| " << setw(32) << i->getFIO() << " | " << setw(18) << i->getBirthday() << setw(8) << " | " << setw(12)
				<< i->getGender() << setw(12) << " | " << setw(16) << i->getCity() << setw(12) << " | "
				<< setw(20) << i->getNumber() << setw(10) << " | " << setw(14) << i->getDiagnosis() << setw(8) << " |";			GoToXY(20, ++y);
			cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------";
			flagOnFirst++;
		}
	}
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);

	if (flagOnFirst == 0)
	{
		GoToXY(90, 20);
		cout << "Человек с таим диагнозом не найден!";
	}


}

void Administrator::showAllPatients()
{
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	int x = 20, y = 20;

	GoToXY(x, y);
	cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------";
	GoToXY(x, ++y);
	cout << "|               ФИО                |      Дата рождения      |         Пол           |           Город           |        Номер телефона       |        Диагноз       |";
	GoToXY(x, ++y);
	cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------";

	for(auto i : patients)
	{
		GoToXY(x, ++y);
		cout << "| " << setw(32) << i->getFIO() << " | " << setw(18) << i->getBirthday() << setw(8) << " | " << setw(12) 
			 << i->getGender() << setw(12) << " | " << setw(16) << i->getCity() << setw(12) << " | "
			 << setw(20) << i->getNumber() << setw(10) << " | " << setw(14) << i->getDiagnosis() << setw(8) << " |";
		GoToXY(x, ++y);
		cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------";
	}

	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
}

