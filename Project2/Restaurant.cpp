#include "Restaurant.h"

Restaurant::Restaurant() : menu(5)
{
	registerCash = 500.00; //
	orders[0] = Order(); //first order (order 0) is not used
	loadMenu();  //loads menu from external file menu.txt
	loadOrders(); //load order history (open, closed, completed)
}

Restaurant::~Restaurant()
{
	saveMenu(); //saves menu to external file on exit
	saveOrders(); //save orders to external file
}

void Restaurant::loadMenu() {
	ifstream myfile("menu.txt");
	string name, description, line, strPrice, strType, strSubType;
	double price;
	int type;

	if (myfile) {
		while (getline(myfile, line)) {
			stringstream linestream(line);

			getline(linestream, strType, ',');
			getline(linestream, name, ',');
			getline(linestream, description, ',');
			getline(linestream, strPrice, ',');

			price = stod(strPrice);
			type = stoi(strType);

			addToMenu(type, name, description, price);
		}
	}
	else {
		centerText("File not found", 1);
	}
	myfile.close();
}

void Restaurant::saveMenu() {
	ofstream outfile;
	outfile.open("./menu.txt");
	for (int i = 1; i < menu.size(); i++) {
		for (int n = 0; n < menu[i].size(); n++) {
			outfile << to_string(i) << menu[i][n].outputString() << endl;
		}
	}
	outfile.close();
}

void Restaurant::addToMenu(int option, string name, string description = "", double price = 0)
{
	switch (option) {
	case 1:
		menu[1].push_back(Entree(name, description, price));
		break;
	case 2:
		menu[2].push_back(Appetizer(name, description, price));
		break;
	case 3:
		menu[3].push_back(Side(name, description, price));
		break;
	case 4:
		menu[4].push_back(Beverage(name, description, price));
		break;		
	default:
		break;
	}
}

void Restaurant::addMenuItem() {
	int option = viewMenu(3, true);
	addToMenu(option, getStringInput("Item name: "), getStringInput("Item description: "), getDoubleInput("Item price: "));
}

void Restaurant::deleteMenuItem() {
	int menuType = viewMenu(3, true), option = 0;

	while (true) {
		viewMenuItems(menuType);
		centerText("Please select item to delete or press 0 to return: ", 1);
		cin >> option;

		if (option != 0) {
			if (confirm("Are you sure you want to delete this order(y/n)?")) {
				menu[menuType].erase(menu[menuType].begin() + (option - 1));
				centerText("Item deleted...", 1);
				pause();
			}
		}
		else {
			return;
		}
	}
}

void Restaurant::viewMenuItems(int type)
{
	string strArray[] = { "", "Entrees", "Appetizers", "Sides", "Beverages" };
	viewTitle(strArray[type]);
	for (int i = 0; i < menu[type].size(); i++) {
		centerText(to_string(i + 1) + ". " + menu[type][i].getName(), 1);
	}
}

void Restaurant::editMenuItem() {
	bool done = false;
	int menuType = viewMenu(3, true), menuOption = 0, option = 0;
	string str;

	while (!done) {
		viewMenuItems(menuType);
		centerText("Please select item to edit or press 0 to return: ", 1);
		cin >> menuOption;

		if (menuOption != 0) {
			option = viewMenu(5, true);
			switch (option) {
				case 0:
					done = true;
					break;
				case 1:
					menu[menuType][menuOption - 1].setName(getStringInput("Please enter new name for this item: "));
					break;
				case 2:
					menu[menuType][menuOption - 1].setDescription(getStringInput("Please enter new description for this item: "));
					break;
				case 3:
					menu[menuType][menuOption - 1].setPrice(getDoubleInput("Please enter new price for this item: "));
					break;
			}
		}
		else {
			done = true;
		}
	}
	return;
}

void Restaurant::viewOrders(int status) {
	bool done = false;
	int option;
	string strArray[] = { "Open", "Closed", "Completed" };

	while (!done) {
		viewTitle(strArray[status] + " Orders");

		for (int i = 1; i < orders.size(); i++) {
			if (orders[i].getStatus() == status) {
				centerText("Order " + to_string(i), 1);
			}
		}

		centerText("Input 0 to return to previous menu", 2);
		centerText("Make a selection: ", 1);
		cin >> option;

		if (option > 0 && option < orders.size()) {
			if (orders[option].getStatus() == 0){
				viewOrderDetail(option);
			} else if (orders[option].getStatus() == 1){
				if (confirm("The selected order is closed. Would you still like to view it?(y/n)")) { viewClosedOrder(option); }
			} else if (orders[option].getStatus() == 2) {
				if (confirm("The selected order is completed. Would you still like to view it?(y/n)")) { viewCompletedOrder(option); }
			}
		}
		else if (option == 0) {
			done = true;
		}
	}
}

void Restaurant::addOrderItem(int orderNum, int menuType) {
	int option = 0;
	viewMenuItems(menuType);
	centerText("Make a selection: ", 1);
	cin >> option;

	if ((option - 1) > -1 && (option - 1) < menu.size()) {
		orders[orderNum].addItem(menu[menuType][option - 1]);
	}
}

void Restaurant::viewClosedOrder(int orderNum){
	bool done = false;
	double total = orders[orderNum].getTotal();
	int menuOption = -1, option = -1;

	while (!done) {
		viewTitle("Order " + to_string(orderNum) + " (Closed)");

		switch (menuOption) {
		case -1: 
			orders[orderNum].viewItems();
			centerText("Total: " + to_string(total) + "\n", 1);
			menuOption = viewMenu(6, false);
			break;
		case 0:
			done = true;
			break;
		case 1:
			option = viewMenu(1, true);
			addOrderItem(orderNum, option);
			menuOption = -1;
			break;
		case 2:
			orders[orderNum].viewItems();
			centerText("Select item to delete from order: ", 1);
			cin >> option;

			if (option > 0 && option <= orders[orderNum].getSize()) {
				orders[orderNum].deleteItem(option);
				menuOption = -1;
			} else if (option == 0) {
				menuOption = -1;
			}
			break;
		case 3:
			if (confirm("Are you sure you want to reopen this order?(y/n)")) {
				orders[orderNum].setStatus(Order::OPEN);
			}
			menuOption = -1;
			break;
		}
	}
}

void Restaurant::viewCompletedOrder(int orderNum) {
	bool done = false;
	double total = orders[orderNum].getTotal();
	int menuOption = -1, option = -1;

	while (!done) {
		viewTitle("Order " + to_string(orderNum) + " (Completed)");

		switch (menuOption) {
		case -1:
			orders[orderNum].viewItems();
			centerText("Total: " + to_string(total) + "\n", 1);
			menuOption = viewMenu(7, false);
			break;
		case 0:
			done = true;
			break;
		case 1:
			option = viewMenu(1, true);
			addOrderItem(orderNum, option);
			menuOption = -1;
			break;
		case 2:
			orders[orderNum].viewItems();
			centerText("Select item to delete from order: ", 1);
			cin >> option;

			if (option > 0 && option <= orders[orderNum].getSize()) {
				orders[orderNum].deleteItem(option);
				menuOption = -1;
			}
			else if (option == 0) {
				menuOption = -1;
			}
			break;
		case 3:
			if (confirm("Are you sure you want to reopen this order?(y/n)")) {
				orders[orderNum].setStatus(Order::OPEN);
			}
			menuOption = -1;
			break;
		case 4:
			if (confirm("Are you sure you want to refund this order?(y/n)")) {
				removeFromCash(total);
				orders[orderNum].setStatus(Order::CLOSED);
				centerText(to_string(total) + " was refunded to customer. Order status set to closed.", 1);
				pause();
				menuOption = -1;
			}
			menuOption = -1;
			break;
		}
	}
}

void Restaurant::viewOrderDetail(int orderNum) {
	bool done = false;
	int menuOption = -1, option = -1;

	while (!done) {
		viewTitle("Order " + to_string(orderNum));

		switch (menuOption) {
		case -1: {
			orders[orderNum].viewItems();
			centerText("Total: " + to_string(orders[orderNum].getTotal()) + "\n", 1);
			menuOption = viewMenu(4, false);
			break;
		}
		case 0:
			done = true;
			break;
		case 1:
			option = viewMenu(1, true);
			addOrderItem(orderNum, option);
			menuOption = -1;
			break;
		case 2:
			orders[orderNum].viewItems();
			centerText("Select item to delete from order: ", 1);
			cin >> option;

			if (option > 0 && option <= orders[orderNum].getSize()) {
				orders[orderNum].deleteItem(option);
				menuOption = -1;
			}
			else if (option == 0) {
				menuOption = -1;
			}
			else {
				cout << "Invalid input" << endl;
			}
			break;
		case 3:
			cashOutOrder(orderNum);
			done = true;
			break;
		case 4:
			if (confirm("Are you sure you want to delete this order(y/n)?")) {
				orders[orderNum].setStatus(Order::CLOSED);
				centerText("Order deleted...", 1);
				pause();
				done = true;
			}
			menuOption = -1;
			break;
		case 5:
			addBurger(orderNum);
			menuOption = -1;
		}
	}
}

void Restaurant::cashOutOrder(int orderNum)
{
	double amount, change;

	centerText("Total is " + to_string(orders[orderNum].getTotal()), 1);
	centerText("Enter amount recieved from customer: ", 1);
	cin >> amount;

	if (amount < orders[orderNum].getTotal()) {
		centerText("Not enough received...", 1);
	}
	else {
		change = amount - orders[orderNum].getTotal();
		centerText("Change is $" + to_string(change), 1);
		orders[orderNum].setStatus(Order::COMPLETED);
		addToCash(amount);
		pause();
	}
}

void Restaurant::addToCash(double cash)
{
	registerCash += cash;
}

void Restaurant::removeFromCash(double cash)
{
	registerCash -= cash;
}

void Restaurant::newOrder() {
	bool done = false;
	int option = 0;
	orders[orderNumber] = Order();

	while (!done) {
		option = viewMenu(1, true);

		if (option > 0 && option < menu.size()) {
			addOrderItem(orderNumber, option);
		}
		else if (option == 0) {
			orders.erase(orderNumber);
			done = true;
		}
		else if (option == 5) {
			orderNumber++;
			done = true;
		}
		else {
			centerText("Invalid input", 1);
		}
	}
}

void Restaurant::saveOrders() {
	ofstream outfile;

	outfile.open("./orders.txt");
	for (int i = 1; i < orders.size(); i++) {
		outfile << orders[i].outputString(i); 
	}
	outfile.close();
}

void Restaurant::loadOrders() {
	ifstream myfile("orders.txt");
	string name, description, line, strPrice, strOrderNum, strItemNum, strStatus;
	double price;
	int orderNum, status;

	if (myfile) {
		while (getline(myfile, line)) {
			stringstream linestream(line);

			getline(linestream, strOrderNum, ',');
			getline(linestream, name, ',');
			getline(linestream, description, ',');
			getline(linestream, strPrice, ',');
			getline(linestream, strStatus, ',');

			price = stod(strPrice);
			orderNum = stoi(strOrderNum);
			status = stoi(strStatus);

			orders[orderNum].addItem(menuItem(name, description, price));
			orders[orderNum].setStatus((Order::STATUS)status);
			orderNumber = orderNum + 1;
		}
	}
	else {
		centerText("File not found", 1);
	}

	myfile.close();
}

void Restaurant::purgeOrders(){
	if (confirm("WARNING!! This will permantly delete all orders (open, closed, and completed). Are you sure?(y/n)")) {
		if (confirm("Are you really sure?(y/n)")) {
			orders.clear();
			orders[0] = Order();
			orderNumber = 1;
		}
	}
}

void Restaurant::addBurger(int orderNum) {
	//orders[orderNum].addItem(Burger());
}