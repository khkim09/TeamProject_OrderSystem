/*

�ֹ� Order Class
�ֹ��� ���õ� ������ �ѹ�, ��� �Լ��� ������ ��� �ִ�.

*/
#pragma once
#include <iostream>
#include <vector>
#include "Time.h"
#include "OrderMenu.h"
#include "MenuList.h"
using namespace std;


class Order {
private:
	//���
	int order_number; //�ֹ���ȣ
	Time order_time;  //�ֹ� �ð�

	vector<OrderMenu> order_items; //�ֹ��� �޴� �� ����
	
	int total; //�ֹ� �ݾ�

	bool member;//��� ����
	            //����� 5%����
	bool discount;  //���� ����
	                //�ֹ��ݾ��� 5���� �̻��� �� 5% �߰� ����
	                //����̰� �ֹ��ݾ� ��� ������ 10% ����
	int receipt_total; //���� ���� �ݾ�

	bool complete; //�ֹ��� �Ϸ� ����
	Time complete_time; //�ֹ� �Ϸ� �ð�

public:
	//������
	Order();
	Order(int ordernumber);

	void Change_ordermenu(MenuList&menuList); //�޴� ��� ����
	void Add_ordermenu(const string& name, int count, MenuList& menuList);// �޴� �� ���� �߰�
	void Add_ordermenu(string name, int count, int price);
	void delete_ordermenu(string name, int count); //�޴� �� ���� ����
	void Check_order() const; // �ֹ� ��ü������ Ȯ��
	void Check_order_items() const; //�ֹ� �׸� Ȯ���ϱ�
	void Complete_order(); // �ֹ� �Ϸ�
	bool isComplete() const; // �ֹ� �Ϸ� ���� Ȯ��
	bool is_order_items_empty() const;
	bool isMember() const;
	vector<OrderMenu>& getItems(); // �ֹ� �׸�� ��������

	int get_order_number() const;
	int get_total() const;
	int get_receipt_total() const;
	Time get_order_time() const;
	Time get_complete_time() const;

	void set_total(int total);
	void set_receipt_total(int receiptTotal);
	void set_complete(bool complete);
	void set_order_time(Time& time);
	void set_complete_time(Time& time);
	void setMember(bool isMember);

	~Order(); // �Ҹ���

private:
	void calculate_price(); //���� ���
};