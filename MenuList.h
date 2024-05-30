#pragma once
#include <vector>
#include <fstream>
#include "Menu.h"

class MenuList { // 메뉴판
private:
	vector<Menu> List; // 메뉴 목록

public:
	void addMenu(Menu newMenu); // 메뉴판에 메뉴 추가
	void removeMenu(string findMenuName); // 메뉴판에서 메뉴 제거
	void changeMenu(string findMenuName); // 메뉴판에서 임의의 메뉴 구성 요소 변경
	void showList(); // 메뉴판 출력
	
	vector<Menu>::iterator getBegin(); // 메뉴판 시작부분 반환
	vector<Menu>::iterator getEnd(); // 메뉴판 끝부분 반환
	vector<Menu>& getList(); // 메뉴판을 반환
	
	void readFromFile(const string& filename); // 파일로부터 메뉴판 읽어들이기
	void saveToFile(const string& filename); // 메뉴판 파일에 저장
};