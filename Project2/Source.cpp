#include "Restaurant.h"

int main() {
	bool done = false;
	Restaurant restaurant = Restaurant(); 

	while (!done) {
		switch (viewMenu(0, true)){
			case 0:
				done = true;
				break;
			case 1:	
				restaurant.newOrder();
				break;
			case 2:
				restaurant.viewOrders(0);
				break;
			case 3:
				switch (viewMenu(2, true)) {
					case 0:	
						break;
					case 1:
						restaurant.addMenuItem();
						break;
					case 2:
						restaurant.deleteMenuItem();
						break;
					case 3:
						restaurant.editMenuItem();
						break;
					case 4:
						restaurant.viewOrders(1);
						break;
					case 5:
						restaurant.viewOrders(2);
						break;
					case 6:
						restaurant.purgeOrders();
						break;
					default:
						centerText("Invalid input", 1);
				}
				break;
			default:
				centerText("Invalid input", 1);
		}
	}
	return 0;
}



