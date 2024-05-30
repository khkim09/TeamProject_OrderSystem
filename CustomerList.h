#pragma once
#include <vector>
#include <string>
#include "Customer.h"

class CustomerList {
public:
	vector<Customer> customers;

	void loadFromFile(const string& filename);
	void saveToFile(const string& filename) const;
	
	void addCustomer(Customer& customer); // 주문자 정보 등록
	bool deleteCustomer(string& phoneNum); // 주문자 정보 삭제
	bool updateCustomer(string& phoneNum, int field, string& newValue); // 주문자 정보 업데이트
	bool printCustomerInfo(string& phoneNum);
	void printAllCustomers(const string& filename);
	void clearAllCustomers();
};