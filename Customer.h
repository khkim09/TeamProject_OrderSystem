#pragma once
#include <string>
#include <fstream>

using namespace std;

// ȸ�� Class ����
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
	
	string getName(); // ȸ�� �̸� ��ȯ
	string getBirth(); // ȸ�� ������� ��ȯ
	string getPhoneNum(); // ȸ�� ��ȭ��ȣ ��ȯ
	string getAddress(); // ȸ�� �ּ� ��ȯ
	string getRequest(); // ȸ�� ��û���� ��ȯ
	string getPaymentMethod(); // ȸ�� �������� ��ȯ

	void setPhoneNum(string& phoneNum); // ��ȭ��ȣ ������
	void setAddress(string& address); // �ּ� ������
	void setRequest(string& request); // ��û���� ������
	void setPaymentMethod(string& payment_method); // �������� ������
	void saveToFile(ofstream& outFile) const; // file�� ����
};