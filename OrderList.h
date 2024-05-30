/*

주문서 list 클래스
주문서들을 모아두고 주문 건수를 관리한다.

*/
#pragma once
#include <vector>
#include <string>
#include "Menu.h"
#include "Order.h"
#include "Time.h"
#include "MenuList.h"
#include "CustomerList.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

class OrderList { 
private:
	vector<Order> Orders;

	//정적 멤버
	static int totalOrderCount; //총 주문 건수
	static int completeOrderCount;//완료된 주문 건수
	static int remainingOrderCount;//남은 주문 건수

public:
	//Orderlist 파일 읽기
	void read_Orderlist_file(const string& filename);
	//Orderlist 파일 쓰기
	void write_Orderlist_file(const string& filename);

	void new_order(MenuList& menulist,CustomerList& customerlist); //새로운 주문. 새로운 주문 번호를 부여하여 Orders에 추가하고 주문메뉴 목록또한 입력받는다.
	void change_order(int orderN, MenuList& menulist); //주문 메뉴 수량을 변경하거나 추가한다.
	void delete_order(int orderN); //주문내역 아예 삭제(!complete일때만 가능)
	void complete_order(int orderN); //주문 완료 알림 출력
	void print_order(int orderN); //orderN번의 주문을 출력한다.
	void show_order_count(); //주문건수 관련 멤버 출력
	void show_remaining_order(); //남은 주문 건수 출력

};
