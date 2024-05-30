#include "OrderList.h"
#include "MenuList.h"
#include "CustomerList.h"
using namespace std;

Menu addMenuFromInput() {
    string name;
    int price;
    string introduce;

    cout << "--------�޴� �̸� �Է�---------" << endl;
    getline(cin, name);
    cout << "--------�޴� ���� �Է�---------" << endl;
    cin >> price;
    cin.ignore();
    cout << "--------�޴� �Ұ� �Է�---------" << endl;
    getline(cin, introduce);

    return Menu(name, price, introduce);
}

Customer createCustomerFromInput() {
    string name;
    string birth;
    string phoneNum;
    string address;
    string request;
    string paymentMethod;

    cout << "�ֹ��� ���� : ";
    getline(cin, name);
    cout << "�ֹ��� ������� (YY-MM-DD) : ";
    getline(cin, birth);
    cout << "�ֹ��� ��ȭ��ȣ (010-XXXX-XXXX) : ";
    getline(cin, phoneNum);
    cout << "��� ���� �ּ� : ";
    getline(cin, address);
    cout << "�ֹ� �� ��û���� : ";
    getline(cin, request);
    cout << "�������� (ī�� / ����) : ";
    getline(cin, paymentMethod);

    return Customer(name, birth, phoneNum, address, request, paymentMethod);
}

void menu() {
    cout << "******************************" << endl;
    cout << "-----1. �ֹ��� ���� �߰�------" << endl;
    cout << "-----2. �ֹ��� ���� ����------" << endl;
    cout << "-----3. �ֹ��� ���� ����------" << endl;
    cout << "-----4. �ֹ��� ���� ���------" << endl;
    cout << "---5. ��� �ֹ��� ���� ���---" << endl;
    cout << "---6. ��� �ֹ��� ���� ����---" << endl;
    cout << "------���α׷� ���� (Q/q)-----" << endl;
    cout << "******************************" << endl;
}

bool isquit(char choice) {
    if (choice == 'q' || choice == 'Q')
        return true;
    return false;
}

int main() {
    //�ֹ������б�
    OrderList orderList;
    orderList.read_Orderlist_file("orders.txt"); // ���� �ֹ� ���� �б�
    
    //�޴��� �б�
    MenuList menulist;
    menulist.readFromFile("Menu_List.txt");

    //������ �б�
    CustomerList customerList;
    customerList.loadFromFile("Customers.txt");

    bool loop;

    while (true) {
        int job;

        cout << "---------1.�޴���---------" << endl;
        cout << "------2.�ֹ��� ����-------" << endl;
        cout << "-------3.�ֹ� ȭ��--------" << endl;
        cout << "-----4.���α׷� ����------" << endl;

        cin >> job;

        if (job == 1) {
            loop = true;

            int order;
            string name, line;

            while (loop) {
                cout << "----------�޴���----------" << endl;
                cout << "------�޴� �߰� = 1-------" << endl;
                cout << "------�޴� ���� = 2-------" << endl;
                cout << "----�޴� ��� ���� = 3----" << endl;
                cout << "-----�޴��� ���� = 4------" << endl;
                cout << "-�޴��� ���� �� ���� = 5--" << endl;

                cout << "--------��� �Է�---------" << endl;

                cin >> order;
                cin.ignore();
                cout << endl;

                switch (order) {
                case 1: {
                    menulist.addMenu(addMenuFromInput());
                    cout << endl;
                    break;
                }
                case 2: {
                    cout << "--------�޴� �̸� �Է�---------" << endl;
                    getline(cin, name);

                    menulist.removeMenu(name);
                    cout << endl;
                    break;
                }
                case 3: {
                    cout << "--------�޴� �̸� �Է�---------" << endl;
                    getline(cin, name);

                    menulist.changeMenu(name);
                    cout << endl;
                    break;
                }
                case 4: {
                    menulist.showList();
                    cout << endl;
                    break;
                }
                case 5: {
                    menulist.saveToFile("Menu_List.txt");
                    cout << endl;
                    loop = false;
                    break;
                }
                default: {
                    cout << "-------�߸��� ��� �Է�--------" << endl << endl;
                    break;
                }
                }
            }
        }
        else if (job == 2) {
            loop = true;
            char choice;

            while (loop) {
                menu();
                cout << endl;
                cout << "������ �޴� ��ȣ�� �Է����ּ��� : ";
                cin >> choice;
                cin.ignore(); // enter Ű ������

                switch (choice) {
                case '1': {
                    Customer customer = createCustomerFromInput();
                    customerList.addCustomer(customer);
                    break;
                }
                case '2': {
                    string delPhoneNum;
                    cout << "������ �ֹ����� ��ȭ��ȣ�� �Է����ּ��� (010-XXXX-XXXX) : ";
                    getline(cin, delPhoneNum);
                    if (customerList.deleteCustomer(delPhoneNum))
                        cout << "�ֹ��� ���� ������ �Ϸ�Ǿ����ϴ�." << endl;
                    else
                        cout << "�ش� �ֹ��� ������ ã�� �� �����ϴ�." << endl;
                    cout << endl;
                    break;
                }
                case '3': {
                    string phoneNum, newValue;
                    int field;
                    cout << "������ �ֹ����� ��ȭ��ȣ�� �Է����ּ��� (010-XXXX-XXXX) : ";
                    getline(cin, phoneNum);
                    cout << "������ ������ �������ּ��� (1 : ��ȭ��ȣ | 2 : ��� ���� �ּ� | 3 : ��û���� | 4 : ��������) : ";
                    cin >> field;
                    cin.ignore();
                    cout << "������Ʈ �� ������ �Է����ּ��� : ";
                    getline(cin, newValue);
                    if (customerList.updateCustomer(phoneNum, field, newValue))
                        cout << "�ֹ��� ���� ������ �Ϸ�Ǿ����ϴ�." << endl;
                    else
                        cout << "�ش� �ֹ��� ������ ���ų� ������ ���� �Է��� �߸��Ǿ����ϴ�." << endl;
                    cout << endl;
                    break;
                }
                case '4': {
                    string findPhoneNum;
                    cout << "����� �ֹ����� ��ȭ��ȣ�� �Է����ּ��� (010-XXXX-XXXX) : ";
                    getline(cin, findPhoneNum);
                    if (!customerList.printCustomerInfo(findPhoneNum))
                        cout << "�ֹ��� ������ ã�� �� �����ϴ�." << endl;
                    cout << endl;
                    break;
                }
                case '5': {
                    customerList.printAllCustomers();
                    cout << endl;
                    break;
                }
                case '6': {
                    char accept;
                    cout << "������ ��� �ֹ��� ������ �����Ͻðڽ��ϱ�? (y/n) : ";
                    cin >> accept;
                    cin.ignore();

                    if (accept == 'y') {
                        customerList.clearAllCustomers();
                        cout << "��� �ֹ��� ������ �����Ǿ����ϴ�." << endl;
                    }
                    cout << endl;
                    break;
                }
                case 'q': case 'Q': {
                    customerList.saveToFile("Customers.txt");
                    cout << "�ֹ��� ���� ������Ʈ �Ϸ�" << endl;
                    cout << "���α׷� ������..." << endl << endl;
                    loop = false;
                    break;
                }
                default:
                    cout << "�߸��� ��� �����Դϴ�." << endl << endl;
                }
            }
        }
        else if (job == 3) {
            loop = true;
            int choice;

            while (loop) {
                cout << endl;
                cout << "1. �ֹ� �����ϱ�" << endl;
                cout << "2. �ֹ� �޴� ���� �� �߰��ϱ�" << endl;
                cout << "3. �ֹ� �����ϱ�" << endl;
                cout << "4. �ֹ� �Ϸ��ϱ�" << endl;
                cout << "5. �ֹ��� ����ϱ�" << endl;
                cout << "6. �ֹ� �� �� Ȯ���ϱ�" << endl;
                cout << "7. ���� �ֹ� �� �� Ȯ���ϱ�" << endl;
                cout << "8. �����ϱ�" << endl;
                cout << endl;
                cout << "������ �޴� ��ȣ�� �Է����ּ��� : ";
                cin >> choice;
                cin.ignore();

                switch (choice) {
                case 1: {
                    orderList.new_order(menulist, customerList);
                    cout << endl;
                    break;
                }
                case 2: {
                    cout << "�ֹ���ȣ�� �Է����ּ���.";
                    int orderN;
                    cin >> orderN;
                    orderList.change_order(orderN, menulist);
                    break;
                }
                case 3: {
                    cout << "�ֹ���ȣ�� �Է����ּ���.";
                    int orderN;
                    cin >> orderN;
                    orderList.delete_order(orderN);
                    break;
                }
                case 4: {
                    cout << "�ֹ���ȣ�� �Է����ּ���.";
                    int orderN;
                    cin >> orderN;
                    orderList.complete_order(orderN);
                    break;
                }
                case 5: {
                    cout << "�ֹ���ȣ�� �Է����ּ���.";
                    int orderN;
                    cin >> orderN;
                    orderList.print_order(orderN);
                    break;
                }
                case 6: {
                    orderList.show_order_count();
                    break;
                }
                case 7: {
                    orderList.show_remaining_order();
                    break;
                }
                case 8: {
                    orderList.write_Orderlist_file("orders.txt"); // �ֹ� ���� ���Ͽ� ����
                    cout << "�ֹ��ý����� �����մϴ�." << endl;
                    loop = false;
                    break;
                }
                default:
                    cout << "�߸��� ��ȣ�Դϴ�. �ٽ� �Է����ּ���" << endl;
                }
                cout << endl;
            }
        }
        else if (job == 4) {
            cout << "--���α׷��� �����մϴ�.--" << endl;
            break;
        }
    }

    return 0;
}