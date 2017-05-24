#include "utility.h"

void viewLogo() {
	cout << R"(
____/\\\\\\\\\\\______/\\\\\\\\\\______/\\\\\\\\\\\____
 ___\/\\////////\\___/\\\////////\\__/\\\/////////\\\___
  ___\/\\\___  \/\\_/\\\/______ \/\\_\//\\\______\///____
   __ \/\\\___ /\//_/\\\_______  /\\__\////\\\____________
    ___\/\\\///\//__/\\\________ /\\______\////\\\_________
     ___\/\\\\\//___\/\\\______  /\\ _________\////\\\______
      ___\/\\\_______\/\\\___   /\//____/\\\______\//\\\_____
       ___\/\\\_______\/\\\\\\\/\//_____\///\\\\\\\\\\\/______
        ___\///________\///////\//_________\///////////________        
							v0.1
	)" << '\n';
}

void centerText(string text, int newLine) { //modified code found here http://www.cplusplus.com/forum/general/44198/ into a method with optional newline
	int consoleWidth = 35;
	for (int i = 0; i < newLine; i++) {
		cout << "\n";
	}
	cout << setprecision(2) << fixed << setw(consoleWidth / 2) << " " << text;
}

void ClearScreen() //found at http://www.cplusplus.com/articles/4z18T05o/
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

void debugScreen(vector<string> strings) {
	ClearScreen();
	cout << "Debug: \n";
	for (int i = 0; i < strings.size(); i++){
		cout << "\n" << to_string(i + 1) << ". " << strings[i];
	}

	pause();
}

void pause()
{
	centerText("Press [Enter] to continue . . .", 1);
	cin.ignore();
	cin.get();
}


int viewMenu(int menuText, bool title) {
	vector<vector<string>> menus{
		{ "Main Menu", "1. New Order", "2. View Orders", "3. Options", "0. Exit", "Make a selection: " },
		{ "Items", "1. Entrees", "2. Appetizers", "3. Sides", "4. Beverages", "5. Complete Order", "0. Cancel Order", "Make a selection: " },
		{ "Options" , "1. Add menu item", "2. Remove menu item", "3. Edit menu item", "4. View closed orders", "5. View completed orders", "0. Return to previous menu", "Make a selection: " },
		{ "Edit Item" , "1. Entrees", "2. Appetizers", "3. Sides", "4. Beverages", "Make a selection: " },
		{ "", "1. Add item", "2. Delete item", "3. Cash out order", "4. Delete order", "0. Return to previous menu", "Make a selection: " },
		{ "Edit Item", "1. Name", "2. Description", "3. Price", "0. Return to previous menu", "Make a selection: " },
		{ "", "1. Add item", "2. Delete item", "3. Reopen Order", "0. Return to previous menu", "Make a selection: " },
		{ "", "1. Add item", "2. Delete item", "3. Reopen Order", "4. Refund Order", "0. Return to previous menu", "Make a selection: " }
	};
	int option = 0;
	int size = menus[menuText].size();

	do {
		if (title) {
			viewTitle(menus[menuText][0]);		
		}
		for (int i = 1; i < size - 1; i++) {
			centerText(menus[menuText][i], 1);
		}
		option = getIntegerInput(menus[menuText][size - 1]);

	} while (option < 0 || option > size);
	return option;
}

void viewTitle(string str)
{
	ClearScreen();
	viewLogo();
	centerText("=========== " + str + " ===========", 1);
}

bool confirm(string warning) {
	string str = "";

	centerText(warning, 1);
	cin >> str;

	if (str == "y" || str == "Y") {
		return true;
	}
	else {
		return false;
	}
}

string getStringInput(string prompt) {
	string str = "";
	centerText(prompt, 1);
	cin.ignore();
	getline(cin, str);
	return str;
}

double getDoubleInput(string prompt) {
	double dbl;
	string str;

	centerText(prompt, 1);
	while (true) {
		getline(cin, str);
		stringstream convert(str);
		if (convert >> dbl) {
			return dbl;
		}
	}
}

int getIntegerInput(string prompt) {
	int integer;
	string str;

	centerText(prompt, 1);
	while (true) {
		getline(cin, str);
		stringstream convert(str);
		if (convert >> integer) {
			return integer;
		}
	}
}