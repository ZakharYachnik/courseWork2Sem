#pragma once

#include "Functions.h"

using namespace std;

class Account
{
	protected:
		string login;//����� 
		string password;//������ �� �������� 
		string FIO;//��� 

	public:
		string getLogin();
		string getPassword();
		string getFIO();

		void setLogin(string login);
		void setPassword(string password);
		void setFIO(string FIO);

		virtual void registration() = 0;
		void viewDoctors();
		void encryption();//�������� ������
		void decryption();//����������� ������

		void writePassword(int& x, int& y);
		void writeFIO(int& x, int& y);

};