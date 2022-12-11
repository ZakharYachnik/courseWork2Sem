#pragma once

#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <ctime>
#include <string>
#include <Windows.h>
#include <iomanip>
#include <string.h>
#include <fstream>
#include <vector>
#include <memory>
#include "Menu.h"
#include "Patient.h"
#include "Administrator.h"

using namespace std;

const char UP = 72;
const char DOWN = 80;
const char ESC = 27;
const char ENTER = 13;

extern int pointOfUs;
extern int  pointOfAdmin;

extern fstream Inform;
extern vector<shared_ptr<Patient>> patients;
extern vector<shared_ptr<Administrator>> admins;
extern HANDLE hStdOut;

int getNumber();//ввод числа 


void GoToXY(short x, short y);//устанавливает положение курсора
void ConsoleCursorVisible(bool show, short size);//делает курсоср невидимым

string writeLogin(int& x, int& y);

int authorization();
