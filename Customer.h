#pragma once
#include <string>
#include <fstream>

using namespace std;

// 회원 Class 정의
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
	
	string getName(); // 회원 이름 반환
	string getBirth(); // 회원 생년월일 반환
	string getPhoneNum(); // 회원 전화번호 반환
	string getAddress(); // 회원 주소 반환
	string getRequest(); // 회원 요청사항 반환
	string getPaymentMethod(); // 회원 결제수단 반환

	void setPhoneNum(string& phoneNum); // 전화번호 재정의
	void setAddress(string& address); // 주소 재정의
	void setRequest(string& request); // 요청사항 재정의
	void setPaymentMethod(string& payment_method); // 결제수단 재정의
	void saveToFile(ofstream& outFile) const; // file에 저장
};