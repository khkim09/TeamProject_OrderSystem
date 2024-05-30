#pragma once
#include <string>
#include <fstream>

using namespace std;

class Customer {
private:
	string name; // �̸�
	string birth; // �������
	string phoneNum; // ��ȭ��ȣ
	string address; // �ּ�
	string request; // ��û����
	string payment_method; // ��������

public:
	Customer(string name, string birth, string phoneNum, string address, string request, string payment_method);
	
	string getName();
	string getBirth();
	string getPhoneNum();
	string getAddress();
	string getRequest();
	string getPaymentMethod();

	void setPhoneNum(string& phoneNum);
	void setAddress(string& address);
	void setRequest(string& request);
	void setPaymentMethod(string& payment_method);
	void saveToFile(ofstream& outFile) const;
};