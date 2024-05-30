#pragma once
#include <string>

using namespace std;

class Menu { // 메뉴
private:
	string name; // 메뉴 이름
	int price; // 메뉴 가격
	string introduce; // 메뉴 소개

public:
	Menu(string name, int price, string introduce); //생성자
	string getName(); // 메뉴 이름 반환
	int getPrice(); // 메뉴 가격 반환
	string getIntroduce(); // 메뉴 소개 반환
	void setName(string name); // 메뉴 이름 재설정
	void setPrice(int price); // 메뉴 가격 재설정
	void setIntroduce(string introduce); // 메뉴 소개 재설정
};