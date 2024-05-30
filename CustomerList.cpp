#include <iostream>
#include <fstream>
#include <sstream>
#include "CustomerList.h"

string trim(const string& str) { // file에 저장된 각 정보 슬라이싱
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos) {
        return ""; // 모든 문자가 공백인 경우
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

void CustomerList::loadFromFile(const string& filename) { // file 정보 읽어오기
	ifstream inFile(filename);
	if (!inFile.is_open()) {
		cerr << "File error : " << filename << endl;
		return;
	}

	string line;
	while (getline(inFile, line)) { // 각 정보 저장
        stringstream ss(line);
        string name, birth, phoneNum, address, request, paymentMethod;
        getline(ss, name, '/');
        getline(ss, birth, '/');
        getline(ss, phoneNum, '/');
        getline(ss, address, '/');
        getline(ss, request, '/');
        getline(ss, paymentMethod, '/');

        // 05.29 modified (회원 찾기, 출력 시 공백 포함 오류 수정)
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

void CustomerList::saveToFile(const string& filename) const{ // file에 저장
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

// 05.30 added (새로 입력한 주문자의 정보가 기존과 일치 시, 거부 Alg 추가)
void CustomerList::addCustomer(Customer& newCustomer) {
    string name = newCustomer.getName();
    string phoneNum = newCustomer.getPhoneNum();
    for (auto& customer : customers) {
        if (customer.getName() == name && customer.getPhoneNum() == phoneNum) {
            cout << endl << "이미 등록된 정보입니다!" << endl << endl;
            return;
        }
    }
    customers.push_back(newCustomer); // 중복 아닐 경우에만 추가
    cout << endl << "주문자 정보가 등록되었습니다." << endl << endl;
}

bool CustomerList::deleteCustomer(string& phoneNum) { // 주문자 정보 삭제
    for (auto it = customers.begin(); it != customers.end(); ++it)
        if (it->getPhoneNum() == phoneNum) {
            customers.erase(it); // customerList에서 삭제 작업
            return true;
        }
    return false;
}

// 주문자 정보 수정 (전화번호로 주문자 구분, 정보 수정 type = field, 새로운 정보)
bool CustomerList::updateCustomer(string& phoneNum, int field, string& newValue) { // 주문자 정보 수정
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

bool CustomerList::printCustomerInfo(string& phoneNum) { // 주문자 1명의 정보 출력
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

void CustomerList::printAllCustomers(const string& filename) { // 모든 주문자 정보 출력
    ifstream inFile(filename);

    // 등록된 주문자 정보가 없을 시 (file == isEmpty())
    if (inFile.peek() == ifstream::traits_type::eof()) {
        cout << "Error : 등록된 정보가 없습니다." << endl;
    }
    else {
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
}

void CustomerList::clearAllCustomers() { // 주문자 정보 모두 삭제
    customers.clear();
}