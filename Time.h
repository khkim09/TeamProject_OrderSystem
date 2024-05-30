/*

시간 Time 구조체
날짜, 시간 정보를 담고 있다.

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

	// 생성자
	Time();

	// 멤버 함수
	void setTime();
	void printTime() const;
	void loadFromFile(ifstream& file);
	void saveToFile(ofstream& file) const;
};