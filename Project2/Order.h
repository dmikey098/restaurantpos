#pragma once
#include "menuItem.h"
#include <math.h>

class Order {
public:
	enum STATUS { OPEN, CLOSED, COMPLETED };
	Order();
	Order(STATUS);
	~Order();

	//mutators
	void deleteItem(int);
	void addItem(menuItem);
	void setStatus(STATUS);

	//accessors
	int getSize();
	int getStatus();
	string outputString(int);
	double getTotal();
	void viewItems();
	
private:
	STATUS orderStatus;
	double orderTotal;
	vector<menuItem> items;
};




