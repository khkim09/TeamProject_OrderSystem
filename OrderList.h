/*

�ֹ��� list Ŭ����
�ֹ������� ��Ƶΰ� �ֹ� �Ǽ��� �����Ѵ�.

*/
#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "Menu.h"
#include "Order.h"
#include "Time.h"
#include "MenuList.h"
#include "CustomerList.h"


using namespace std;

class OrderList {
private:
	//���
	vector<Order> Orders; //�ֹ��� ���

	//���� ���
	static int totalOrderCount; //�� �ֹ� �Ǽ�
	static int completeOrderCount;//�Ϸ�� �ֹ� �Ǽ�
	static int remainingOrderCount;//���� �ֹ� �Ǽ�

public:
	//��� �Լ�
	void read_Orderlist_file(const string& filename);	//Orderlist ���� �б�
	void write_Orderlist_file(const string& filename);	//Orderlist ���� ����

	bool new_order(MenuList& menulist, CustomerList& customerlist); //���ο� �ֹ�
	void change_order(int orderN, MenuList& menulist); //�ֹ� �޴� ������ ����, �߰�
	void delete_order(int orderN); //�ֹ��� �ƿ� ����(!complete�϶��� ����)
	void complete_order(int orderN); //�ֹ� �Ϸ� �˸� ���
	void print_order(int orderN); //�ֹ��� ���
	void show_order_count(); //�ֹ��Ǽ� ���� ��� ���
	void show_remaining_order(); //���� �ֹ� �Ǽ� ���
};
