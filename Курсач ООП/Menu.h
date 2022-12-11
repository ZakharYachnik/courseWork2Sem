#pragma once
class Menu
{
	public:
		void activeMenu();//начальное меню
		void menuForAdmin();// основное меню админа
		void enterForAdmin(int active);//учет клавиши Enter для меню админа
		void menuForUser();//основное меню для пользователя
		void enterForUser(int active);//учет клавиши Enter в меню пользователя
};