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
	int x = 90, y = 20; //������� ��������� �������

	login = writeLogin(x, y);// ������� ����������� ����� ������

	this->writePassword(x, y); // ������� ����������� ����� ������

	system("cls");

	try
	{
		Inform.open("InformationPatients.txt", ofstream::app);

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


		this->writeDate(x, y); // ���������� ���� ����

		GoToXY(x, ++y);
		cout << "                          ";
		this->writeGender(x, y); // ����������� ���� ����

		GoToXY(90, y + 1);
		cout << "                    ";
		this->writeCity(x, y); // ���������� ���� ������

		GoToXY(90, y + 1);
		cout << "                        ";

		this->writeNumber(x, y); // ���������� ���� ������

		GoToXY(90, y + 1);
		cout << "                          ";
		GoToXY(x, ++y);
		cout << "�������: ";
		cin >> diagnosis;
		

		Inform << login;//������ ������ � ����
		Inform << '\n';
		this->encryption(); //������� ���������� ������
		Inform << password << '\n';
		this->decryption(); //������������� ������
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
		cout << "������ �������� �����!!!";
	}

	system("cls");
	GoToXY(90, 20);
	cout << "����������� �������� ������ �������!!!";
	_getch();
}

void Patient::writeCity(int& x, int& y)
{
	int fl = 0;
	GoToXY(x, ++y);
	cout << "�����: ";

	while (1)
	{
		if(cin.peek() == '\n')
			cin.ignore(10000, '\n');
		getline(cin, city);
		fl = 0;
		for (int i = 0; i < size(city); i++) //�������� �� ������� �������� � ����
		{
			if (city[i] == ' ' || ((int)city[i] > 47 && (int)city[i] < 58))
				fl++;
		}

		if (fl == 0) // ��������� � ������������ �����
			break;
		else
		{
			GoToXY(x + 7, y);
			cout << "                  ";
			GoToXY(x, y + 1);
			cout << "����� ������ �������!";
			GoToXY(x + 7, y);
		}
	}
}

void Patient::writeGender(int& x, int& y)
{
	int fl = 0;
	GoToXY(x, y);
	cout << "���: ";
	do
	{
		if (fl != 0) // ��������� � ������������ �����
		{
			GoToXY(90, y + 1);
			cout << "��� ������ �������!";
		}
		GoToXY(x + 5, y);
		cout << "                     ";//������� ���� �����
		GoToXY(x + 5, y);
		cin >> gender;
		fl++;
	} while (gender != "�������" && gender != "�������" && gender != "�������" && gender != "�������"); //���� �� ����� ����� �������
}

void Patient::writeDate(int& x, int& y)//������� ����������� ����� ����
{
	char c = '1'; //���������� ��� �����
	int fl = 0; //����
	bool tempBool = true; // ��������� ��������� ����������
	GoToXY(x, ++y); // ��������� ���������
	cout << "���� ��������: ";

	while (tempBool) //������� ���� �� ������ false
	{
		GoToXY(105, y);
		while (c != '\r' && fl != 11) // ���� �� enter ��� �� ������� 11 ��������
		{
			c = _getch();

			if (c != '\r' && c != 8) // ��������� �� enter � �� backspace
			{
				if (fl != 2 && fl != 5)// ���� 3 ��� 5 ������� �� ������� �����
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
			int temp1 = (birthday[0] - 48) * 10 + (birthday[1] - 48);//������� �� char � �����
			int temp2 = (birthday[3] - 48) * 10 + (birthday[4] - 48);
			int temp3 = (birthday[6] - 48) * 1000 + (birthday[7] - 48) * 100 + (birthday[8] - 48) * 10 + (birthday[9] - 48);

			if ((temp1 > 31 || temp1 < 1) || (temp2 < 1 || temp2 > 12) || (temp3 > 2022 || temp3 < 1900)) // �������� �� ������������ ����
			{
				GoToXY(x, y + 1);
				cout << "���� ������� �������!";

				for (int i = 0; i < 15; i++) // ������� ���� �����
				{
					GoToXY(x + 15 + i, y);
					cout << " ";
				}

				birthday = "";
				fl = 0;
				c = '1';
			}
			else
				tempBool = false; // ��� ������ �� ��������� �����
		}

		else
		{
			GoToXY(x, y + 1);
			cout << "���� ������� �������!";

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
	cout << "����� ��������: ";
	int fl = 0;
	while (1)
	{
		cin >> number;
		 
		fl = 0;
		for (int i = 0; i < size(number); i++) // �������� �� �� ����
		{
			if (number[i] != '+' && ((int)number[i] < 48 || (int)number[i] > 57))
				fl++;
		}

		if (fl == 0 && size(number) == 13) // ����� ��������� ���� ������� �������
			break;
		else
		{
			GoToXY(x + 16, y);
			cout << "                     ";
			GoToXY(x, y + 1);
			cout << "����� ������ �������!";
			GoToXY(x + 16, y);
		}
	}
}