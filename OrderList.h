/*

주문서 list 클래스
주문서들을 모아두고 주문 건수를 관리한다.

*/
#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "Menu.h"
#include "Order.h"
#include "Time.h"
#include "MenuList.h"
#include "CustomerList.h"


using namespace std;

class OrderList {
private:
	//멤버
	vector<Order> Orders; //주문서 목록

	//정적 멤버
	static int totalOrderCount; //총 주문 건수
	static int completeOrderCount;//완료된 주문 건수
	static int remainingOrderCount;//남은 주문 건수

public:
	//멤버 함수
	void read_Orderlist_file(const string& filename);	//Orderlist 파일 읽기
	void write_Orderlist_file(const string& filename);	//Orderlist 파일 쓰기

	bool new_order(MenuList& menulist, CustomerList& customerlist); //새로운 주문
	void change_order(int orderN, MenuList& menulist); //주문 메뉴 수량을 변경, 추가
	void delete_order(int orderN); //주문서 아예 삭제(!complete일때만 가능)
	void complete_order(int orderN); //주문 완료 알림 출력
	void print_order(int orderN); //주문서 출력
	void show_order_count(); //주문건수 관련 멤버 출력
	void show_remaining_order(); //남은 주문 건수 출력
};
