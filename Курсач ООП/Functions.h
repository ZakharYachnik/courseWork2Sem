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

int getNumber();//���� ����� 


void GoToXY(short x, short y);//������������� ��������� �������
void ConsoleCursorVisible(bool show, short size);//������ ������� ���������

string writeLogin(int& x, int& y);

int authorization();
void activeMenu();//��������� ����
void menuForAdmin();// �������� ���� ������
//void enterForAdmin(int active);//���� ������� Enter ��� ���� ������
void menuForUser();//�������� ���� ��� ������������
//void enterForUser(int active);//���� ������� Enter � ���� ������������
//void menuForDoctor();
//void enterForDoctor(int active);
