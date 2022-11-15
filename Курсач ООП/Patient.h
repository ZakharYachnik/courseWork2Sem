#pragma once
#include "Account.h"

class Patient : public Account
{
	private:
		string birthday;//���� �������� ������������
		string gender;//��� ������������
		string city;//����� ������������
		string number;//����� �������� ������������
		string diagnosis;//������� ������������
		
		
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