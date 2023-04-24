#pragma once

#include "Account.h"

using namespace std;

class Administrator : public Account
{
	public:
		Administrator(string FIO);
		Administrator();
		void registration();
		void deleteAccount();
		void changeAdminInf();
		void enterForChanges(int activeMenu);
		static void sortPatients();
		static void showAllPatients();
		static void writeAdminFile();
		static void outputListRecords();
		static void searchStructure();
		static void findFIO();
		static void findBirthday();
		static void findGender();
		static void findNumber();
		static void findCity();
		static void findDiagnosis();
		friend void readFileInformation();
		friend ostream& operator << (ostream& os, Administrator& other);
		friend istream& operator >> (istream& is, Administrator& other);
};

