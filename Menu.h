#pragma once
#include <string>

using namespace std;

class Menu { // �޴�
private:
	string name; // �޴� �̸�
	int price; // �޴� ����
	string introduce; // �޴� �Ұ�

public:
	Menu(string name, int price, string introduce); //������
	string getName(); // �޴� �̸� ��ȯ
	int getPrice(); // �޴� ���� ��ȯ
	string getIntroduce(); // �޴� �Ұ� ��ȯ
	void setName(string name); // �޴� �̸� �缳��
	void setPrice(int price); // �޴� ���� �缳��
	void setIntroduce(string introduce); // �޴� �Ұ� �缳��
};