/*

�ֹ��޴� ��� Class
�ֹ��޴��� ���õ� ������ �ѹ�, ��� �Լ��� ������ ��� �ִ�.
Menu.h �����Ͽ� ����(ȸ�� �� ��ġ�� ���⼺�� ��������)

*/

#pragma once
#include <string>
using namespace std;

class OrderMenu { // �ֹ��޴�
private:
	//���
	string name; // �޴� �̸�
	int price; //����
	int count; //����
public:
	//������
	OrderMenu(string name, int count);

	//����Լ�
	string getName() const;
	int getPrice() const;
	int getCount() const;
	void setCount(int newCount);
	void setPrice(int newPrice);
};