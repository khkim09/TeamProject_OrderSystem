#include <iostream>
#include <fstream>
#include <sstream>
#include "CustomerList.h"

string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos) {
        return ""; // ��� ���ڰ� ������ ���
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

        // �� �κ� ������
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

void CustomerList::printAllCustomers() {
    cout << "---------�ֹ��� ����----------" << endl;
    for (auto& customer : customers) {
        cout << "���� : " << customer.getName() << endl;
        cout << "������� : " << customer.getBirth() << endl;
        cout << "��ȭ��ȣ : " << customer.getPhoneNum() <<"."<< endl;
        cout << "�ּ� : " << customer.getAddress() << endl;
        cout << "��û���� : " << customer.getRequest() << endl;
        cout << "�������� : " << customer.getPaymentMethod() << endl;
        cout << "------------------------------" << endl;
    }
}

void CustomerList::addCustomer(Customer& customer) {
    customers.push_back(customer);
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
            cout << "���� : " << customer.getName() << endl;
            cout << "������� : " << customer.getBirth() << endl;
            cout << "��ȭ��ȣ : " << customer.getPhoneNum() << endl;
            cout << "�ּ� : " << customer.getAddress() << endl;
            cout << "��û���� : " << customer.getRequest() << endl;
            cout << "�������� : " << customer.getPaymentMethod() << endl;
            cout << "------------------------------" << endl;
            
            return true;
        }
    }
    return false;
}

void CustomerList::clearAllCustomers() {
    customers.clear();
}