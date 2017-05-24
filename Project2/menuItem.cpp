#include "menuItem.h"

menuItem::menuItem(string name, string description, double price) {
	this->name = name;
	this->description = description;
	this->price = price;
}

menuItem::menuItem() {}
menuItem::~menuItem() {}

string menuItem::getName() {
	return name;
}
string menuItem::toString() {
	return name + " " + to_string(price);
}
string  menuItem::outputString() const  {
	return "," + name + "," + description + "," + to_string(price);
}
bool menuItem::operator==(const menuItem& other) {
	return name == other.name;
}
double menuItem::getPrice() {
	return price;
}
void menuItem::setName(string name) {
	this->name = name;
}
void menuItem::setDescription(string description) {
	this->description = description;
}
void menuItem::setPrice(double price) {
	this->price = price;
}