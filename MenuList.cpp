#include "MenuList.h"
#include <iostream>

// 메뉴판에 메뉴 추가
void MenuList::addMenu(Menu newMenu) {
	List.emplace_back(newMenu);
}

// 메뉴판에서 메뉴 제거
void MenuList::removeMenu(string findMenuName) {
	vector<Menu>::iterator iter;

	for (iter = List.begin(); iter != List.end();) { // 메뉴판의 처음부터 끝까지
		if (findMenuName.compare(iter->getName()) == 0) { // 삭제할 메뉴의 이름을 찾은 경우
			iter = List.erase(iter);
		}
		else {
			iter++;
		}
	}

	return;
}

// 메뉴판에서 임의의 메뉴 구성 요소 변경
void MenuList::changeMenu(string findMenuName) {
	vector<Menu>::iterator iter;

	for (iter = List.begin(); iter != List.end();) { // 메뉴판의 처음부터 끝까지
		if (findMenuName.compare(iter->getName()) == 0) { // 변경할 메뉴의 이름을 찾은 경우
			cout << "------변경 요소 선택------" << endl;
			cout << "----메뉴 이름 변경 = 1----" << endl;
			cout << "----메뉴 가격 변경 = 2----" << endl;
			cout << "----메뉴 소개 변경 = 3----" << endl;

			int order, price;
			string name, introduce;

			cin >> order;
			cin.ignore(); // 05.30 modified

			if (order == 1) {
				cout << "-----변경할 이름 입력-----" << endl;
				getline(cin, name);

				iter->setName(name);

				break;
			}
			else if (order == 2) {
				cout << "-----변경할 가격 입력-----" << endl;
				cin >> price;

				iter->setPrice(price);

				break;
			}
			else if (order == 3) {
				cout << "-----변경할 소개 입력-----" << endl;
				getline(cin, introduce);

				iter->setIntroduce(introduce);

				break;
			}
			else {
				cout << "-------잘못된 입력--------" << endl;
				break;
			}
		}
		else {
			iter++;
		}
	}

	return;
}

// 메뉴판 출력
void MenuList::showList() {
	vector<Menu>::iterator iter;
	cout << "--------------------- 메뉴 ----------------------" << endl;
	for (iter = List.begin(); iter != List.end(); iter++) { // 메뉴판의 처음부터 끝까지
		cout << iter->getName() << " " << iter->getPrice() << " " << iter->getIntroduce() << endl;
	}
	cout << "-----------------------------------------------" << endl;
	return;
}


// 메뉴판 시작부분 반환
vector<Menu>::iterator MenuList::getBegin() {
	return List.begin();
}

// 메뉴판 끝부분 반환
vector<Menu>::iterator MenuList::getEnd() {
	return List.end();
}

// 메뉴판을 반환
vector<Menu>& MenuList::getList() {
	return List;
}

// 파일로부터 메뉴판 읽어들이기
void MenuList::readFromFile(const string& filename) {
	ifstream file(filename);
	if (!file.is_open()) {
		cerr << "File error: could not open " << filename << endl;
		return;
	}

	string name;
	int price;
	string introduce;
	string line;

	while (getline(file, line)) {
		name = line;
		getline(file, line);
		price = stoi(line);
		getline(file, line);
		introduce = line;

		Menu newMenu(name, price, introduce);
		addMenu(newMenu);
	}

	file.close();
}

// 메뉴판 파일에 저장
void MenuList::saveToFile(const string& filename) {
	ofstream F(filename);
	if (!F.is_open()) {
		cerr << "Error opening file : " << filename << endl;
		return;
	}
	
	vector<Menu>::iterator iter;

	for (iter = getBegin(); iter != getEnd(); iter++) { // 메뉴판의 처음부터 끝까지
		if (iter == getBegin()) {
			F << iter->getName();
		}
		else {
			F << "\n" << iter->getName();
		}
		F << "\n" << iter->getPrice();
		F << "\n" << iter->getIntroduce();
	}

	F.close();
}