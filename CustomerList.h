#pragma once
#include <vector>
#include <string>
#include "Customer.h"

// 회원(주문자) 정보 리스트 Class 정의
class CustomerList {
public:
	vector<Customer> customers; // 회원 정보 리스트

	void loadFromFile(const string& filename); // file 정보 읽어오기
	void saveToFile(const string& filename) const; // file에 저장
	
	void addCustomer(Customer& customer); // 주문자 정보 등록
	bool deleteCustomer(string& phoneNum); // 주문자 정보 삭제
	bool updateCustomer(string& phoneNum, int field, string& newValue); // 주문자 정보 업데이트
	bool printCustomerInfo(string& phoneNum); // 주문자 1명의 정보 출력
	void printAllCustomers(const string& filename); // 모든 주문자 정보 출력
	void clearAllCustomers(); // 주문자 정보 모두 삭제
};