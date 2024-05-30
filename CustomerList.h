#pragma once
#include <vector>
#include <string>
#include "Customer.h"

// ȸ��(�ֹ���) ���� ����Ʈ Class ����
class CustomerList {
public:
	vector<Customer> customers; // ȸ�� ���� ����Ʈ

	void loadFromFile(const string& filename); // file ���� �о����
	void saveToFile(const string& filename) const; // file�� ����
	
	void addCustomer(Customer& customer); // �ֹ��� ���� ���
	bool deleteCustomer(string& phoneNum); // �ֹ��� ���� ����
	bool updateCustomer(string& phoneNum, int field, string& newValue); // �ֹ��� ���� ������Ʈ
	bool printCustomerInfo(string& phoneNum); // �ֹ��� 1���� ���� ���
	void printAllCustomers(const string& filename); // ��� �ֹ��� ���� ���
	void clearAllCustomers(); // �ֹ��� ���� ��� ����
};