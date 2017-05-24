#include "Order.h"

Order::Order() {
	orderTotal = 0.00;
	orderStatus = OPEN;
}

Order::Order(STATUS status) {

	orderStatus = status;
	orderTotal = 0.00;
}

Order::~Order() {
}

void Order::viewItems()
{
	for (int i = 0; i < items.size(); i++) {
		centerText(to_string(i + 1) + ". " + items[i].toString(), 1);
	}
}

void Order::addItem(menuItem item) {
	items.push_back(item);
	orderTotal += item.getPrice();
}

void Order::setStatus(STATUS status) {
	orderStatus = status;
}

void Order::deleteItem(int option) {
	centerText(items[option - 1].toString(),1);

	orderTotal -= items[option - 1].getPrice();
	items.erase(items.begin() + (option - 1));
}

int Order::getSize() {
	return items.size();
}

int Order::getStatus()
{
	return orderStatus;
}

string Order::outputString(int orderNumber)
{
	string str = "";
	for (int i = 0; i < items.size(); i++) {
		str += to_string(orderNumber) + items[i].outputString() + "," + to_string(orderStatus) + "\n";
	}
	return str;
}

double Order::getTotal()
{
	return orderTotal;
}

