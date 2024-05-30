#pragma once
#include <vector>
#include <string>
#include "Customer.h"

class CustomerList {
public:
	vector<Customer> customers;

	void loadFromFile(const string& filename);
	void saveToFile(const string& filename) const;
	
	void addCustomer(Customer& customer); // �ֹ��� ���� ���
	bool deleteCustomer(string& phoneNum); // �ֹ��� ���� ����
	bool updateCustomer(string& phoneNum, int field, string& newValue); // �ֹ��� ���� ������Ʈ
	bool printCustomerInfo(string& phoneNum);
	void printAllCustomers(const string& filename);
	void clearAllCustomers();
};