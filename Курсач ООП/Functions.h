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
#include "Doctor.h"
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
extern vector<Doctor> doctors;
extern vector<Patient> patients;
extern vector<Administrator> admins;

int getNumber();//ввод числа 


void GoToXY(short x, short y);//устанавливает положение курсора
void ConsoleCursorVisible(bool show, short size);//делает курсоср невидимым

string writeLogin(int& x, int& y);

int authorization();
void activeMenu();//начальное меню
void menuForAdmin();// основное меню админа
//void enterForAdmin(int active);//учет клавиши Enter для меню админа
void menuForUser();//основное меню для пользователя
//void enterForUser(int active);//учет клавиши Enter в меню пользователя
//void menuForDoctor();
//void enterForDoctor(int active);
