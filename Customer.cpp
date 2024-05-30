#include <fstream>
#include "Customer.h"

// ȸ��(�ֹ���) ������
Customer::Customer(string name, string birth, string phoneNum, string address, string request, string payment_method) {
	this->name = name;
	this->birth = birth;
	this->phoneNum = phoneNum;
	this->address = address;
	this->request = request;
	this->payment_method = payment_method;
}

string Customer::getName() { return this->name; } // ȸ�� �̸� ��ȯ
string Customer::getBirth() { return this->birth; } // ȸ�� ������� ��ȯ
string Customer::getPhoneNum() { return this->phoneNum; } // ȸ�� ��ȭ��ȣ ��ȯ
string Customer::getAddress() { return this->address; } // ȸ�� �ּ� ��ȯ
string Customer::getRequest() { return this->request;} // ȸ�� ��û���� ��ȯ
string Customer::getPaymentMethod() { return this->payment_method; } // ȸ�� �������� ��ȯ

void Customer::setPhoneNum(string& newPhoneNum) { this->phoneNum = newPhoneNum; } // ��ȭ��ȣ ������
void Customer::setAddress(string& newAdress) { this->address = newAdress; } // �ּ� ������
void Customer::setRequest(string& newRequest) { this->request = newRequest; } // ��û���� ������
void Customer::setPaymentMethod(string& newPaymentMethod) { this->payment_method = newPaymentMethod; } // �������� ������

// file�� ����
void Customer::saveToFile(ofstream& outFile) const{
	outFile << this->name << " / " << this->birth << " / " 
		<< this->phoneNum << " / " << this->address << " / "
		<< this->request << " / " << this->payment_method << "\n";
}