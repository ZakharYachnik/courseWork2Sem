#include "Functions.h"

void Administrator::registration()
{
	int x = 90, y = 20; //������� ��������� �������

	login = writeLogin(x, y);// ������� ����������� ����� ������

	this->writePassword(x, y); // ������� ����������� ����� ������

	system("cls");

	try
	{
		Inform.open("InformationAdmins.txt", ofstream::app);

		Inform.seekg(0, ios_base::end);//������� ������� � ����� �����

		if (Inform.tellg() != 0) // �������� �� ������� �����
			Inform << '\n';

		x = 90;
		y = 20;

		GoToXY(x, y);
		cout << "������� ���� ������";

		this->writeFIO(x, y); // ���������� ���� ���
		GoToXY(90, y + 1);
		cout << "                          "; // ������� ������ ����� ���

		Inform << login;//������ ������ � ����
		Inform << '\n';
		this->encryption(); //������� ���������� ������
		Inform << password << '\n';
		this->decryption(); //������������� ������
		Inform << FIO << '\n';

		Inform.close();
	}
	catch (const exception& ex)
	{
		GoToXY(90, 12);
		cout << ex.what();
		GoToXY(90, 13);
		cout << "������ �������� �����!!!";
	}

	system("cls");
	GoToXY(90, 20);
	cout << "����������� �������� �������������� ������ �������!!!";
	_getch();
}

void Administrator::deleteAccount()
{
}

