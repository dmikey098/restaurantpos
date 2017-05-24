#pragma once
#include "menuItem.h"
#include "utility.h"

class Order {
public:
	enum STATUS { OPEN, CLOSED, COMPLETED };
	Order();
	Order(int);
	~Order();

	//mutators
	void deleteItem(int);
	void addItem(menuItem);
	void setStatus(int);

	//accessors
	int getSize();
	int getStatus();
	string outputString(int);
	double getTotal();
	void viewItems();
	
private:
	STATUS orderStatus;
	//int orderStatus;
	double orderTotal;
	vector<menuItem> items;
};




