#include "Menu.h"
#include <iostream>

//������
Menu::Menu(string name, int price, string introduce) {
	this->name = name;
	this->price = price;
	this->introduce = introduce;
}

string Menu::getName() {
	return this->name;
}

int Menu::getPrice() {
	return this->price;
}

string Menu::getIntroduce() {
	return this->introduce;
}

// �޴� �̸� �缳��
void Menu::setName(string name) {
	this->name = name;
}

// �޴� ���� �缳��
void Menu::setPrice(int price) {
	this->price = price;
}

// �޴� �Ұ� �缳��
void Menu::setIntroduce(string introduce) {
	this->introduce = introduce;
}