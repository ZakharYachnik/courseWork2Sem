#include "Functions.h"

void Administrator::registration()
{
	int x = 90, y = 20; //задание координат курсора

	login = writeLogin(x, y);// функция правильного ввода логина

	this->writePassword(x, y); // Функция правильного ввода пароля

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

		this->writeFIO(x, y); // правильный ввод ФИО
		GoToXY(90, y + 1);
		cout << "                          "; // очистка строки ввода ФИО

		Inform << login;//запись данных в файл
		Inform << '\n';
		this->encryption(); //функция шифрования пароля
		Inform << password << '\n';
		this->decryption(); //расшифрование пароля
		Inform << FIO << '\n';

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
}

