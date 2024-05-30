/*

주문메뉴 목록 Class 관련 멤버함수
Menu.cpp 참조하여 만듦(회의 후 합치는 방향성도 괜찮을듯)

*/

#include "OrderMenu.h"

//생성자
OrderMenu::OrderMenu(string name, int count):
	name(name),count(count),price(0){
//Menulist를 통해 price를 추가
}

//멤버함수
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