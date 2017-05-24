#pragma once
#include <string>
#include <set>
#include <map>
#include "utility.h"
using namespace std;

class menuItem {
public:
	menuItem(string name, string description, double price);
	menuItem();
	~menuItem();
	string getName();
	string toString();
	virtual string outputString() const;
	bool menuItem::operator==(const menuItem& other);
	double getPrice();
	void setName(string name);
	void setDescription(string description);
	void setPrice(double price);

protected:
	double price;
	string name;
	string description;

};

class Entree : public menuItem {
public:
	Entree() {}

	Entree(string name, string description, double price) : menuItem(name, description, price) {
		this->name = name;
		this->description = description;
		this->price = price;
	}
};

//class Sandwich : public Entree {
//public:
//	enum SandwichTopping {
//		PATTY = 1, CHKPATTY, CHEESE, LETTUCE, TOMATO, ONION, PICKLE, MAYO, MUSTARD, KETCHUP
//	};
//	vector<string> SandwichToppings { "", "Beef Patty", "Chicken Patty", "American Cheese", "Lettuce", "Tomato", "Onion", "Pickle", 
//		"Mayo", "Mustard", "Ketchup" };
//
//	vector<string> toppings;
//	map<SandwichTopping, double> topping_list = {
//		{ PATTY, 2.00 },
//		{ CHKPATTY, 2.50 },
//		{ CHEESE, 0.69 },
//		{ LETTUCE, 0 },
//		{ TOMATO, 0 },
//		{ ONION, 0 },
//		{ PICKLE, 0 },
//		{ MAYO, 0 },
//		{ MUSTARD, 0 },
//		{ KETCHUP, 0 }
//	};
//
//	Sandwich(string name, string description, double price) : Entree(name, description, price) {
//		this->name = name;
//		this->description = description;
//		this->price = price;
//	}
//
//	void addTopping() {
//		string str;
//
//		viewTitle("Toppings");
//		for (int i = 1; i < SandwichToppings.size(); i++) {
//			centerText(to_string(i) + ". " + SandwichToppings[i], 1);
//		}
//		int option = getIntegerInput("Select a topping: ");
//
//		
//		centerText("1. Extra", 1);
//		centerText("2. None", 1);
//		int option2 = getIntegerInput("Make a selection: ");
//		if (option2 == 1) { 
//			str = "Extra"; 
//		} else if (option2 == 0) {
//		} else { 
//			str = "No"; 
//		}
//
//		toppings.push_back(str + " " + SandwichToppings[option]);
//		price += topping_list[SandwichTopping(option)];
//
//	}
//
//	string outputString() {
//		return "," + name + "," + description + "," + to_string(price) + ",1" ;
//	}
//
//};

class Appetizer : public menuItem {
public:
	Appetizer(string name, string description, double price) : menuItem(name, description, price) {
		this->name = name;
		this->description = description;
		this->price = price;
	}
};

class Side : public menuItem {
public:
	Side(string name, string description, double price) : menuItem(name, description, price) {
		this->name = name;
		this->description = description;
		this->price = price;
	}
};

class Beverage : public menuItem {
public:
	Beverage(string name, string description, double price) : menuItem(name, description, price) {
		this->name = name;
		this->description = description;
		this->price = price;
	}
};

