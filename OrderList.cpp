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
    if (!file.is_open()) {//예외
        cerr << "Could not open the file: " << filename << endl;
        return;
    }

    Orders.clear();

    // 파일의 맨 처음에 주문 건수 관련 멤버를 읽어들임
    file >> totalOrderCount >> completeOrderCount >> remainingOrderCount;
    file.ignore(numeric_limits<streamsize>::max(), '\n');  // 행 끝까지 무시

    int orderNumber, total, receiptTotal, complete, member;
    while (file >> orderNumber >> total >> receiptTotal >> complete >> member) {
        //주문번호, 총액, 결제 금액, 완료 여부, 멤버 여부 읽기
        file.ignore(); // 행 끝의 공백 문자 제거
        Order order(orderNumber);
        order.set_total(total);
        order.set_receipt_total(receiptTotal);
        order.set_complete(complete);
        order.setMember(member);

        //주문 시간, 완료 시간 읽기
        Time orderTime;
        orderTime.loadFromFile(file);
        order.set_order_time(orderTime);

        Time completeTime;
        completeTime.loadFromFile(file);
        order.set_complete_time(completeTime);


        string line;
        while (getline(file, line)) {//주문 항목 읽기

            if (line == "END_OF_ORDER") break; //주문 항목이 끝나면 종료

            //"메뉴이름" 수량 가격 형식으로 저장됨
            //형식에 따라 읽기
            size_t first_quote = line.find('\"');
            size_t second_quote = line.find('\"', first_quote + 1);

            string name = line.substr(first_quote + 1, second_quote - first_quote - 1);
            istringstream iss(line.substr(second_quote + 1));
            int count, price;
            iss >> count >> price;
            //주문 항목에 추가
            order.Add_ordermenu(name, count, price);
        }
        //주문서 추가
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
        // 주문번호, 총액, 결제금액, 완료 여부, 회원 여부 쓰기
        file << order.get_order_number() << " "
            << order.get_total() << " "
            << order.get_receipt_total() << " "
            << order.isComplete() << " "
            << order.isMember() << endl;

        // 주문 시간, 완료 시간 쓰기
        order.get_order_time().saveToFile(file);
        order.get_complete_time().saveToFile(file);

        // 주문 항목 쓰기. 메뉴 이름은 따옴표 추가
        for (auto& item : order.getItems()) {
            file << "\"" << item.getName() << "\" " // 수동으로 따옴표 추가
                << item.getCount() << " "
                << item.getPrice() << endl;
        }
        // 주문서 마지막에 메시지 추가
        file << "END_OF_ORDER" << endl;
    }
    file.close();
}


// 새로운 주문 추가
bool OrderList::new_order(MenuList& menulist, CustomerList& customerlist) {
    // 새 주문서
    Order newOrder(totalOrderCount + 1);

    int choice;
    bool answer = false;

    while (true) {
        // 회원여부 확인
        cout << "회원이십니까?" << endl;
        cout << "1. 예" << endl;
        cout << "2. 아니오" << endl;

        cin >> choice;
        cin.ignore();
        cout << endl;

        if (choice == 1) {// 회원이라면 전화번호로 회원 조회
            cout << "회원 조회를 위해 전화번호를 입력해주십시오 (010-XXXX-XXXX) : ";
            string phone_number;

            getline(cin, phone_number);

            for (auto& customer : customerlist.customers) {
                cout << phone_number << " 조회중.." << endl << endl;
                if (customer.getPhoneNum() == phone_number) {
                    newOrder.setMember(true); // 확인 되면 회원 여부 true로 변경
                    cout << "'" << customer.getName() << "'님 확인되었습니다!" << endl;
                    break;
                }
            }

            if (!newOrder.isMember()) { // 조회 안되면 메시지 출력
                cout << "회원 정보가 존재하지 않습니다." << endl;
            }
            break;
        }
        // 주문 먼저 끝낸 후 회원 정보 등록 화면으로 이동
        else if (choice == 2) {
            char ans;
            cout << "회원 등록을 진행하시겠습니까? (y/n) : ";
            cin >> ans; // 등록 의사 (ans)
            cin.ignore();
            cout << endl;

            if (ans == 'y') { // 등록 의사 == 'y' : bool값 true반환
                answer = true; // main으로 반환할 bool값 저장(answer)
                cout << "주문을 종료하시면 회원 등록 화면으로 넘어갑니다." << endl;
            }
            break;
        }
        else {
            cout << "잘못된 입력입니다." << endl;
        }
    }

    // 주문 항목 업데이트
    newOrder.Change_ordermenu(menulist);

    if (newOrder.is_order_items_empty()) {// 주문 항목이 비어있으면 메시지 출력
        cout << "주문 항목이 비어 있으므로 주문이 추가되지 않습니다." << endl;
        return false;
    }


    Orders.push_back(newOrder);//주문서 추가
    totalOrderCount++; //주문 건수 관련 변수 업데이트
    remainingOrderCount++;
    cout << totalOrderCount << "번 주문이 추가되었습니다!" << endl;//메시지 출력
    return answer; //회원 추가 여부 반환
}

// 주문 메뉴 수량 변경/추가
void OrderList::change_order(int orderN, MenuList& menulist) {
    for (auto it = Orders.begin(); it != Orders.end(); ++it) {
        if (it->get_order_number() == orderN) {
            if (!it->isComplete()) { //주문이 완료되지 않았을 때만 가능
                it->Change_ordermenu(menulist);//주문 항목 변경

                if (it->is_order_items_empty()) { //주문 항목이 비어있으면 주문서 삭제
                    cout << "주문 항목이 비어있으므로 주문이 삭제됩니다." << endl;
                    Orders.erase(it);
                }
            }
            else {//완료된 주문이면 메시지 출력
                cout << "이미 완료된 주문입니다." << endl;
            }
            return;
        }
    }
    //존재하지 않는 주문서면 메시지 출력
    cout << "존재하지 않는 주문번호입니다." << endl;

}

// 주문서 삭제
void OrderList::delete_order(int orderN) {
    for (auto it = Orders.begin(); it != Orders.end(); ++it) {
        if (it->get_order_number() == orderN) { //맞는 주문 번호를 찾아서 삭제
            if (!it->isComplete()) {//완료되지 않는 주문서만 삭제 가능
                Orders.erase(it);
                remainingOrderCount--;//남은 주문 건 수 업데이트
                cout << orderN << "번 주문이 취소되었습니다." << endl;
            }
            else {//완료된 주문은 삭제 불가능
                cout << "완료된 주문입니다." << endl;
            }
            return;
        }
    }
    //존재하지 않는 주문서면 메시지 출력
    cout << "존재하지 않는 주문번호입니다." << endl;
}


// 주문 완료
void OrderList::complete_order(int orderN) {

    for (auto& order : Orders) {
        if (order.get_order_number() == orderN) {//입력한 주문 번호를 찾아서 
            if (!order.isComplete()) {
                order.Complete_order(); //complete의 값을 true로 변경
                completeOrderCount++; //주문 건수 관련 변수 업데이트
                remainingOrderCount--;
                cout << orderN << "번 주문이 완료되었습니다." << endl;
            }
            else {//완료된 주문이면 메시지 출력
                cout << "이미 완료된 주문입니다." << endl;
            }
            return;
        }
    }//존재하지 않는 주문서면 메시지 출력
    cout << "존재하지 않는 주문번호입니다." << endl;
}


// 주문서 출력
void OrderList::print_order(int orderN) {
    if (totalOrderCount == 0) {//주문 내역이 비어있을 경우 메시지 출력
        cout << "주문내역이 아직 존재하지 않습니다." << endl;
        return;
    }
    for (auto& order : Orders) { //orderN번 주문 출력
        if (order.get_order_number() == orderN) {
            order.Check_order();
            return;
        }
    }
    //존재하지 않는 주문서면 메시지 출력
    cout << "존재하지 않는 주문번호입니다." << endl;
}

// 주문 건수 관련 멤버 출력
void OrderList::show_order_count() {
    cout << "총 주문 수: " << totalOrderCount << "건" << endl;
    cout << "완료된 주문 수: " << completeOrderCount << "건" << endl;
    cout << "남은 주문 수: " << remainingOrderCount << "건" << endl;
}

// 남은 주문 건수 출력
void OrderList::show_remaining_order() {
    cout << "남은 주문 수: " << remainingOrderCount << "건" << endl;
}