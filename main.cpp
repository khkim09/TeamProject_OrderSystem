#include "OrderList.h"
#include "MenuList.h"
#include "CustomerList.h"
using namespace std;

Menu addMenuFromInput() {
    string name;
    int price;
    string introduce;

    cout << "--------메뉴 이름 입력---------" << endl;
    getline(cin, name);
    cout << "--------메뉴 가격 입력---------" << endl;
    cin >> price;
    cin.ignore();
    cout << "--------메뉴 소개 입력---------" << endl;
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

    cout << "주문자 성함 : ";
    getline(cin, name);
    cout << "주문자 생년월일 (YY-MM-DD) : ";
    getline(cin, birth);
    cout << "주문자 전화번호 (010-XXXX-XXXX) : ";
    getline(cin, phoneNum);
    cout << "배송 받을 주소 : ";
    getline(cin, address);
    cout << "주문 시 요청사항 : ";
    getline(cin, request);
    cout << "결제수단 (카드 / 현금) : ";
    getline(cin, paymentMethod);

    return Customer(name, birth, phoneNum, address, request, paymentMethod);
}

void menu() {
    cout << "******************************" << endl;
    cout << "-----1. 주문자 정보 추가------" << endl;
    cout << "-----2. 주문자 정보 삭제------" << endl;
    cout << "-----3. 주문자 정보 수정------" << endl;
    cout << "-----4. 주문자 정보 출력------" << endl;
    cout << "---5. 모든 주문자 정보 출력---" << endl;
    cout << "---6. 모든 주문자 정보 삭제---" << endl;
    cout << "------프로그램 종료 (Q/q)-----" << endl;
    cout << "******************************" << endl;
}

bool isquit(char choice) {
    if (choice == 'q' || choice == 'Q')
        return true;
    return false;
}

int main() {
    //주문정보읽기
    OrderList orderList;
    orderList.read_Orderlist_file("orders.txt"); // 기존 주문 정보 읽기
    
    //메뉴판 읽기
    MenuList menulist;
    menulist.readFromFile("Menu_List.txt");

    //고객정보 읽기
    CustomerList customerList;
    customerList.loadFromFile("Customers.txt");

    bool loop;

    while (true) {
        int job;

        cout << "---------1.메뉴판---------" << endl;
        cout << "------2.주문자 정보-------" << endl;
        cout << "-------3.주문 화면--------" << endl;
        cout << "-----4.프로그램 종료------" << endl;

        cin >> job;

        if (job == 1) {
            loop = true;

            int order;
            string name, line;

            while (loop) {
                cout << "----------메뉴판----------" << endl;
                cout << "------메뉴 추가 = 1-------" << endl;
                cout << "------메뉴 삭제 = 2-------" << endl;
                cout << "----메뉴 요소 변경 = 3----" << endl;
                cout << "-----메뉴판 열기 = 4------" << endl;
                cout << "-메뉴판 저장 및 종료 = 5--" << endl;

                cout << "--------명령 입력---------" << endl;

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
                    cout << "--------메뉴 이름 입력---------" << endl;
                    getline(cin, name);

                    menulist.removeMenu(name);
                    cout << endl;
                    break;
                }
                case 3: {
                    cout << "--------메뉴 이름 입력---------" << endl;
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
                    cout << "-------잘못된 명령 입력--------" << endl << endl;
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
                cout << "실행할 메뉴 번호를 입력해주세요 : ";
                cin >> choice;
                cin.ignore(); // enter 키 날리기

                switch (choice) {
                case '1': {
                    Customer customer = createCustomerFromInput();
                    customerList.addCustomer(customer);
                    break;
                }
                case '2': {
                    string delPhoneNum;
                    cout << "삭제할 주문자의 전화번호를 입력해주세요 (010-XXXX-XXXX) : ";
                    getline(cin, delPhoneNum);
                    if (customerList.deleteCustomer(delPhoneNum))
                        cout << "주문자 정보 삭제가 완료되었습니다." << endl;
                    else
                        cout << "해당 주문자 정보를 찾을 수 없습니다." << endl;
                    cout << endl;
                    break;
                }
                case '3': {
                    string phoneNum, newValue;
                    int field;
                    cout << "수정할 주문자의 전화번호를 입력해주세요 (010-XXXX-XXXX) : ";
                    getline(cin, phoneNum);
                    cout << "수정할 정보를 선택해주세요 (1 : 전화번호 | 2 : 배송 받을 주소 | 3 : 요청사항 | 4 : 결제수단) : ";
                    cin >> field;
                    cin.ignore();
                    cout << "업데이트 할 정보를 입력해주세요 : ";
                    getline(cin, newValue);
                    if (customerList.updateCustomer(phoneNum, field, newValue))
                        cout << "주문자 정보 수정이 완료되었습니다." << endl;
                    else
                        cout << "해당 주문자 정보가 없거나 수정할 정보 입력이 잘못되었습니다." << endl;
                    cout << endl;
                    break;
                }
                case '4': {
                    string findPhoneNum;
                    cout << "출력할 주문자의 전화번호를 입력해주세요 (010-XXXX-XXXX) : ";
                    getline(cin, findPhoneNum);
                    if (!customerList.printCustomerInfo(findPhoneNum))
                        cout << "주문자 정보를 찾을 수 없습니다." << endl;
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
                    cout << "정말로 모든 주문자 정보를 삭제하시겠습니까? (y/n) : ";
                    cin >> accept;
                    cin.ignore();

                    if (accept == 'y') {
                        customerList.clearAllCustomers();
                        cout << "모든 주문자 정보가 삭제되었습니다." << endl;
                    }
                    cout << endl;
                    break;
                }
                case 'q': case 'Q': {
                    customerList.saveToFile("Customers.txt");
                    cout << "주문자 정보 업데이트 완료" << endl;
                    cout << "프로그램 종료중..." << endl << endl;
                    loop = false;
                    break;
                }
                default:
                    cout << "잘못된 명령 선택입니다." << endl << endl;
                }
            }
        }
        else if (job == 3) {
            loop = true;
            int choice;

            while (loop) {
                cout << endl;
                cout << "1. 주문 시작하기" << endl;
                cout << "2. 주문 메뉴 변경 및 추가하기" << endl;
                cout << "3. 주문 삭제하기" << endl;
                cout << "4. 주문 완료하기" << endl;
                cout << "5. 주문서 출력하기" << endl;
                cout << "6. 주문 건 수 확인하기" << endl;
                cout << "7. 남은 주문 건 수 확인하기" << endl;
                cout << "8. 종료하기" << endl;
                cout << endl;
                cout << "실행할 메뉴 번호를 입력해주세요 : ";
                cin >> choice;
                cin.ignore();

                switch (choice) {
                case 1: {
                    orderList.new_order(menulist, customerList);
                    cout << endl;
                    break;
                }
                case 2: {
                    cout << "주문번호를 입력해주세요.";
                    int orderN;
                    cin >> orderN;
                    orderList.change_order(orderN, menulist);
                    break;
                }
                case 3: {
                    cout << "주문번호를 입력해주세요.";
                    int orderN;
                    cin >> orderN;
                    orderList.delete_order(orderN);
                    break;
                }
                case 4: {
                    cout << "주문번호를 입력해주세요.";
                    int orderN;
                    cin >> orderN;
                    orderList.complete_order(orderN);
                    break;
                }
                case 5: {
                    cout << "주문번호를 입력해주세요.";
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
                    orderList.write_Orderlist_file("orders.txt"); // 주문 정보 파일에 저장
                    cout << "주문시스템을 종료합니다." << endl;
                    loop = false;
                    break;
                }
                default:
                    cout << "잘못된 번호입니다. 다시 입력해주세요" << endl;
                }
                cout << endl;
            }
        }
        else if (job == 4) {
            cout << "--프로그램을 종료합니다.--" << endl;
            break;
        }
    }

    return 0;
}