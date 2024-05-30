#pragma once
#include <string>
#include <fstream>

using namespace std;

class Customer {
private:
	string name; // 이름
	string birth; // 생년월일
	string phoneNum; // 전화번호
	string address; // 주소
	string request; // 요청사항
	string payment_method; // 결제수단

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