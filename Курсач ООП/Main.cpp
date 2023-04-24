#include "Functions.h"

extern void readFileInformation();

int main()
{
	system("cls");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ConsoleCursorVisible(false, 100);
	system("cls");
	readFileInformation();
	Menu::activeMenu();
}