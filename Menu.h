#pragma once
#include <string>

using namespace std;

class Menu { // �޴�
private :
	string name; // �޴� �̸�
	int price; // �޴� ����
	string introduce; // �޴� �Ұ�

public :
	Menu(string name, int price, string introduce);
	string getName();
	int getPrice();
	string getIntroduce();
	void setName(string name);
	void setPrice(int price);
	void setIntroduce(string introduce);
};