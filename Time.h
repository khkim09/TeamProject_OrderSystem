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
	//시간
	int sec;
	int min;
	int hour;

	//날짜
	int day;
	int month;
	int year;

	// 생성자
	Time();

	// 멤버 함수
	void setTime(); //현재 시간 세팅
	void printTime() const; //시간 출력
	void loadFromFile(ifstream& file); //시간 읽기
	void saveToFile(ofstream& file) const; //시간 쓰기
};