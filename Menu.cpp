#include "Menu.h"
#include <iostream>

//생성자
Menu::Menu(string name, int price, string introduce) {
	this->name = name;
	this->price = price;
	this->introduce = introduce;
}

// 메뉴 이름 반환
string Menu::getName() {
	return this->name;
}

// 메뉴 가격 반환
int Menu::getPrice() {
	return this->price;
}

// 메뉴 가격 반환
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