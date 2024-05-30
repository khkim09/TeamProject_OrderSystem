/*

주문 Order Class의 멤버 함수 정의

*/
#include "Order.h"
#include <iostream>

//생성자

Order::Order()//빈 객체
    :order_number(0),total(0), member(false),discount(false), receipt_total(0), complete(false) {
    order_time.setTime();
    complete_time.setTime(); //일단 order time과 똑같이 초기화
}

Order::Order(int ordernumber)
    : order_number(ordernumber), total(0), discount(false), receipt_total(0), complete(false) {
    order_time.setTime();
    complete_time.setTime(); //일단 order time과 똑같이 초기화
}

void Order::Change_ordermenu(MenuList& menulist) {
    if (complete == true) {
        cout << "이미 완료된 주문입니다." << endl;
    }
    else {
        while (true) {
            cout << endl;
            cout << "1.메뉴 추가" << endl;
            cout << "2.메뉴 삭제" << endl;
            cout << "3.주문 항목 보기" << endl;
            cout << "4.메뉴 보기" << endl;
            cout << "0.주문 종료하기" << endl;
            cout << "번호를 입력해주세요";

            int order;
            cin >> order;
            switch (order) {
            case 1: {
                string name;
                int count;

                cout <<endl<< "추가할 메뉴 이름을 입력해주세요.";
                getchar();
                getline(cin, name);
                cout <<endl<< "추가할 수량을 입력해주세요.";
                cin >> count;
                Add_ordermenu(name, count,menulist);
                break;
            }
            case 2: {
                if (order_items.empty()) {
                    cout << "삭제할 항목이 존재하지 않습니다." << endl;
                    break;
                }
                string name;
                int count;
                cout <<endl<< "삭제할 메뉴 이름을 입력해주세요.";
                getchar();
                getline(cin, name);
                cout <<endl<< "삭제할 수량을 입력해주세요.";
                cin >> count;
                delete_ordermenu(name, count);
                break;
            }
            case 3: {
                Check_order_items();
                break;
            }
            case 4: {
                menulist.showList();
            }
            case 0: {


                return;
            }
            default: {
                cout << "잘못된 입력입니다." << endl;
            }
            }
        }
    }
}

void Order::Add_ordermenu(const string& name, int count, MenuList& menuList) {
    // 메뉴가 Menulist에 존재하는지 확인
    bool menuExists = false;
    int price = 0;

    for (auto& menu : menuList.getList()) {
        if (menu.getName() == name) {
            menuExists = true;
            price = menu.getPrice();
            break;
        }
    }

    // 메뉴가 Menulist에 존재하지 않으면 메시지 출력 후 추가되지 않음
    if (!menuExists) {
        cout << "존재하지 않는 메뉴입니다!" << endl;
        return;
    }

    // 메뉴가 이미 존재하는지 확인하고 수량 업데이트 또는 추가
    for (auto& item : order_items) {
        if (item.getName() == name) { // 메뉴가 이미 존재한다면
            item.setCount(item.getCount() + count);
            calculate_price();
            return;
        }
    }

    // 새로운 메뉴 추가
    OrderMenu newItem(name, count);
    newItem.setPrice(price);
    order_items.push_back(newItem);
    calculate_price();
}


void Order::Add_ordermenu(string name, int count, int price) {
    for (auto& item : order_items) {
        if (item.getName() == name) { // 메뉴가 이미 존재한다면
            item.setCount(item.getCount() + count);
            calculate_price();
            return;
        }
    }
    // 메뉴가 존재하지 않으면 새로 추가
    OrderMenu newItem(name, count);
    newItem.setPrice(price);
    order_items.push_back(newItem);
};


void Order::delete_ordermenu(string name, int count) {
    for (auto it = order_items.begin(); it != order_items.end(); ++it) {
        if (it->getName() == name) { // OrderMenu 객체의 name 멤버를 가져와서 std::string과 비교
            if (it->getCount() > count) { // 수량이 충분하면
                it->setCount(it->getCount() - count); // 수량을 감소시킴
            }
            else if (it->getCount() == count) { // 수량이 같으면
                order_items.erase(it); // 해당 항목을 삭제
            }
            else { // 수량이 부족하면
                cout << "유효한 수량이 아닙니다." << endl;
            }
            return;
        }
    }
    cout << "존재하지 않는 주문 항목입니다." << endl; // 주문 항목이 존재하지 않을 경우
}



void Order::Check_order() const {
    cout << "주문 번호: " << order_number << endl;
    cout << "주문 시간: "; order_time.printTime(); cout << endl;
    Check_order_items();
    cout << "총액: " << total << endl;
    cout << "할인: " << (discount ? "O" : "X") << endl;
    cout << "회원: " << (member ? "O" : "X")<<endl;
    cout << "결제 금액: " << receipt_total << endl;
    cout << "주문 완료: " << (complete ? "O" : "X") << endl;
    if (complete) {
        cout << "주문 완료 시간: "; complete_time.printTime() ; cout << endl;
    }
}

void Order::Check_order_items()const {
    if (order_items.empty()) {
        cout << "주문 항목이 존재하지 않습니다!" << endl;
        return;
    }
    cout << "주문 항목:" << endl;
    for (const auto& item : order_items) {
        cout << "- " << item.getName() << "    " << item.getCount() << endl;
    }
}

void Order::Complete_order() {
    complete = true;
    complete_time.setTime();
}

bool Order::isComplete() const {
    return complete;
}

bool Order::is_order_items_empty() const {
    return order_items.empty();
}

bool Order::isMember() const {
    return member;
}

vector<OrderMenu>& Order::getItems() {
    return order_items;
}

void Order::set_total(int total) {
    this->total = total;
}

void Order::set_receipt_total(int receiptTotal) {
    this->receipt_total = receiptTotal;
}

void Order::set_complete(bool complete) {
    this->complete = complete;
}

void Order::calculate_price() {
    total = 0;
    for (const auto& item : order_items) {
        total += item.getCount() * item.getPrice();
    }

    if (total >= 50000) {
        discount = true;
        if (member) {//허들 넘고 회원일때
            receipt_total = static_cast<int>(total * 0.90); // 10% 할인
        }
        else//허들만 넘었을 때
            receipt_total = static_cast<int>(total * 0.95);
    }
    else if (member) //회원이기만 할때
        receipt_total = static_cast<int>(total * 0.95);
    else //해당사항 없을 때
        receipt_total = total;
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

// 주문 시간 설정
void Order::set_order_time(Time& time) {
    order_time = time;
}

// 완료 시간 설정
void Order::set_complete_time(Time& time) {
    complete_time = time;
}

void Order::setMember(bool isMember) {
    member = isMember;
}

Order::~Order() {
    // 소멸자 구현 (필요한 경우 리소스 정리)
}

