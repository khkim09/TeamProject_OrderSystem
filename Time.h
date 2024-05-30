/*

�ð� Time ����ü
��¥, �ð� ������ ��� �ִ�.

*/
#pragma once
#include <ctime>
#include <fstream>
#include <iostream>
using namespace std;

struct Time {
	//�ð�
	int sec;
	int min;
	int hour;

	//��¥
	int day;
	int month;
	int year;

	// ������
	Time();

	// ��� �Լ�
	void setTime(); //���� �ð� ����
	void printTime() const; //�ð� ���
	void loadFromFile(ifstream& file); //�ð� �б�
	void saveToFile(ofstream& file) const; //�ð� ����
};