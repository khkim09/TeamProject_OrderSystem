/*

주문서 list 클래스 관련 멤버함수
주문서들을 모아두고 주문 건수를 관리한다.

*/
#include "OrderList.h"
#include <iostream>
#include <sstream>


// 정적 멤버 초기화
int OrderList::totalOrderCount = 0;
int OrderList::completeOrderCount = 0;
int OrderList::remainingOrderCount = 0;


// OrderList 파일 읽기
void OrderList::read_Orderlist_file(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open the file: " << filename << endl;
        return;
    }

    Orders.clear();

    // 파일의 맨 처음에 주문 건수들을 읽어들임
    file >> totalOrderCount >> completeOrderCount >> remainingOrderCount;
    file.ignore(numeric_limits<streamsize>::max(), '\n');  // 행 끝까지 무시

    int orderNumber, total, receiptTotal, complete, member;
    while (file >> orderNumber >> total >> receiptTotal >> complete >> member) {
        file.ignore(); // 행 끝의 공백 문자 제거
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

// OrderList 파일 쓰기
void OrderList::write_Orderlist_file(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open the file: " << filename << endl;
        return;
    }

    // 파일의 맨 처음에 주문 건수들을 기록
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
            file << "\"" << item.getName() << "\" " // 수동으로 따옴표 추가
                << item.getCount() << " "
                << item.getPrice() << endl;
        }
        file << "END_OF_ORDER" << endl;
    }
    file.close();
}


// 새로운 주문 추가
bool OrderList::new_order(MenuList& menulist,CustomerList& customerlist) {
    Order newOrder(totalOrderCount+1);

    int choice;
    bool answer = false;

    while (true) {
        cout << "회원이십니까?" << endl;
        cout << "1. 예" << endl;
        cout << "2. 아니오" << endl;

        cin >> choice;
        cin.ignore();
        cout << endl;

        if (choice == 1) {
            cout << "회원 조회를 위해 전화번호를 입력해주십시오 (010-XXXX-XXXX) : ";
            string phone_number;

            getline(cin, phone_number);

            for (auto& customer : customerlist.customers) {
                cout << phone_number << " 조회중.." << endl << endl;
                if (customer.getPhoneNum() == phone_number) {
                    newOrder.setMember(true);
                    cout << "'" << customer.getName() << "'님 확인되었습니다!" << endl;
                    break;
                }
            }

            if (!newOrder.isMember()) {
                cout << "회원 정보가 존재하지 않습니다." << endl;
            }
            break;
        }
        else if (choice == 2) { // 회원 정보 등록 과정
            char ans;
            cout << "회원 등록을 진행하시겠습니까? (y/n) : ";
            cin >> ans; // 등록 여부 (ans)
            cin.ignore();
            cout << endl;

            if (ans == 'y') {
                answer = true; // main으로 반환할 bool값 (answer)
                cout << "주문을 종료하시면 회원 등록 화면으로 넘어갑니다." << endl;
            }
            break;
        }
        else {
            cout << "잘못된 입력입니다." << endl;
        }
    }

    newOrder.Change_ordermenu(menulist);

    if (newOrder.is_order_items_empty()) {
        cout << "주문 항목이 비어 있으므로 주문이 추가되지 않습니다." << endl;
        return false;
    }
    
    Orders.push_back(newOrder);
    totalOrderCount++;
    remainingOrderCount++;
    cout << totalOrderCount << "번 주문이 추가되었습니다!"<< endl;
    return answer;
}

// 주문 변경
void OrderList::change_order(int orderN, MenuList& menulist) {
    for (auto it = Orders.begin(); it != Orders.end(); ++it) {
        if (it->get_order_number() == orderN) {
            if (!it->isComplete()) {
                it->Change_ordermenu(menulist);

                if (it->is_order_items_empty()) {
                    cout << "주문 항목이 비어있으므로 주문이 삭제됩니다." << endl;
                    Orders.erase(it);
                }
            }
            else {
                cout << "이미 완료된 주문입니다." << endl;
            }
            return;
        }
    }
    cout << "존재하지 않는 주문번호입니다." << endl;

}

// 주문 삭제
void OrderList::delete_order(int orderN) {
    for (auto it = Orders.begin(); it != Orders.end(); ++it) {
        if (it->get_order_number() == orderN) {
            if (!it->isComplete()) {
                Orders.erase(it);
                remainingOrderCount--;
                cout << orderN << "번 주문이 취소되었습니다." << endl;
            }
            else {
                cout << "완료된 주문입니다." << endl;
            }
            return;
        }
    }
    cout << "존재하지 않는 주문번호입니다." << endl;
}


// 주문 완료
void OrderList::complete_order(int orderN) {
    for (auto& order : Orders) {
        if (order.get_order_number() == orderN) {
            if (!order.isComplete()) {
                order.Complete_order();
                completeOrderCount++;
                remainingOrderCount--;
                cout << orderN << "번 주문이 완료되었습니다." << endl;
            }
            else {
                cout << "이미 완료된 주문입니다." << endl;
            }
            return;
        }
    }
    cout << "존재하지 않는 주문번호입니다." << endl;
}


// 주문 출력
void OrderList::print_order(int orderN) {
    if (totalOrderCount == 0) {
        cout << "주문내역이 아직 존재하지 않습니다." << endl;
        return;
    }
    for (auto& order : Orders) {
        if (order.get_order_number() == orderN) {
            order.Check_order();
            return;
        }
    }
    cout << "존재하지 않는 주문번호입니다." << endl;
}

// 주문 건수 출력
void OrderList::show_order_count() {
    cout << "총 주문 수: " << totalOrderCount <<"건"<< endl;
    cout << "완료된 주문 수: " << completeOrderCount <<"건"<< endl;
    cout << "남은 주문 수: " << remainingOrderCount <<"건"<< endl;
}

// 남은 주문 건수 출력
void OrderList::show_remaining_order() {
    cout << "남은 주문 수: " << remainingOrderCount << "건" << endl;
}