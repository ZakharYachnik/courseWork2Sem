#include "Functions.h"


string Patient::getBirthday()
{
	return birthday;
}

string Patient::getCity()
{
	return city;
}

string Patient::getNumber()
{
	return number;
}

string Patient::getGender()
{
	return gender;
}

string Patient::getDiagmosis()
{
	return diagnosis;
}


void Patient::setBirthday(string birthday)
{
	this->birthday = birthday;
}

void Patient::setCity(string city)
{
	this->city = city;
}

void Patient::setNumber(string number)
{
	this->number = number;
}

void Patient::setGender(string gender)
{
	this->gender = gender;
}

void Patient::setDiagmosis(string diagnosis)
{
	this->diagnosis = diagnosis;
}

void Patient:: registration()
{
	int x = 90, y = 20; //задание координат курсора

	login = writeLogin(x, y);// функция правильного ввода логина

	this->writePassword(x, y); // Функция правильного ввода пароля

	system("cls");

	try
	{
		Inform.open("InformationPatients.txt", ofstream::app);

		Inform.seekg(0, ios_base::end);//перенос курсора в конец файла

		if (Inform.tellg() != 0) // проверка на пустоту файла
			Inform << '\n';

		x = 90;
		y = 20;

		GoToXY(x, y);
		cout << "Введите ваши данные";

		this->writeFIO(x, y); // правильный ввод ФИО
		GoToXY(90, y + 1);
		cout << "                          "; // очистка строки ввода ФИО


		this->writeDate(x, y); // Правильный ввод даты

		GoToXY(x, ++y);
		cout << "                          ";
		this->writeGender(x, y); // парвильрный ввод пола

		GoToXY(90, y + 1);
		cout << "                    ";
		this->writeCity(x, y); // правильный ввод города

		GoToXY(90, y + 1);
		cout << "                        ";

		this->writeNumber(x, y); // правильный ввод города

		GoToXY(90, y + 1);
		cout << "                          ";
		GoToXY(x, ++y);
		cout << "Диагноз: ";
		cin >> diagnosis;
		

		Inform << login;//запись данных в файл
		Inform << '\n';
		this->encryption(); //функция шифрования пароля
		Inform << password << '\n';
		this->decryption(); //расшифрование пароля
		Inform << FIO << '\n';
		Inform << birthday << '\n';
		Inform << gender << '\n';
		Inform << city << '\n';
		Inform << number << '\n';
		Inform << diagnosis;

		Inform.close();
	}
	catch(const exception & ex)
	{
		GoToXY(90, 12);
		cout << ex.what();
		GoToXY(90, 13);
		cout << "Ошибка открытия файла!!!";
	}

	system("cls");
	GoToXY(90, 20);
	cout << "Регистрация аккаунта прошла успешно!!!";
	_getch();
}

void Patient::writeCity(int& x, int& y)
{
	int fl = 0;
	GoToXY(x, ++y);
	cout << "Город: ";

	while (1)
	{
		if(cin.peek() == '\n')
			cin.ignore(10000, '\n');
		getline(cin, city);
		fl = 0;
		for (int i = 0; i < size(city); i++) //проверка на наличие пробелов и цифр
		{
			if (city[i] == ' ' || ((int)city[i] > 47 && (int)city[i] < 58))
				fl++;
		}

		if (fl == 0) // сообщение о неправильном вводе
			break;
		else
		{
			GoToXY(x + 7, y);
			cout << "                  ";
			GoToXY(x, y + 1);
			cout << "Город введен неверно!";
			GoToXY(x + 7, y);
		}
	}
}

void Patient::writeGender(int& x, int& y)
{
	int fl = 0;
	GoToXY(x, y);
	cout << "Пол: ";
	do
	{
		if (fl != 0) // сообщение о некорректном вводе
		{
			GoToXY(90, y + 1);
			cout << "Пол введен неверно!";
		}
		GoToXY(x + 5, y);
		cout << "                     ";//очистка поля ввода
		GoToXY(x + 5, y);
		cin >> gender;
		fl++;
	} while (gender != "Мужской" && gender != "Женский" && gender != "женский" && gender != "мужской"); //пока не будет верно введено
}

void Patient::writeDate(int& x, int& y)//функция корректного ввода даты
{
	char c = '1'; //переменная для ввода
	int fl = 0; //флаг
	bool tempBool = true; // временная булевская переменная
	GoToXY(x, ++y); // установка координат
	cout << "Дата рождения: ";

	while (tempBool) //вводить пока не станет false
	{
		GoToXY(105, y);
		while (c != '\r' && fl != 11) // пока не enter или не введено 11 символов
		{
			c = _getch();

			if (c != '\r' && c != 8) // проверяем на enter и на backspace
			{
				if (fl != 2 && fl != 5)// если 3 или 5 элемент то выводим точку
				{
					_putch(c);
					birthday += c;
				}
				else
				{
					_putch('.');
					birthday += '.';
				}
				fl++;
			}
		}
		if (fl == 10) {
			int temp1 = (birthday[0] - 48) * 10 + (birthday[1] - 48);//перевод из char в числа
			int temp2 = (birthday[3] - 48) * 10 + (birthday[4] - 48);
			int temp3 = (birthday[6] - 48) * 1000 + (birthday[7] - 48) * 100 + (birthday[8] - 48) * 10 + (birthday[9] - 48);

			if ((temp1 > 31 || temp1 < 1) || (temp2 < 1 || temp2 > 12) || (temp3 > 2022 || temp3 < 1900)) // проверка на корректность даты
			{
				GoToXY(x, y + 1);
				cout << "Дата введена неверно!";

				for (int i = 0; i < 15; i++) // очистка поля ввода
				{
					GoToXY(x + 15 + i, y);
					cout << " ";
				}

				birthday = "";
				fl = 0;
				c = '1';
			}
			else
				tempBool = false; // для выхода из основного цикла
		}

		else
		{
			GoToXY(x, y + 1);
			cout << "Дата введена неверно!";

			for (int i = 0; i < 15; i++)
			{
				GoToXY(105 + i, y);
				cout << " ";
			}
			birthday = "";
			fl = 0;
			c = '1';
		}
	}
}

void Patient::writeNumber(int& x, int& y)
{
	GoToXY(x, ++y);
	cout << "Номер телефона: ";
	int fl = 0;
	while (1)
	{
		cin >> number;
		 
		fl = 0;
		for (int i = 0; i < size(number); i++) // проверка на не цифр
		{
			if (number[i] != '+' && ((int)number[i] < 48 || (int)number[i] > 57))
				fl++;
		}

		if (fl == 0 && size(number) == 13) // вывод сообщения если введено неверно
			break;
		else
		{
			GoToXY(x + 16, y);
			cout << "                     ";
			GoToXY(x, y + 1);
			cout << "Номер введен неверно!";
			GoToXY(x + 16, y);
		}
	}
}