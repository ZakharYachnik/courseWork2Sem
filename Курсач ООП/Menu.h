#pragma once
class Menu
{
	public:
		static void activeMenu();//��������� ����
		static void menuForAdmin();// �������� ���� ������
		static void enterForAdmin(int active);//���� ������� Enter ��� ���� ������
		static void menuForUser();//�������� ���� ��� ������������
		static void enterForUser(int active);//���� ������� Enter � ���� ������������
};