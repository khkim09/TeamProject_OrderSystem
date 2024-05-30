#include "MenuList.h"
#include <iostream>

// �޴��ǿ� �޴� �߰�
void MenuList::addMenu(Menu newMenu) {
	List.emplace_back(newMenu);
}

// �޴��ǿ��� �޴� ����
void MenuList::removeMenu(string findMenuName) {
	vector<Menu>::iterator iter;

	for (iter = List.begin(); iter != List.end();) { // �޴����� ó������ ������
		if (findMenuName.compare(iter->getName()) == 0) { // ������ �޴��� �̸��� ã�� ���
			iter = List.erase(iter);
		}
		else {
			iter++;
		}
	}

	return;
}

// �޴��ǿ��� ������ �޴� ���� ��� ����
void MenuList::changeMenu(string findMenuName) {
	vector<Menu>::iterator iter;

	for (iter = List.begin(); iter != List.end();) { // �޴����� ó������ ������
		if (findMenuName.compare(iter->getName()) == 0) { // ������ �޴��� �̸��� ã�� ���
			cout << "------���� ��� ����------" << endl;
			cout << "----�޴� �̸� ���� = 1----" << endl;
			cout << "----�޴� ���� ���� = 2----" << endl;
			cout << "----�޴� �Ұ� ���� = 3----" << endl;

			int order, price;
			string name, introduce;

			cin >> order;
			cin.ignore(); // 05.30 modified

			if (order == 1) {
				cout << "-----������ �̸� �Է�-----" << endl;
				getline(cin, name);

				iter->setName(name);

				break;
			}
			else if (order == 2) {
				cout << "-----������ ���� �Է�-----" << endl;
				cin >> price;

				iter->setPrice(price);

				break;
			}
			else if (order == 3) {
				cout << "-----������ �Ұ� �Է�-----" << endl;
				getline(cin, introduce);

				iter->setIntroduce(introduce);

				break;
			}
			else {
				cout << "-------�߸��� �Է�--------" << endl;
				break;
			}
		}
		else {
			iter++;
		}
	}

	return;
}

// �޴��� ���
void MenuList::showList() {
	vector<Menu>::iterator iter;
	cout << "--------------------- �޴� ----------------------" << endl;
	for (iter = List.begin(); iter != List.end(); iter++) { // �޴����� ó������ ������
		cout << iter->getName() << " " << iter->getPrice() << " " << iter->getIntroduce() << endl;
	}
	cout << "-----------------------------------------------" << endl;
	return;
}


// �޴��� ���ۺκ� ��ȯ
vector<Menu>::iterator MenuList::getBegin() {
	return List.begin();
}

// �޴��� ���κ� ��ȯ
vector<Menu>::iterator MenuList::getEnd() {
	return List.end();
}

// �޴����� ��ȯ
vector<Menu>& MenuList::getList() {
	return List;
}

// ���Ϸκ��� �޴��� �о���̱�
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

// �޴��� ���Ͽ� ����
void MenuList::saveToFile(const string& filename) {
	ofstream F(filename);
	if (!F.is_open()) {
		cerr << "Error opening file : " << filename << endl;
		return;
	}
	
	vector<Menu>::iterator iter;

	for (iter = getBegin(); iter != getEnd(); iter++) { // �޴����� ó������ ������
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