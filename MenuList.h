#pragma once
#include <vector>
#include <fstream> 	/*임의로 추가한 곳!!!!!*/
#include "Menu.h"

class MenuList { // 메뉴판
private : 
	vector<Menu> List; // 메뉴 목록

public: 
	void addMenu(Menu newMenu);
	void removeMenu(string findMenuName);
	void changeMenu(string findMenuName);
	void showList();
	vector<Menu>::iterator getBegin();
	vector<Menu>::iterator getEnd();




	/*임의로 추가한 곳!!!!!*/
	vector<Menu>& getList();
	void readFromFile(const string& filename);

	void saveToFile(const string& filename);
};