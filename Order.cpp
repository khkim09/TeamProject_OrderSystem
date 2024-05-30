/*

�ֹ� Order Class�� ��� �Լ� ����

*/
#include "Order.h"

//������
Order::Order(int ordernumber)
    : order_number(ordernumber), total(0), member(false), discount(false), receipt_total(0), complete(false) {
    order_time.setTime();
    complete_time.setTime(); //�ϴ� order time�� �Ȱ��� �ʱ�ȭ
}


/*����Լ�*/

//�޴� ��� ����
void Order::Change_ordermenu(MenuList& menulist) {
    if (complete == true) {
        cout << "�̹� �Ϸ�� �ֹ��Դϴ�." << endl;
    }
    else {
        while (true) {
            cout << "******************************" << endl;
            cout << "---------1. �޴� �߰�---------" << endl;
            cout << "---------2. �޴� ����---------" << endl;
            cout << "------3. �ֹ� �׸� ����-------" << endl;
            cout << "---------4. �޴� ����---------" << endl;
            cout << "-------0. �ֹ� �����ϱ�-------" << endl << endl;
            cout << "��ȣ�� �Է����ּ��� : ";

            int order;
            cin >> order;
            cin.ignore();

            switch (order) {
            case 1: { //�޴� �߰�
                string name;
                int count;

                cout << endl << "�߰��� �޴� �̸��� �Է����ּ��� : ";
                getline(cin, name);
                cout << endl << "�߰��� ������ �Է����ּ��� : ";
                cin >> count;
                cin.ignore();
                //�޴� �̸��� ������ �Է¹޾Ƽ� �߰�
                Add_ordermenu(name, count, menulist);
                break;
            }
            case 2: {//�޴� ����
                //�ֹ� �׸��� ����ִٸ� �̸��� ������ �Է¹��� �ʴ´�
                if (order_items.empty()) {
                    cout << "������ �׸��� �������� �ʽ��ϴ�." << endl;
                    break;
                }
                string name;
                int count;

                cout << endl << "������ �޴� �̸��� �Է����ּ��� : ";
                getline(cin, name);
                cout << endl << "������ ������ �Է����ּ��� : ";
                cin >> count;
                cin.ignore();
                //�޴� �̸��� ������ �Է¹޾� ����
                delete_ordermenu(name, count);
                break;
            }
            case 3: {//�޴� �̸��� ������ �Է¹޾� ����

                Check_order_items();
                break;
            }
            case 4: {//�޴��� ����
                menulist.showList();
            }
            case 0: {//����
                return;
            }
            default: {//�߸��� �Է��� �� 
                cout << "�߸��� �Է��Դϴ�." << endl;
            }
            }
        }
    }
}

//�޴� �� ���� �߰�
//���α׷����� �߰��� �� ����Ѵ�.
void Order::Add_ordermenu(const string& name, int count, MenuList& menuList) {
    // �޴��� Menulist�� �����ϴ��� Ȯ��
    bool menuExists = false;
    int price = 0;

    //�Է¹��� �޴� �̸��� �޴��ǿ� �����ϴ��� Ȯ��
    for (auto& menu : menuList.getList()) {
        if (menu.getName() == name) {
            menuExists = true;
            price = menu.getPrice();
            break;
        }
    }

    // �޴��� Menulist�� �������� ������ �޽��� ��� �� �߰����� ����
    if (!menuExists) {
        cout << "�������� �ʴ� �޴��Դϴ�!" << endl;
        return;
    }

    // �޴��� �ֹ� �׸� �����ϴ��� Ȯ��
    for (auto& item : order_items) {
        if (item.getName() == name) { // �޴��� �̹� �����Ѵٸ�
            item.setCount(item.getCount() + count); //������ �߰�
            calculate_price(); //���� ������Ʈ
            return;
        }
    }

    //�ֹ��׸� �������� �ʴ´ٸ� ���� �߰�
    OrderMenu newItem(name, count);
    newItem.setPrice(price);
    order_items.push_back(newItem);
    calculate_price();
}

//�޴� �� ���� �߰�
//�ֹ��� ���� �� ����ϴ� �Լ�
void Order::Add_ordermenu(string name, int count, int price) {
    OrderMenu newItem(name, count);
    newItem.setPrice(price);
    order_items.push_back(newItem);
};

//�޴� �� ���� ����
void Order::delete_ordermenu(string name, int count) {
    for (auto it = order_items.begin(); it != order_items.end(); ++it) {
        if (it->getName() == name) { // OrderMenu ��ü�� name ����� �����ͼ� �Է¹��� �̸��� ��
            if (it->getCount() > count) { // ������ ����ϸ�
                it->setCount(it->getCount() - count); // ������ ���ҽ�Ŵ
            }
            else if (it->getCount() == count) { // ������ ������
                order_items.erase(it); // �ش� �׸��� ����
            }
            else { // ������ �����ϸ� ���� �޽��� ���
                cout << "��ȿ�� ������ �ƴմϴ�." << endl;
            }
            return;
        }
    }
    // �ֹ� �׸��� �������� ���� ���
    cout << "�������� �ʴ� �ֹ� �׸��Դϴ�." << endl;
}


//�ֹ� ���� ��� �ֹ����� ����� ��� ����Ѵ�
void Order::Check_order() const {

    cout << endl;
    cout << "******************************" << endl << endl;
    cout << "�ֹ� ��ȣ : " << order_number << endl;
    cout << "�ֹ� �ð� : "; order_time.printTime(); cout << endl << endl;
    Check_order_items();
    cout << endl;
    cout << "�Ѿ� : " << total << endl;
    cout << "���� : " << (discount ? "O" : "X") << endl;
    cout << "ȸ�� : " << (member ? "O" : "X") << endl;
    cout << "���� �ݾ� : " << receipt_total << endl;
    cout << "�ֹ� �Ϸ� : " << (complete ? "O" : "X") << endl;
    if (complete) {
        cout << "�ֹ� �Ϸ� �ð� : "; complete_time.printTime(); cout << endl;
    }
    cout << "******************************" << endl;
}

//�ֹ� �׸� ���
void Order::Check_order_items()const {
    if (order_items.empty()) {//�ֹ� �׸��� �������� ���� ��
        cout << "�ֹ� �׸��� �������� �ʽ��ϴ�!" << endl;
        return;
    }
    cout << "�ֹ� �׸� :" << endl;
    for (const auto& item : order_items) { //�ֹ� �׸��� ������� ���
        cout << "- " << item.getName() << "    " << item.getCount() << endl;
    }
}

//�ֹ� �Ϸ�
void Order::Complete_order() {
    //complete�� true�� �ٲٰ� �ֹ��Ϸ� �ð� ������Ʈ
    complete = true;
    complete_time.setTime();
}


//�ֹ� �Ϸ� ���� Ȯ��
bool Order::isComplete() const {
    return complete;
}

//�ֹ� �׸� ������� Ȯ��
bool Order::is_order_items_empty() const {
    return order_items.empty();
}

//ȸ�� ���� Ȯ��
bool Order::isMember() const {
    return member;
}

//���� ���
void Order::calculate_price() {
    total = 0;
    for (const auto& item : order_items) {
        total += item.getCount() * item.getPrice();
    }

    if (total >= 50000) {
        discount = true;
        if (member) {//��� �Ѱ� ȸ���϶�
            receipt_total = static_cast<int>(total * 0.90); // 10% ����
        }
        else//��鸸 �Ѿ��� ��
            receipt_total = static_cast<int>(total * 0.95);
    }
    else if (member) //ȸ���̱⸸ �Ҷ�
        receipt_total = static_cast<int>(total * 0.95);
    else //�ش���� ���� ��
        receipt_total = total;
}


/*��� ��������*/
vector<OrderMenu>& Order::getItems() {
    return order_items;
}

int Order::get_order_number() const {
    return order_number;
}

int Order::get_total() const {
    return total;
}

int Order::get_receipt_total() const {
    return receipt_total;
}

Time Order::get_order_time() const {
    return order_time;
}

Time Order::get_complete_time() const {
    return complete_time;
}



/*��� �Է��ϱ�*/

void Order::set_total(int total) {
    this->total = total;
}

void Order::set_receipt_total(int receiptTotal) {
    this->receipt_total = receiptTotal;
}

void Order::set_complete(bool complete) {
    this->complete = complete;
}

// �ֹ� �ð� ����
void Order::set_order_time(Time& time) {
    order_time = time;
}

// �Ϸ� �ð� ����
void Order::set_complete_time(Time& time) {
    complete_time = time;
}

void Order::setMember(bool isMember) {
    member = isMember;
}