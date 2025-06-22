#include "online_store.h"
#include "product_files.h"

int main() {
	OnlineStore store(100, 100, 100);
	int choice;

	store.store_user_data(store);

	//store.register_user("admin123", "12345678", "admin");
	store.register_user("admin123", "12345678", "admin");

	cout << "\n\n";    // line to differentiate
	create_data();   // creating product data
	store_data(store);   // storing product data to the store
	cout << "\n\n";
	

	while (true) {
		store.display_menu();
		cin >> choice;

		// handling exit
		if ((store.user == nullptr && choice == 4) ||
			(store.user != nullptr && store.user->getRole() == "admin" && choice == 9) ||
			(store.user != nullptr && store.user->getRole() == "seller" && choice == 6) ||
			(store.user != nullptr && store.user->getRole() == "buyer" && choice == 6)) {
			break;
		}

		store.handle_choices(choice);
		cout << "\n\n";
	}

}