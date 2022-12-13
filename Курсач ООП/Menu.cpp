#include "Functions.h"


void Menu::activeMenu()
{
	system("cls");
	pointOfAdmin = 0;
	pointOfPatient = 0;
	string firstMenu[] = { "�����������", "�����������", "�����" };
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
						cout << "�������� ����� ��� �����!";
					}
					flag++;
					j = authorization();
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
				patients.push_back(make_shared<Patient>((*new Patient())));
				patients[patients.size() - 1]->registration();
				pointOfPatient = patients.size() - 1; // ������� ������� ��������
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

void Menu::menuForAdmin()
{
	system("cls");
	string adminMenu[] = { "������� ������ ��������� �� �����", "���������� ������ ���������", "������� �������", "������� ���� ���������������",
						"����� ��������� �� ���������", "���������������� ������� ��������������","�������� ������", "������� ������ �������" };
	int active_menu = 0;

	char ch;
	while (true)
	{
		int x = 90, y = 20;
		GoToXY(x, y);

		for (int i = 0; i < size(adminMenu); i++)
		{
			if (i == active_menu)
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			else
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			GoToXY(x, y++);
			cout << adminMenu[i];
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
			if (active_menu < size(adminMenu) - 1)
				++active_menu;
			break;

		case ENTER:
			system("cls");
			enterForAdmin(active_menu);
			system("cls");
			break;

		case ESC:
			activeMenu();
		}
	}
}

void Menu::menuForUser()
{
	system("cls");
	string userMenu[] = { "������� ������ �� �����", "�������� ������", "������� �������", "���������� �� �����", "����������� ������ �� �����", "�����"};
	int active_menu = 0;

	char ch;
	while (true)
	{
		int x = 90, y = 20;
		GoToXY(x, y);

		for (int i = 0; i < size(userMenu); i++)
		{
			if (i == active_menu)
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			else
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			GoToXY(x, y++);
			cout << userMenu[i];
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
			if (active_menu < size(userMenu) - 1)
				++active_menu;
			break;

		case ENTER:
			system("cls");
			enterForUser(active_menu);
			system("cls");
			break;

		case ESC:
			activeMenu();
		}
	}
}

void Menu::enterForAdmin(int active)
{

}

void Menu::enterForUser(int active)
{
	switch (active)
	{
		case 0:
			patients[pointOfPatient - 1]->showInfAboutOnePatient();
			_getch();
			SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			break;
		
		case 1:
			patients[pointOfPatient - 1]->changePatientInf();
			_getch();
			break;

		case 2:
			patients[pointOfPatient - 1]->deleteAccount();
			_getch();
			activeMenu();
			break;

		case 3:
			patients[pointOfPatient - 1]->makeAppointment();
			system("cls");
			GoToXY(90, 20);
			cout << "�� �������� �� �����!";
			_getch();
			break;

		case 4:
			system("cls");
			patients[pointOfPatient - 1]->checkPatientAppointment();
			_getch();
			break;

		case 5:
			activeMenu();
			break;
	}
}