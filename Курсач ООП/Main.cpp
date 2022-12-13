#include "Functions.h"

extern void readFileInformation();

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ConsoleCursorVisible(false, 100);
	readFileInformation();
	Menu::activeMenu();
}