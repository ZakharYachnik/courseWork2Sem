#pragma once

#include "Account.h"

class Doctor : public Account
{
	private:
		string position;

	public:
		void registration() {}
		string getPosition();

		void setPosition(string position);
};