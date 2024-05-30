/*

�ֹ��� list Ŭ���� ���� ����Լ�
�ֹ������� ��Ƶΰ� �ֹ� �Ǽ��� �����Ѵ�.

*/
#include "OrderList.h"
#include <iostream>
#include <sstream>


// ���� ��� �ʱ�ȭ
int OrderList::totalOrderCount = 0;
int OrderList::completeOrderCount = 0;
int OrderList::remainingOrderCount = 0;


// OrderList ���� �б�
void OrderList::read_Orderlist_file(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open the file: " << filename << endl;
        return;
    }

    Orders.clear();

    // ������ �� ó���� �ֹ� �Ǽ����� �о����
    file >> totalOrderCount >> completeOrderCount >> remainingOrderCount;
    file.ignore(numeric_limits<streamsize>::max(), '\n');  // �� ������ ����

    int orderNumber, total, receiptTotal, complete, member;
    while (file >> orderNumber >> total >> receiptTotal >> complete >> member) {
        file.ignore(); // �� ���� ���� ���� ����
        Order order(orderNumber);
        order.set_total(total);
        order.set_receipt_total(receiptTotal);
        order.set_complete(complete);
        order.setMember(member);

        Time orderTime;
        orderTime.loadFromFile(file);
        order.set_order_time(orderTime);

        Time completeTime;
        completeTime.loadFromFile(file);
        order.set_complete_time(completeTime);

        string line;
        while (getline(file, line)) {
            if (line == "END_OF_ORDER") break;

            size_t first_quote = line.find('\"');
            size_t second_quote = line.find('\"', first_quote + 1);

            string name = line.substr(first_quote + 1, second_quote - first_quote - 1);
            istringstream iss(line.substr(second_quote + 1));
            int count, price;
            iss >> count >> price;
            order.Add_ordermenu(name, count, price);
        }
        Orders.push_back(order);
    }
    file.close();
}

// OrderList ���� ����
void OrderList::write_Orderlist_file(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open the file: " << filename << endl;
        return;
    }

    // ������ �� ó���� �ֹ� �Ǽ����� ���
    file << totalOrderCount << " " << completeOrderCount << " " << remainingOrderCount << endl;

    for (auto& order : Orders) {
        file << order.get_order_number() << " "
            << order.get_total() << " "
            << order.get_receipt_total() << " "
            << order.isComplete() << " "
            << order.isMember() << endl;

        order.get_order_time().saveToFile(file);
        order.get_complete_time().saveToFile(file);

        for (auto& item : order.getItems()) {
            file << "\"" << item.getName() << "\" " // �������� ����ǥ �߰�
                << item.getCount() << " "
                << item.getPrice() << endl;
        }
        file << "END_OF_ORDER" << endl;
    }
    file.close();
}


// ���ο� �ֹ� �߰�
bool OrderList::new_order(MenuList& menulist,CustomerList& customerlist) {
    Order newOrder(totalOrderCount+1);

    int choice;
    bool answer = false;

    while (true) {
        cout << "ȸ���̽ʴϱ�?" << endl;
        cout << "1. ��" << endl;
        cout << "2. �ƴϿ�" << endl;

        cin >> choice;
        cin.ignore();
        cout << endl;

        if (choice == 1) {
            cout << "ȸ�� ��ȸ�� ���� ��ȭ��ȣ�� �Է����ֽʽÿ� (010-XXXX-XXXX) : ";
            string phone_number;

            getline(cin, phone_number);

            for (auto& customer : customerlist.customers) {
                cout << phone_number << " ��ȸ��.." << endl << endl;
                if (customer.getPhoneNum() == phone_number) {
                    newOrder.setMember(true);
                    cout << "'" << customer.getName() << "'�� Ȯ�εǾ����ϴ�!" << endl;
                    break;
                }
            }

            if (!newOrder.isMember()) {
                cout << "ȸ�� ������ �������� �ʽ��ϴ�." << endl;
            }
            break;
        }
        else if (choice == 2) { // ȸ�� ���� ��� ����
            char ans;
            cout << "ȸ�� ����� �����Ͻðڽ��ϱ�? (y/n) : ";
            cin >> ans; // ��� ���� (ans)
            cin.ignore();
            cout << endl;

            if (ans == 'y') {
                answer = true; // main���� ��ȯ�� bool�� (answer)
                cout << "�ֹ��� �����Ͻø� ȸ�� ��� ȭ������ �Ѿ�ϴ�." << endl;
            }
            break;
        }
        else {
            cout << "�߸��� �Է��Դϴ�." << endl;
        }
    }

    newOrder.Change_ordermenu(menulist);

    if (newOrder.is_order_items_empty()) {
        cout << "�ֹ� �׸��� ��� �����Ƿ� �ֹ��� �߰����� �ʽ��ϴ�." << endl;
        return false;
    }
    
    Orders.push_back(newOrder);
    totalOrderCount++;
    remainingOrderCount++;
    cout << totalOrderCount << "�� �ֹ��� �߰��Ǿ����ϴ�!"<< endl;
    return answer;
}

// �ֹ� ����
void OrderList::change_order(int orderN, MenuList& menulist) {
    for (auto it = Orders.begin(); it != Orders.end(); ++it) {
        if (it->get_order_number() == orderN) {
            if (!it->isComplete()) {
                it->Change_ordermenu(menulist);

                if (it->is_order_items_empty()) {
                    cout << "�ֹ� �׸��� ��������Ƿ� �ֹ��� �����˴ϴ�." << endl;
                    Orders.erase(it);
                }
            }
            else {
                cout << "�̹� �Ϸ�� �ֹ��Դϴ�." << endl;
            }
            return;
        }
    }
    cout << "�������� �ʴ� �ֹ���ȣ�Դϴ�." << endl;

}

// �ֹ� ����
void OrderList::delete_order(int orderN) {
    for (auto it = Orders.begin(); it != Orders.end(); ++it) {
        if (it->get_order_number() == orderN) {
            if (!it->isComplete()) {
                Orders.erase(it);
                remainingOrderCount--;
                cout << orderN << "�� �ֹ��� ��ҵǾ����ϴ�." << endl;
            }
            else {
                cout << "�Ϸ�� �ֹ��Դϴ�." << endl;
            }
            return;
        }
    }
    cout << "�������� �ʴ� �ֹ���ȣ�Դϴ�." << endl;
}


// �ֹ� �Ϸ�
void OrderList::complete_order(int orderN) {
    for (auto& order : Orders) {
        if (order.get_order_number() == orderN) {
            if (!order.isComplete()) {
                order.Complete_order();
                completeOrderCount++;
                remainingOrderCount--;
                cout << orderN << "�� �ֹ��� �Ϸ�Ǿ����ϴ�." << endl;
            }
            else {
                cout << "�̹� �Ϸ�� �ֹ��Դϴ�." << endl;
            }
            return;
        }
    }
    cout << "�������� �ʴ� �ֹ���ȣ�Դϴ�." << endl;
}


// �ֹ� ���
void OrderList::print_order(int orderN) {
    if (totalOrderCount == 0) {
        cout << "�ֹ������� ���� �������� �ʽ��ϴ�." << endl;
        return;
    }
    for (auto& order : Orders) {
        if (order.get_order_number() == orderN) {
            order.Check_order();
            return;
        }
    }
    cout << "�������� �ʴ� �ֹ���ȣ�Դϴ�." << endl;
}

// �ֹ� �Ǽ� ���
void OrderList::show_order_count() {
    cout << "�� �ֹ� ��: " << totalOrderCount <<"��"<< endl;
    cout << "�Ϸ�� �ֹ� ��: " << completeOrderCount <<"��"<< endl;
    cout << "���� �ֹ� ��: " << remainingOrderCount <<"��"<< endl;
}

// ���� �ֹ� �Ǽ� ���
void OrderList::show_remaining_order() {
    cout << "���� �ֹ� ��: " << remainingOrderCount << "��" << endl;
}