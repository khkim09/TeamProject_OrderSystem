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
	int sec;
	int min;
	int hour;

	int day;
	int month;
	int year;

	// ������
	Time();

	// ��� �Լ�
	void setTime();
	void printTime() const;
	void loadFromFile(ifstream& file);
	void saveToFile(ofstream& file) const;
};