#include <fstream>
#include "Customer.h"

// 회원(주문자) 생성자
Customer::Customer(string name, string birth, string phoneNum, string address, string request, string payment_method) {
	this->name = name;
	this->birth = birth;
	this->phoneNum = phoneNum;
	this->address = address;
	this->request = request;
	this->payment_method = payment_method;
}

string Customer::getName() { return this->name; } // 회원 이름 반환
string Customer::getBirth() { return this->birth; } // 회원 생년월일 반환
string Customer::getPhoneNum() { return this->phoneNum; } // 회원 전화번호 반환
string Customer::getAddress() { return this->address; } // 회원 주소 반환
string Customer::getRequest() { return this->request;} // 회원 요청사항 반환
string Customer::getPaymentMethod() { return this->payment_method; } // 회원 결제수단 반환

void Customer::setPhoneNum(string& newPhoneNum) { this->phoneNum = newPhoneNum; } // 전화번호 재정의
void Customer::setAddress(string& newAdress) { this->address = newAdress; } // 주소 재정의
void Customer::setRequest(string& newRequest) { this->request = newRequest; } // 요청사항 재정의
void Customer::setPaymentMethod(string& newPaymentMethod) { this->payment_method = newPaymentMethod; } // 결제수단 재정의

// file에 저장
void Customer::saveToFile(ofstream& outFile) const{
	outFile << this->name << " / " << this->birth << " / " 
		<< this->phoneNum << " / " << this->address << " / "
		<< this->request << " / " << this->payment_method << "\n";
}