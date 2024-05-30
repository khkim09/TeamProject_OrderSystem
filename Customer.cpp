#include <fstream>
#include "Customer.h"

Customer::Customer(string name, string birth, string phoneNum, string address, string request, string payment_method) {
	this->name = name;
	this->birth = birth;
	this->phoneNum = phoneNum;
	this->address = address;
	this->request = request;
	this->payment_method = payment_method;
}

string Customer::getName() { return this->name; }
string Customer::getBirth() { return this->birth; }
string Customer::getPhoneNum() { return this->phoneNum; }
string Customer::getAddress() { return this->address; }
string Customer::getRequest() { return this->request;}
string Customer::getPaymentMethod() { return this->payment_method; }

void Customer::setPhoneNum(string& newPhoneNum) { this->phoneNum = newPhoneNum; }
void Customer::setAddress(string& newAdress) { this->address = newAdress; }
void Customer::setRequest(string& newRequest) { this->request = newRequest; }
void Customer::setPaymentMethod(string& newPaymentMethod) { this->payment_method = newPaymentMethod; }

void Customer::saveToFile(ofstream& outFile) const{
	outFile << this->name << " / " << this->birth << " / " 
		<< this->phoneNum << " / " << this->address << " / "
		<< this->request << " / " << this->payment_method << "\n";
}