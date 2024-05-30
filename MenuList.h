#pragma once
#include <vector>
#include <fstream> 	/*���Ƿ� �߰��� ��!!!!!*/
#include "Menu.h"

class MenuList { // �޴���
private : 
	vector<Menu> List; // �޴� ���

public: 
	void addMenu(Menu newMenu);
	void removeMenu(string findMenuName);
	void changeMenu(string findMenuName);
	void showList();
	vector<Menu>::iterator getBegin();
	vector<Menu>::iterator getEnd();




	/*���Ƿ� �߰��� ��!!!!!*/
	vector<Menu>& getList();
	void readFromFile(const string& filename);

	void saveToFile(const string& filename);
};