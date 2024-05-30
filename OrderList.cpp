/*

�ֹ��� list Ŭ���� ���� ����Լ�
�ֹ������� ��Ƶΰ� �ֹ� �Ǽ��� �����Ѵ�.

*/
#include "OrderList.h"
#include <iostream>


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
    totalOrderCount = 0;
    completeOrderCount = 0;
    remainingOrderCount = 0;

    int orderNumber, total, receiptTotal, complete,member;
    string name;
    int count, price;
    while (file >> orderNumber >> total >> receiptTotal >> complete>>member) {
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

        while (file >> name >> count >> price) {
            if (name == "END_OF_ORDER") break;
            order.Add_ordermenu(name, count, price);
        }
        Orders.push_back(order);
        totalOrderCount++;
        if (complete) {
            completeOrderCount++;
        }
        else {
            remainingOrderCount++;
        }
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

    for (auto& order : Orders) {
        file << order.get_order_number() << " "
            << order.get_total() << " "
            << order.get_receipt_total() << " "
            << order.isComplete() << " "
            << order.isMember() << endl;

        

        order.get_order_time().saveToFile(file);
        order.get_complete_time().saveToFile(file);

        for (auto& item : order.getItems()) {
            file << item.getName() << " "
                << item.getCount() << " "
                << item.getPrice() << endl;
        }
        file << "END_OF_ORDER" << endl;
    }
    file.close();
}


// ���ο� �ֹ� �߰�
void OrderList::new_order(MenuList& menulist,CustomerList& customerlist) {
    Order newOrder(totalOrderCount+1);

    int choice;

    while (true) {
        cout << "ȸ���̽ʴϱ�?" << endl;
        cout << "1.��" << endl;
        cout << "2.�ƴϿ�" << endl;

        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "ȸ�� ��ȸ�� ���� ��ȭ��ȣ�� �Է����ֽʽÿ�.(010-XXXX-XXXX)" << endl;
            string phone_number;

            getline(cin, phone_number);

            for (auto& customer : customerlist.customers) {
                cout << phone_number << " ��ȸ��.." << endl << endl;
                if (customer.getPhoneNum() == phone_number) {
                    newOrder.setMember(true);
                    break;
                }
            }

            if (newOrder.isMember()) {
                cout << "Ȯ�εǾ����ϴ�!" << endl;
            }
            else {
                cout << "ȸ�� ������ �������� �ʽ��ϴ�." << endl;
            }

            break;
        }
        else if (choice == 2) {
            //ȸ�� �߰��� �ұ�主���,,,
            break;
        }
        else {
            cout << "�߸��� �Է��Դϴ�." << endl;
        }
            
    }

    newOrder.Change_ordermenu(menulist);

    if (newOrder.is_order_items_empty()) {
        cout << "�ֹ� �׸��� ��� �����Ƿ� �ֹ��� �߰����� �ʽ��ϴ�." << endl;
        return;
    }
    
    Orders.push_back(newOrder);
    totalOrderCount++;
    remainingOrderCount++;
    cout << totalOrderCount << "�� �ֹ��� �߰��Ǿ����ϴ�!"<<endl;
}

// �ֹ� ����
void OrderList::change_order(int orderN,MenuList& menulist) {
    for (auto it = Orders.begin(); it != Orders.end(); ++it) {
        if (it->get_order_number() == orderN) {
            if (!it->isComplete()) {
                it->Change_ordermenu(menulist);

                if (it->is_order_items_empty()) {
                    cout << "�ֹ� �׸��� ��������Ƿ� �ֹ��� �����˴ϴ�."<<endl;
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
        }
        return;
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