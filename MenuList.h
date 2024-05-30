#pragma once
#include <vector>
#include <fstream>
#include "Menu.h"

class MenuList { // �޴���
private:
	vector<Menu> List; // �޴� ���

public:
	void addMenu(Menu newMenu); // �޴��ǿ� �޴� �߰�
	void removeMenu(string findMenuName); // �޴��ǿ��� �޴� ����
	void changeMenu(string findMenuName); // �޴��ǿ��� ������ �޴� ���� ��� ����
	void showList(); // �޴��� ���
	
	vector<Menu>::iterator getBegin(); // �޴��� ���ۺκ� ��ȯ
	vector<Menu>::iterator getEnd(); // �޴��� ���κ� ��ȯ
	vector<Menu>& getList(); // �޴����� ��ȯ
	
	void readFromFile(const string& filename); // ���Ϸκ��� �޴��� �о���̱�
	void saveToFile(const string& filename); // �޴��� ���Ͽ� ����
};