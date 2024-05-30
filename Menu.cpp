#include "Menu.h"
#include <iostream>

//생성자
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

// 메뉴 이름 재설정
void Menu::setName(string name) {
	this->name = name;
}

// 메뉴 가격 재설정
void Menu::setPrice(int price) {
	this->price = price;
}

// 메뉴 소개 재설정
void Menu::setIntroduce(string introduce) {
	this->introduce = introduce;
}