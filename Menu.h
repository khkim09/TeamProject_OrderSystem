#pragma once
#include <string>

using namespace std;

class Menu { // 메뉴
private :
	string name; // 메뉴 이름
	int price; // 메뉴 가격
	string introduce; // 메뉴 소개

public :
	Menu(string name, int price, string introduce);
	string getName();
	int getPrice();
	string getIntroduce();
	void setName(string name);
	void setPrice(int price);
	void setIntroduce(string introduce);
};