/*

주문메뉴 목록 Class
주문메뉴와 관련된 데이터 넘버, 멤버 함수의 선언을 담고 있다.
Menu.h 참조하여 만듦(회의 후 합치는 방향성도 괜찮을듯)

*/

#pragma once
#include <string>
using namespace std;

class OrderMenu { // 주문메뉴
private:
	//멤버
	string name; // 메뉴 이름
	int price; //가격
	int count; //수량
public:
	//생성자
	OrderMenu(string name, int count);

	//멤버함수
	string getName() const;
	int getPrice() const;
	int getCount() const;
	void setCount(int newCount);
	void setPrice(int newPrice);
};