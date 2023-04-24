#pragma warning(disable : 4996)

#include "Functions.h"
#include <ctime>

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

string Patient::getDiagnosis()
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

void Patient::showInfAboutOnePatient()
{
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	GoToXY(20, 20);
	cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------";
	GoToXY(20, 21);
	cout << "|               ���                |      ���� ��������      |         ���           |           �����           |        ����� ��������       |        �������       |";
	GoToXY(20, 22);
	cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------";
	GoToXY(20, 23);
	cout << "| " << setw(32) << FIO << " | " << setw(22) << birthday << setw(4) << " | " << setw(20) << this->getGender() << setw(4) << " | " << setw(24)
		<< this->getCity() << setw(4) << " | " << setw(26) << this->getNumber() << setw(4) << " | " << setw(18) << this->getDiagnosis() << setw(4) << " |";
	GoToXY(20, 24);
	cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------";

}

void Patient::changePatientInf()
{
	GoToXY(90, 18);
	cout << "��� �� ������ ��������?";
	int activeMenu = 0;
	string changes[] = { "�����", "������", "���", "���� ��������", "���", "�����", "����� ��������", "�������" };
	char ch;

	while (true)
	{
		int x = 90, y = 20;
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
			system("cls");
			GoToXY(90,20);
			cout << "��������� ���������!";
			return;
			break;
		
		case ESC:
			return;
		}
	}
}

void Patient::enterForChanges(int activeMenu)
{
	int x = 90, y = 20;

	switch (activeMenu)
	{
	case 0:
	{
		string tempLogin = writeLogin(x, y);
		this->setLogin(tempLogin); 
		writePatientFile();
		break;
	}

	case 1: {
		this->writePassword(x, y);
		writePatientFile();
		break;
	}
	case 2:
	{
		this->writeFIO(x, y);
		writePatientFile();
		break;
	}

	case 3:
	{
		this->writeDate(x, y);
		writePatientFile();
		break;
	}

	case 4:
	{
		this->writeGender(x, y);
		writePatientFile();
		break;
	}

	case 5:
	{
		this->writeGender(x, y);
		writePatientFile();
		break;
	}

	case 6:
	{
		this->writeNumber(x, y);
		writePatientFile();
		break;
	}
	case 7:
	{
		GoToXY(90, 20);
		string tempDiagnosis;
		cout << "������� �������: ";
		cin >> tempDiagnosis;
		this->setDiagmosis(tempDiagnosis);
		writePatientFile();
		break;
	}
	}
}

void Patient::readPatients()
{
	try
	{
		Inform.open("InformationPatients.txt");

		Inform.seekg(0, ios_base::end);
		if (Inform.tellg() == 0)
		{
			Inform.close();
			return;
		}
		Inform.seekg(0, ios_base::beg);
		patients.clear();
		while (!Inform.eof())
		{
			Patient tempPatient;
			getline(Inform, tempPatient.login);
			getline(Inform, tempPatient.password);
			tempPatient.decryption();
			getline(Inform, tempPatient.FIO);
			getline(Inform, tempPatient.birthday);
			getline(Inform, tempPatient.gender);
			getline(Inform, tempPatient.city);
			getline(Inform, tempPatient.number);
			getline(Inform, tempPatient.diagnosis);

			patients.push_back(make_shared<Patient>(tempPatient));
		}
	}
	catch (const exception& ex)
	{
		GoToXY(90, 12);
		cout << ex.what();
		GoToXY(90, 13);
		cout << "������ �������� �����!!!";
	}

	Inform.close();
}

void Patient::writePatientFile()
{
	try
	{
		Inform.open("InformationPatients.txt", ios_base::out);
		for(auto i : patients)
		{
			if (Inform.tellg() != 0) // �������� �� ������� �����
				Inform << '\n';
			Inform << i->login;
			Inform << '\n';
			i->encryption();
			Inform << i->password;
			i->decryption();
			Inform << '\n' << i->FIO << '\n';
			Inform << i->birthday << '\n';
			Inform << i->gender << '\n';
			Inform << i->city << '\n';
			Inform << i->number << '\n';
			Inform << i->diagnosis;
		}

		Inform.close();
	}
	catch (const exception& ex)
	{
		GoToXY(90, 12);
		cout << ex.what();
		GoToXY(90, 13);
		cout << "������ �������� �����!!!";
	}
}

void Patient::deleteAccount()
{
	char ch = 0;
	int tempInt = 0;
	GoToXY(90, 20);
	cout << "�� �������, ��� ������ ������� �������?";
	while (tempInt != 3)
	{
		if (tempInt == 0)
			SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		else
			SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
		GoToXY(90, 22);
		cout << "��";

		if (tempInt == 1)
			SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		else
			SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
		GoToXY(90, 23);
		cout << "���";

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
				Menu::menuForUser();
			else
				tempInt = 3;
			break;
		}
	}

	patients.erase(patients.begin() + pointOfPatient - 1);
	writePatientFile();
	system("cls");
	GoToXY(90, 20);
	cout << "������� ������� ������!";
}

void Patient::makeAppointment()
{
	string doctor = doctorChoice();
	system("cls");
	string curTime = timeNow();
	string appointmentTime = choiceTime();

	fstream report;
	fstream allReports;
	fstream patientReports;

	try
	{	
		report.open("report.txt", ios_base::out);
		report << "     !!!������ � ����� " << doctor << "�!!!" << endl;
		report << "����� ������ � �����: " << appointmentTime << ";" << endl;
		report << "��� ��������: " << this->getFIO() << ";" << endl;
		report << "�����: " << this->getCity() << ";" << endl;
		report << "����� �������� ��������: " << this->getNumber() << ";" << endl;
		report << "                     " << curTime << "." << endl;

		allReports.open("allReports.txt", ios_base::app);
		allReports << "     !!!������ � ����� " << doctor << "�!!!" << endl;
		allReports << "����� ������ � �����: " << appointmentTime << ";" << endl;
		allReports << "��� ��������: " << this->getFIO() << ";" << endl;
		allReports << "�����: " << this->getCity() << ";" << endl;
		allReports << "����� �������� ��������: " << this->getNumber() << ";" << endl;
		allReports << "                     " << curTime << "." << endl << endl;

		patientReports.open(this->getLogin() + "Reports.txt", ios_base::app);
		patientReports << "     !!!������ � ����� " << doctor << "�!!!" << endl;
		patientReports << "����� ������ � �����: " << appointmentTime << ";" << endl;
		patientReports << "��� ��������: " << this->getFIO() << ";" << endl;
		patientReports << "�����: " << this->getCity() << ";" << endl;
		patientReports << "����� �������� ��������: " << this->getNumber() << ";" << endl;
		patientReports << "                     " << curTime << "." << endl << endl;

		report.close();
		allReports.close();
		patientReports.close();
	}
	catch (const exception& ex)
	{
		GoToXY(90, 12);
		cout << ex.what();
		GoToXY(90, 13);
		cout << "������ �������� �����!!!";
	}

	system("notepad C:\\Users\\user\\Desktop\\������ 2\\������ ���\\������ ���\\report.txt");
}

string Patient::doctorChoice()
{
	system("cls");
	GoToXY(90, 18);
	cout << "�������� � ������ ����� ��� ����";

	string doctorsMenu[] = {"��������", "������", "�������", "�����������", "����������", "����������", "������"};
	int active_menu = 0;
	char ch;
	while (true)
	{
		int x = 90, y = 20;
		GoToXY(x, y);

		for (int i = 0; i < size(doctorsMenu); i++)
		{
			if (i == active_menu)
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			else
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			GoToXY(x, y++);
			cout << doctorsMenu[i];
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
			if (active_menu < size(doctorsMenu) - 1)
				++active_menu;
			break;

		case ENTER:
			return doctorsMenu[active_menu];
			break;

		case ESC:
			Menu::menuForUser();
		}
	}
}

string Patient::timeNow()
{
	time_t now = time(0);
	tm* ltm = localtime(&now);
	
	return to_string(ltm->tm_hour) + ':' + to_string(ltm->tm_min) + ':' + to_string(ltm->tm_sec) + " " + to_string(ltm->tm_mday) + '.' + to_string(1 + ltm->tm_mon)  + '.' + to_string(1900 + ltm->tm_year);
}

string Patient::choiceTime()
{
	system("cls");
	GoToXY(90, 18);
	cout << "�������� ���������� ��� �����";
	time_t now = time(0);
	tm* ltm = localtime(&now);

	string timeMenu[4];
	timeMenu[0] = "18:00 " + to_string(ltm->tm_mday + 1) + "." + to_string(1 + ltm->tm_mon) + "." + to_string(1900 + ltm->tm_year);
	timeMenu[1] = "17:30 " + to_string(ltm->tm_mday + 2) + "." + to_string(1 + ltm->tm_mon) + "." + to_string(1900 + ltm->tm_year);
	timeMenu[2] = "14:20 " + to_string(ltm->tm_mday + 3) + "." + to_string(1 + ltm->tm_mon) + "." + to_string(1900 + ltm->tm_year);
	timeMenu[3] = "19:00 " + to_string(ltm->tm_mday + 3) + "." + to_string(1 + ltm->tm_mon) + "." + to_string(1900 + ltm->tm_year);

	int active_menu = 0;
	char ch;
	while (true)
	{
		int x = 90, y = 20;
		GoToXY(x, y);

		for (int i = 0; i < size(timeMenu); i++)
		{
			if (i == active_menu)
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			else
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			GoToXY(x, y++);
			cout << timeMenu[i];
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
			if (active_menu < size(timeMenu) - 1)
				++active_menu;
			break;

		case ENTER:
			return timeMenu[active_menu];
			break;

		case ESC:
			Menu::menuForUser();
		}
	}
}

void Patient::checkPatientAppointment()
{
	fstream patientReports;
	string tempStr;
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	try
	{
		patientReports.open(this->getLogin() + "Reports.txt", ios_base::in);
		
		int x = 5, y = 10;
		int i = 0;
		int flagOnOutput = 0;
		while (patientReports.tellg() != EOF)
		{
			if (i == 7)
			{	
				i = 0;
				x += 50;
				y = 10;
				if (++flagOnOutput == 4)
				{
					x = 5;
					y = 20;
				}
			}
			GoToXY(x, ++y);
			getline(patientReports, tempStr);
			cout << tempStr;
			i++;
		}
		patientReports.close();
	}
	catch (const exception& ex)
	{
		GoToXY(90, 12);
		cout << ex.what();
		GoToXY(90, 13);
		cout << "������ �������� �����!!!";
	}

	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
}

void readFileInformation()
{
	try
	{
		Inform.open("InformationPatients.txt");

		Inform.seekg(0, ios_base::end);
		if (Inform.tellg() == 0)
		{
			Inform.close();
			return;
		}
		Inform.seekg(0, ios_base::beg);
		while (!Inform.eof())
		{
			Patient tempPatient;
			getline(Inform, tempPatient.login);
			getline(Inform, tempPatient.password);
			tempPatient.decryption();
			getline(Inform, tempPatient.FIO);
			getline(Inform, tempPatient.birthday);
			getline(Inform, tempPatient.gender);
			getline(Inform, tempPatient.city);
			getline(Inform, tempPatient.number);
			getline(Inform, tempPatient.diagnosis);

			patients.push_back(make_shared<Patient>(tempPatient));
		}
	}
	catch (const exception& ex)
	{
		GoToXY(90, 12);
		cout << ex.what();
		GoToXY(90, 13);
		cout << "������ �������� �����!!!";
	}

	Inform.close();

	try
	{
		Inform.open("InformationAdmins.txt");

		Inform.seekg(0, ios_base::end);
		if (Inform.tellg() == 0)
		{
			Inform.close();
			return;
		}
		Inform.seekg(0, ios_base::beg);

		while (!Inform.eof())
		{
			Administrator tempAdmin;
			getline(Inform, tempAdmin.login);
			getline(Inform, tempAdmin.password);
			tempAdmin.decryption();
			getline(Inform, tempAdmin.FIO);

			admins.push_back(make_shared<Administrator>(tempAdmin));
		}
	}
	catch (const exception& ex)
	{
		GoToXY(90, 12);
		cout << ex.what();
		GoToXY(90, 13);
		cout << "������ �������� �����!!!";
	}

	Inform.close();
}

ostream& operator<<(ostream& os, Administrator& other)
{
	GoToXY(90,30);
	os << other.FIO << endl << other.login;
	return os;
}

istream& operator>>(istream& is, Administrator& other)
{
	is >> other.FIO;
	is >> other.login;
	is >> other.password;

	return is;
}
