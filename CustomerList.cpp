#include <iostream>
#include <fstream>
#include <sstream>
#include "CustomerList.h"

string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos) {
        return ""; // 모든 문자가 공백인 경우
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

void CustomerList::loadFromFile(const string& filename) {
	ifstream inFile(filename);
	if (!inFile.is_open()) {
		cerr << "File error : " << filename << endl;
		return;
	}

	string line;
	while (getline(inFile, line)) {
        stringstream ss(line);
        string name, birth, phoneNum, address, request, paymentMethod;
        getline(ss, name, '/');
        getline(ss, birth, '/');
        getline(ss, phoneNum, '/');
        getline(ss, address, '/');
        getline(ss, request, '/');
        getline(ss, paymentMethod, '/');

        // 05.29 modified
        name = trim(name);
        birth = trim(birth);
        phoneNum = trim(phoneNum);
        address = trim(address);
        request = trim(request);
        paymentMethod = trim(paymentMethod);

        customers.push_back(Customer(name, birth, phoneNum, address, request, paymentMethod));
    }

    inFile.close();
}

void CustomerList::saveToFile(const string& filename) const{
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Error opening file : " << filename << endl;
        return;
    }
    for (auto& customer : customers) {
        customer.saveToFile(outFile);
    }
    outFile.close();
}

// 05.30 added
void CustomerList::addCustomer(Customer& newCustomer) {
    string name = newCustomer.getName();
    string phoneNum = newCustomer.getPhoneNum();
    for (auto& customer : customers) {
        if (customer.getName() == name && customer.getPhoneNum() == phoneNum) {
            cout << endl << "이미 등록된 정보입니다!" << endl << endl;
            return;
        }
    }
    customers.push_back(newCustomer);
    cout << endl << "주문자 정보가 등록되었습니다." << endl << endl;
}

bool CustomerList::deleteCustomer(string& phoneNum) {
    for (auto it = customers.begin(); it != customers.end(); ++it)
        if (it->getPhoneNum() == phoneNum) {
            customers.erase(it);
            return true;
        }
    return false;
}

bool CustomerList::updateCustomer(string& phoneNum, int field, string& newValue) {
    for (auto& customer : customers) {
        if (customer.getPhoneNum() == phoneNum) {
            switch (field) {
            case 1:
                customer.setPhoneNum(newValue); break;
            case 2:
                customer.setAddress(newValue); break;
            case 3:
                customer.setRequest(newValue); break;
            case 4:
                customer.setPaymentMethod(newValue); break;
            default:
                return false;
            }
            return true;
        }
    }
    return false;
}

bool CustomerList::printCustomerInfo(string& phoneNum) {
    for (auto& customer : customers) {
        if (customer.getPhoneNum() == phoneNum) {
            cout << "성함 : " << customer.getName() << endl;
            cout << "생년월일 : " << customer.getBirth() << endl;
            cout << "전화번호 : " << customer.getPhoneNum() << endl;
            cout << "주소 : " << customer.getAddress() << endl;
            cout << "요청사항 : " << customer.getRequest() << endl;
            cout << "결제수단 : " << customer.getPaymentMethod() << endl;
            cout << "------------------------------" << endl;
            
            return true;
        }
    }
    return false;
}

void CustomerList::printAllCustomers() {
    cout << "---------주문자 정보----------" << endl;
    for (auto& customer : customers) {
        cout << "성함 : " << customer.getName() << endl;
        cout << "생년월일 : " << customer.getBirth() << endl;
        cout << "전화번호 : " << customer.getPhoneNum() << endl; // 05.30 modified
        cout << "주소 : " << customer.getAddress() << endl;
        cout << "요청사항 : " << customer.getRequest() << endl;
        cout << "결제수단 : " << customer.getPaymentMethod() << endl;
        cout << "------------------------------" << endl;
    }
}

void CustomerList::clearAllCustomers() {
    customers.clear();
}