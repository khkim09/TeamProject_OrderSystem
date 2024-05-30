/*

주문 Order Class
주문과 관련된 데이터 넘버, 멤버 함수의 선언을 담고 있다.

*/
#pragma once
#include <iostream>
#include <vector>
#include "Time.h"
#include "OrderMenu.h"
#include "MenuList.h"
using namespace std;


class Order {
private:
	//멤버
	int order_number; //주문번호
	Time order_time;  //주문 시간

	vector<OrderMenu> order_items; //주문항목. 주문한 메뉴 및 수량

	int total; //주문 금액

	bool member;//멤버 여부
	//회원이면 5%할인
	bool discount;  //할인 여부
	//주문금액이 5만원 이상일 시/회원일 시 5% 추가 할인
	//회원이고 주문금액 허들 넘으면 10% 할인
	int receipt_total; //최종 결제 금액

	bool complete; //주문의 완료 여부
	Time complete_time; //주문 완료 시간

public:
	//생성자
	Order(int ordernumber);

	//멤버함수
	void Change_ordermenu(MenuList& menuList); //메뉴 목록 변경
	void Add_ordermenu(const string& name, int count, MenuList& menuList);// 메뉴 및 수량 추가
	void Add_ordermenu(string name, int count, int price);
	void delete_ordermenu(string name, int count); //메뉴 및 수량 삭제
	void Check_order() const; // 주문 내역 출력
	void Check_order_items() const; //주문 항목 출력
	void Complete_order(); // 주문 완료

	bool isComplete() const; // 주문 완료 여부 확인
	bool is_order_items_empty() const; //주문 항목 비어있는지 확인
	bool isMember() const; //회원 여부 확인


	//멤버 가져오기
	vector<OrderMenu>& getItems();
	int get_order_number() const;
	int get_total() const;
	int get_receipt_total() const;
	Time get_order_time() const;
	Time get_complete_time() const;

	//멤버 입력하기
	void set_total(int total);
	void set_receipt_total(int receiptTotal);
	void set_complete(bool complete);
	void set_order_time(Time& time);
	void set_complete_time(Time& time);
	void setMember(bool isMember);

private:
	void calculate_price(); //가격 계산
};