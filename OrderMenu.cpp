/*

�ֹ��޴� ��� Class ���� ����Լ�
Menu.cpp �����Ͽ� ����(ȸ�� �� ��ġ�� ���⼺�� ��������)

*/

#include "OrderMenu.h"

//������
OrderMenu::OrderMenu(string name, int count):
	name(name),count(count),price(0){
//Menulist�� ���� price�� �߰�
}

//����Լ�
string OrderMenu::getName() const {
    return name;
}

int OrderMenu::getPrice() const {
    return price;
}

int OrderMenu::getCount() const {
    return count;
}

void OrderMenu::setCount(int newCount) {
    count = newCount;
}

void OrderMenu::setPrice(int newPrice) {
    price = newPrice;
}