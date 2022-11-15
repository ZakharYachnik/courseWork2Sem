#pragma once
#include "Account.h"

class Patient : public Account
{
	private:
		string birthday;//дата рождения пользователя
		string gender;//пол пользователя
		string city;//город пользователя
		string number;//номер телефона пользователя
		string diagnosis;//диагноз пользователя
		
		
	public:
		string getBirthday();
		string getCity();
		string getNumber();
		string getGender();
		string getDiagmosis();

		
		void setBirthday(string birthday);
		void setCity(string city);
		void setNumber(string number);
		void setGender(string gender);
		void setDiagmosis(string diagnosis);

		void registration();

		void writeDate(int& x, int& y);
		void writeGender(int& x, int& y);
		void writeCity(int& x, int& y);
		void writeNumber(int& x, int& y);
};