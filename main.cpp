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

Customer createCustomerFromInput() { // �ֹ��� ���� ����
    string name;
    string birth;
    string phoneNum;
    string address;
    string request;
    string paymentMethod;

    cout << "-------ȸ��(�ֹ���) ���� ���-------";
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

void menu() { // ȸ�� ���� ���� ��� ���� �޴���
    cout << "******************************" << endl;
    cout << "-----1. ȸ�� ���� �߰�------" << endl;
    cout << "-----2. ȸ�� ���� ����------" << endl;
    cout << "-----3. ȸ�� ���� ����------" << endl;
    cout << "-----4. ȸ�� ���� ���------" << endl;
    cout << "---5. ��� ȸ�� ���� ���---" << endl;
    cout << "---6. ��� ȸ�� ���� ����---" << endl;
    cout << "------���α׷� ���� (Q/q)-----" << endl;
    cout << "******************************" << endl;
}

bool isquit(char choice) { // ���α׷� ���� �Է� ���� �Ǵ�
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

        cout << "---------1.�޴���----------" << endl;
        cout << "----2.ȸ��(�ֹ���) ����----" << endl;
        cout << "--------3.�ֹ� ȭ��--------" << endl;
        cout << "------4.���α׷� ����------" << endl;

        cout << endl << "������ �۾� ��ȣ�� �Է����ּ��� : ";
        cin >> job;
        cin.ignore();
        cout << endl;

        if (job == 1) {
            loop = true;

            char choice;
            string name, line;

            while (loop) {
                cout << "----------�޴���----------" << endl;
                cout << "------�޴� �߰� = 1-------" << endl;
                cout << "------�޴� ���� = 2-------" << endl;
                cout << "----�޴� ��� ���� = 3----" << endl;
                cout << "-----�޴��� ���� = 4------" << endl;
                cout << "----�޴��� ���� = Q/q-----" << endl;
                cout << endl;
                cout << "������ �޴� ��ȣ�� �Է����ּ��� : ";
                cin >> choice;
                cin.ignore();
                cout << endl;

                switch (choice) {
                case '1': {
                    menulist.addMenu(addMenuFromInput());
                    cout << endl << "�޴��� �߰��Ǿ����ϴ�!" << endl;
                    menulist.saveToFile("Menu_List.txt");
                    break;
                }
                case '2': {
                    cout << "--------�޴� �̸� �Է�---------" << endl;
                    getline(cin, name);

                    menulist.removeMenu(name);
                    cout << endl << "'" << name << "'" << " �޴��� �����߽��ϴ�!" << endl;
                    menulist.saveToFile("Menu_List.txt");
                    break;
                }
                case '3': {
                    cout << "--------�޴� �̸� �Է�---------" << endl;
                    getline(cin, name);

                    menulist.changeMenu(name);
                    cout << endl << "'" << name << "'" << " �޴��� �����߽��ϴ�!" << endl;
                    menulist.saveToFile("Menu_List.txt");
                    break;
                }
                case '4': {
                    menulist.showList();
                    cout << endl;
                    break;
                }
                case 'q': case 'Q': {
                    menulist.saveToFile("Menu_List.txt");
                    cout << "+++�޴� ������Ʈ �Ϸ�+++" << endl << endl;
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
        else if (job == 2) { // ȸ��(�ֹ���) ���� ���� �޴� ����
            loop = true;
            char choice;

            // ���� ��� �޴��� ���� �ٷ� �ֹ��� ����Ʈ(����) ������Ʈ �ǵ��� ����
            while (loop) {
                menu(); // �ֹ��� ���� ���� �޴��� ���
                cout << endl;
                cout << "������ �޴� ��ȣ�� �Է����ּ��� : ";
                cin >> choice;
                cin.ignore(); // enter Ű ������
                cout << endl;

                switch (choice) {
                case '1': { // �ֹ��� ���� �߰�
                    Customer customer = createCustomerFromInput();
                    customerList.addCustomer(customer);
                    customerList.saveToFile("Customers.txt"); 
                    break;
                }
                case '2': { // �ֹ��� ���� ����
                    string delPhoneNum; // ��ȭ��ȣ�� ȸ�� ��ȸ
                    cout << "������ ȸ������ ��ȭ��ȣ�� �Է����ּ��� (010-XXXX-XXXX) : ";
                    getline(cin, delPhoneNum);
                    if (customerList.deleteCustomer(delPhoneNum))
                        cout << "ȸ�� ���� ������ �Ϸ�Ǿ����ϴ�." << endl;
                    else
                        cout << "�ش� �ֹ��� ������ ã�� �� �����ϴ�." << endl;
                    cout << endl;
                    customerList.saveToFile("Customers.txt");
                    break;
                }
                case '3': { // �ֹ��� ���� ����
                    string phoneNum, newValue; // ��ȭ��ȣ�� ��ȸ, ������ ���� (��ü�� ��)
                    int field;
                    cout << "������ ȸ������ ��ȭ��ȣ�� �Է����ּ��� (010-XXXX-XXXX) : ";
                    getline(cin, phoneNum);
                    cout << "������ ������ �������ּ��� (1 : ��ȭ��ȣ | 2 : ��� ���� �ּ� | 3 : ��û���� | 4 : ��������) : ";
                    cin >> field;
                    cin.ignore();
                    cout << "������Ʈ �� ������ �Է����ּ��� : ";
                    getline(cin, newValue);
                    if (customerList.updateCustomer(phoneNum, field, newValue))
                        cout << "ȸ�� ���� ������ �Ϸ�Ǿ����ϴ�." << endl;
                    else
                        cout << "�ش� ȸ�� ������ ���ų� ������ ���� �Է��� �߸��Ǿ����ϴ�." << endl;
                    cout << endl;
                    customerList.saveToFile("Customers.txt");
                    break;
                }
                case '4': { // �ֹ��� 1���� ���� ���
                    string findPhoneNum;
                    cout << "����� ȸ������ ��ȭ��ȣ�� �Է����ּ��� (010-XXXX-XXXX) : ";
                    getline(cin, findPhoneNum);
                    if (!customerList.printCustomerInfo(findPhoneNum))
                        cout << "ȸ�� ������ ã�� �� �����ϴ�." << endl;
                    cout << endl;
                    break;
                }
                case '5': { // ��� �ֹ��� ���� ���
                    customerList.printAllCustomers("Customers.txt");
                    cout << endl;
                    break;
                }
                case '6': { // ��� �ֹ��� ���� ����
                    char accept;
                    cout << "������ ��� �ֹ��� ������ �����Ͻðڽ��ϱ�? (y/n) : ";
                    cin >> accept;
                    cin.ignore();

                    if (accept == 'y') {
                        customerList.clearAllCustomers();
                        cout << "��� �ֹ��� ������ �����Ǿ����ϴ�." << endl;
                    }
                    cout << endl;
                    customerList.saveToFile("Customers.txt");
                    break;
                }
                case 'q': case 'Q': { // �ֹ��� ���� ���α׷� ����
                    customerList.saveToFile("Customers.txt");
                    cout << "+++�ֹ��� ���� ������Ʈ �Ϸ�+++" << endl << endl;
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
            char choice;

            while (loop) {
                cout << "1. �ֹ� �����ϱ�" << endl;
                cout << "2. �ֹ� �޴� ���� �� �߰��ϱ�" << endl;
                cout << "3. �ֹ� �����ϱ�" << endl;
                cout << "4. �ֹ� �Ϸ��ϱ�" << endl;
                cout << "5. �ֹ��� ����ϱ�" << endl;
                cout << "6. �ֹ� �� �� Ȯ���ϱ�" << endl;
                cout << "7. ���� �ֹ� �� �� Ȯ���ϱ�" << endl;
                cout << "Q. �����ϱ� (Q/q)" << endl;
                cout << endl;
                cout << "������ �޴� ��ȣ�� �Է����ּ��� : ";
                cin >> choice;
                cin.ignore();
                cout << endl;

                switch (choice) {
                case '1': { // ȸ�� ���� ��� ��� �߰�
                    if (orderList.new_order(menulist, customerList)) {
                        Customer customer = createCustomerFromInput();
                        customerList.addCustomer(customer);
                        customerList.saveToFile("Customers.txt");
                    }
                    cout << endl;
                    break;
                }
                case '2': {
                    cout << "�ֹ���ȣ�� �Է����ּ��� : ";
                    int orderN;
                    cin >> orderN;
                    orderList.change_order(orderN, menulist);
                    orderList.write_Orderlist_file("orders.txt");
                    cout << endl;
                    break;
                }
                case '3': {
                    cout << "�ֹ���ȣ�� �Է����ּ��� : ";
                    int orderN;
                    cin >> orderN;
                    orderList.delete_order(orderN);
                    orderList.write_Orderlist_file("orders.txt");
                    cout << endl;
                    break;
                }
                case '4': {
                    cout << "�ֹ���ȣ�� �Է����ּ��� : ";
                    int orderN;
                    cin >> orderN;
                    orderList.complete_order(orderN);
                    orderList.write_Orderlist_file("orders.txt");
                    cout << endl;
                    break;
                }
                case '5': {
                    cout << "�ֹ���ȣ�� �Է����ּ��� : ";
                    int orderN;
                    cin >> orderN;
                    orderList.print_order(orderN);
                    cout << endl;
                    break;
                }
                case '6': {
                    orderList.show_order_count();
                    cout << endl;
                    break;
                }
                case '7': {
                    orderList.show_remaining_order();
                    cout << endl;
                    break;
                }
                case 'q': case 'Q': {
                    orderList.write_Orderlist_file("orders.txt"); // �ֹ� ���� ���Ͽ� ����
                    cout << "+++�ֹ� ���� ������Ʈ �Ϸ�+++" << endl << endl;
                    loop = false;
                    break;
                }
                default:
                    cout << "�߸��� ��� �����Դϴ�." << endl << endl;
                }
            }
        }
        else if (job == 4) {
            cout << "--���α׷��� �����մϴ�.--" << endl;
            break;
        }
    }

    return 0;
}