/*

�ֹ��� list Ŭ����
�ֹ������� ��Ƶΰ� �ֹ� �Ǽ��� �����Ѵ�.

*/
#pragma once
#include <vector>
#include <string>
#include "Menu.h"
#include "Order.h"
#include "Time.h"
#include "MenuList.h"
#include "CustomerList.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

class OrderList { 
private:
	vector<Order> Orders;

	//���� ���
	static int totalOrderCount; //�� �ֹ� �Ǽ�
	static int completeOrderCount;//�Ϸ�� �ֹ� �Ǽ�
	static int remainingOrderCount;//���� �ֹ� �Ǽ�

public:
	//Orderlist ���� �б�
	void read_Orderlist_file(const string& filename);
	//Orderlist ���� ����
	void write_Orderlist_file(const string& filename);

	void new_order(MenuList& menulist,CustomerList& customerlist); //���ο� �ֹ�. ���ο� �ֹ� ��ȣ�� �ο��Ͽ� Orders�� �߰��ϰ� �ֹ��޴� ��϶��� �Է¹޴´�.
	void change_order(int orderN, MenuList& menulist); //�ֹ� �޴� ������ �����ϰų� �߰��Ѵ�.
	void delete_order(int orderN); //�ֹ����� �ƿ� ����(!complete�϶��� ����)
	void complete_order(int orderN); //�ֹ� �Ϸ� �˸� ���
	void print_order(int orderN); //orderN���� �ֹ��� ����Ѵ�.
	void show_order_count(); //�ֹ��Ǽ� ���� ��� ���
	void show_remaining_order(); //���� �ֹ� �Ǽ� ���

};
