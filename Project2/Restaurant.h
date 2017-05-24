#pragma once
#include "Order.h"
#include <fstream>
#include <iterator>
#include <cmath>


class Restaurant
{
public:
	Restaurant();
	~Restaurant();

	//Menu items
	void loadMenu();
	void saveMenu();
	void addToMenu(int, string, string, double);
	void addMenuItem();
	void deleteMenuItem();
	void viewMenuItems(int);
	void editMenuItem();

	//Orders
	void viewOrders(int);
	void newOrder();
	void addOrderItem(int, int);
	void viewOrderDetail(int);
	void viewClosedOrder(int);
	void viewCompletedOrder(int);
	void cashOutOrder(int);
	void addToCash(double);
	void removeFromCash(double);
	void saveOrders();
	void loadOrders();
	void purgeOrders();
	void addBurger(int);

private:
	vector<vector<menuItem>> menu;
	map<int, Order> orders;
	double registerCash;
	int orderNumber;
};

