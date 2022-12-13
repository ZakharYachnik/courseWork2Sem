#pragma once
class Menu
{
	public:
		static void activeMenu();//начальное меню
		static void menuForAdmin();// основное меню админа
		static void enterForAdmin(int active);//учет клавиши Enter для меню админа
		static void menuForUser();//основное меню для пользователя
		static void enterForUser(int active);//учет клавиши Enter в меню пользователя
};