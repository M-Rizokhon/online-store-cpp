#pragma once
#include "Header1.h"
#include "extra_functions.h"   // header file with additional



// online store class (basically the main class)
class OnlineStore {
private:
	// pointer declaration (memory will be allocated to them)
	Product* products;
	CartItem* cart_items;
	User** users;    // declaring pointer to pointer


	// declaring counters to each array
	int prod_counter;
	int cart_counter;
	int user_counter;

	// declaring the sizes of arrays needed for dynamic memory allocation
	int prod_size;
	int cart_size;
	int user_size;

	
public:
	User* user;   // current user (needed for logging out and other functions)


	// parametrized constructor
	// parameters are the sizes of array, which will be used when dynamically allocating memory
	OnlineStore(int prod_size, int cart_size, int user_size) : prod_size(prod_size), cart_size(cart_size), user_size(user_size) {
		// first assigning each counter to 0
		prod_counter = 0;
		cart_counter = 0;
		user_counter = 0;

		// dynamically allocating memory to arrays
		products = new Product[prod_size];
		cart_items = new CartItem[cart_size];
		users = new User*[user_size];

		user = nullptr;   // assigning user to null pointer
	}


	// destructor to delete objects
	~OnlineStore() {
		delete[] products;
		delete[] cart_items;
		
		for (int i = 0; i < user_counter; ++i) {
			delete users[i];
		}
		delete[] users;	
	}


	// function to register users as Buyer or Seller or Admin
	void register_user(string username, string password, string role, bool saveToFile = true) {
		// checking if the array is full
		if (user_counter >= user_size) {
			cout << "Cannot add more users, user list is full!\n";
			return;
		}


		// checking if the username already exists (throwing error if already exists)
		for (int i = 0; i < user_counter; ++i) {
			if (username == users[i]->getUsername()) {
				cout << "Error! Username already exists!\n";
				return;
			}
		}

		// creating a user depending on the role

		if (role == "admin") {
			users[user_counter] = new Admin(username, password);
		}

		else if (role == "seller") {
			users[user_counter] = new Seller(username, password);
		}

		else {  // by default the user will be buyer
			users[user_counter] = new Buyer(username, password);
		}
		if (saveToFile) {
			ofstream file("users.txt", ios::app);
			file << username << " " << password << " " << role << endl;
			file.close();
		}

		user_counter++;

		cout << "User '" << username << "' is registered successfully!\n";

	}


	void store_user_data(OnlineStore& store, string filename = "users.txt") {
		ifstream file(filename);
		string username, password, role;

		while (file >> username >> password >> role) {
			store.register_user(username, password, role, false);  //  'false' to avoid saving again to file
		}
		file.close();
	}





	// a function to log in (returns true if logged in successfully, false otherwise)
	bool login(string username, string password, string role) {
		for (int i = 0; i < user_counter; ++i) {
			// if all arguments match, I will return true (meaning it exists)
			if (username == users[i]->getUsername() && password == users[i]->getPassword() && role == users[i]->getRole()) {
				cout << "Logged in as " << role << " (" << username << ")\n";
				user = users[i];
				return true;
			}
		}
		cout << "Invalid username or password or role!\n";
		return false;
	}


	// a function to logout 
	void logout() {
		if (user != nullptr) {
			cout << "Logging out from '" << user->getUsername() << "'\n";
			user = nullptr;   // assigning user to null pointer after logging out
			cart_counter = 0;   // setting cart counter to 0 as there is not user to add items to the cart
		}
		else { cout << "No one logged in yet!\n"; }
	}

	// a function to remove a user
	void remove_user(string username) {
		if (user_counter == 0) {
			cout << "No users to remove!\n";
			return;
		}

		for (int i = 0; i < user_counter; ++i) {   // searching for the user
			if (users[i]->getUsername() == username) {
				delete users[i];
				for (int j = i; j < user_counter - 1; ++j) {   // basically moving one to the left to remove
					users[j] = users[j + 1];
				}
				cout << "User '" << username << "' removed successfully!\n";
				user_counter--;
				return;
			}
		}

		cout << "User '" << username << "' not found\n";
	}
	

	

	// a function to display all products
	void displayProducts() const {
		cout << "Products in the Store!\n";
		cout << "Name                 Price       Stock        Product ID\n";
		cout << "------------------------------------------------------------------\n";

		for (int i = 0; i < prod_counter; ++i) {
			format_line(products[i]);
		}
	}


	 //small function to format the output to the console 
	void format_line(Product& product) const {
		// getting product details as strings
		string name = product.getName();
		string price = to_string(product.getPrice());
		string id = to_string(product.getID());
		string stock = to_string(product.getStock());


		// printing name, 10 characters wide
		cout << name;
		for (int i = name.length(); i < 20; ++i)
			cout << " ";

		// printing price, 14 chars wide
		cout << price;
		for (int i = price.length(); i < 14; ++i)
			cout << " ";

		// stock 16 chars wide
		cout << stock;
		for (int i = stock.length(); i < 16; ++i)
			cout << " ";

		cout << id;
		cout << endl;

	}


	// a function to add a new product for Admin and Seller
	void addProduct(string name, double price, int id, int stock, bool saveToFile = true) {
		// checking for errors (stock must be a positive integer)
		try {
			if (stock <= 0)
				throw logic_error("Error! Stock cannot be a negative value!");  // throwing logical error
		}

		catch (const logic_error& e) {   // catching the error
			cout << e.what() << endl;
			return;
		}

		if (prod_counter < prod_size) {   // checking if product array is not full (we cannot add more products to full array)
			// checking if id already exists
			for (int i = 0; i < prod_counter; ++i) {
				if (products[i].getID() == id) {
					cout << "Product ID already exists!\n";
					return;   // returning if ID already exists
				}
			}
			if (saveToFile) {
				ofstream file("products.txt", ios::app);
				file << name << " " << price << " " << id << " " << stock << endl;
				file.close();
			} // to save new items


			// adding the product to product list (array)
			products[prod_counter++] = Product(name, price, id, stock);
			cout << "Product " << name << " is added successfully!\n";
		}
		else {
			cout << "Sorry, cannot add more products, product list is full!\n";
			return;
		}
	}





	// a function to update the stock for Sellers and Admins
	void update_stock(int product_id, int new_stock) {
		// checking for errors
		try {
			if (new_stock < 0) {      // throwing error in case of stock having invalid value
				throw logic_error("Error! New stock cannot be negative!\n");  
			}
		}
		catch (const logic_error& e)  {  // catching and printing error to the console
			cout << e.what() << endl;
			return;
		}

		for (int i = 0; i < prod_counter; ++i) {   // looking for product ID
			if (products[i].getID() == product_id) {
				products[i].setStock(new_stock);    // setting the stock to new value
				cout << "Stock of product '" << products[i].getName() << "' is updated to " << new_stock << endl;
				return;
			}
		}
		cout << "Product ID is not found!\n";
	}

	// function overloading for updating stock for seller
	void update_stock(Seller& seller, int product_id, int new_stock) {
		try {
			if (new_stock < 0) {      // throwing error in case of stock having invalid value
				throw logic_error("Error! New stock cannot be negative!\n");
			}
		}
		catch (const logic_error& e) {  // catching and printing error to the console
			cout << e.what() << endl;
			return;
		}

		for (int i = 0; i < seller.getCounter(); ++i) {   // looking for product ID
			if (seller.my_products[i].getID() == product_id) {
				seller.my_products[i].setStock(new_stock);    // setting the stock to new value
				cout << "Stock of product '" << products[i].getName() << "' is updated to " << new_stock << endl;
				return;
			}
		}
		cout << "Product ID is not found among your own products !\n";

	}




	// a function to add to the cart of Buyer
	void AddToCart(int product_id, int quantity) {
		// checking for errors for quantity value
		try {
			if (quantity <= 0) {   // throwing error in case of quantity being non positive
 				throw logic_error("Error! Quantity cannot be negative!\n");
			}
		}
		catch (const logic_error& e) {  // catching and printing error to the screen
			cout << e.what() << endl;
			return;
		}


		if (cart_counter >= cart_size) {     // checking if cart is not full
			cout << "Sorry, the cart is full! Cannot add more products!\n";
			return;
		}

		for (int i = 0; i < prod_counter; ++i) {    // searching for the product from the store
			if (products[i].getID() == product_id) {
				if (quantity <= products[i].getStock()) {   // checking if quantity does not exceed available stock
					cart_items[cart_counter++] = CartItem(products[i], quantity);  // adding the product to the cart
					int new_stock = products[i].getStock() - quantity;   // new stock at the store
					products[i].setStock(new_stock);   // setting new stock to the product
					cout << "Product '" << products[i].getName() << "' added to the cart successfully!\n";
					return;

				}
				else {
					cout << "Sorry, there are not enough " << products[i].getName() << "(s) in the store\n";
					return;
				}
			}
		}

		cout << "Sorry, product ID is not found!\n";  // message in case the product is not in the store
	}



	// a function to view the cart (for the buyer)
	void ViewCart() {
		if (cart_counter == 0) {    // checking if the cart is empty
			cout << "Cart is empty!\n";
			return;  
		}

		double total = 0.0;   // total price
		cout << "Cart of '" << user->getUsername() << "'\n";
		cout << "Product                   Price             Quantity\n";
		cout << "-----------------------------------------------------\n";

		string Name, Price, Quantity;
		for (int i = 0; i < cart_counter; ++i) {
			Name = cart_items[i].get_name();
			Price = to_string(cart_items[i].get_price());
			Quantity = to_string(cart_items[i].getQuantity());

			// printing the details to the console
			cout << Name;
			for (int i = Name.length(); i < 20; ++i)
				cout << " ";
			cout << "   ";

			cout << "$" << Price;
			for (int i = Price.length(); i < 10; ++i)
				cout << " ";

			cout << "      ";
			cout << Quantity;
			for (int i = Quantity.length(); i < 10; ++i)
				cout << " ";

			cout << "\n";
			
			// adding to the total price
			total += cart_items[i].get_price() * cart_items[i].getQuantity();
		}
		cout << "-----------------------------------------------------\n";
		cout << "Your total is $" << total << endl;
	}



	// checkout (for the buyer). Basically the cashier part of shopping at Korzinka for example.
	void checkout() {
		if (cart_counter == 0) {   // checking if cart is empty
			cout << "Cart is empty, cannot proceed to checkout!\n";
			return;
		}

		cin.ignore();
		ViewCart();   // showing the cart to the buyer
		cout << "\nProceeding to checkout...\n";
		cout << "Enter your name : ";     // getting name
		string name;
		getline(cin, name);   // using getline in case the name involved whitespace (e.g. Muhammad Rizo)

		cout << "Enter your address : ";   // getting address
		string address;
		getline(cin, address);


		cout << "\nOrder Summary \n";
		cout << "Name : " << name << ", Address : " << address << endl;
		ViewCart();  // showing the cart one more time
		cout << "\nThank you for your purchase\n";


		record_file(cart_items, name, address, cart_counter);      // recording to the file

		cart_counter = 0;   // setting cart counter to 0 (meaning empty)
	}


	// a function to display the menu for each user
	// different users have different menus (Admin's menu differs from Buyer's menu)
	void display_menu() {
		if (user == nullptr) {   // if no user is logged in
			cout << "Logged in as Guest\n";
			cout << "1. View Products\n";
			cout << "2. Login\n";
			cout << "3. Register\n";
			cout << "4. Exit\n";
		}

		else if (user->getRole() == "admin") {
			cout << "Logged in as Admin\n";
			user->displayMenu();   // calling the function display menu
		}

		else if (user->getRole() == "seller") {
			cout << "Logged in as Seller\n";
			user->displayMenu();
		}

		else if (user->getRole() == "buyer") {
			user->displayMenu();
		}


		cout << "Enter your choice : ";  // prompting user to choose an option
	}



	// a function to handle the choices
	void handle_choices(int choice) {
		// handling choices for Guest
		if (user == nullptr) {
			if (choice == 1) {
				displayProducts();
			}

			else if (choice == 2) {
				cin.ignore();      // clearing the buffer

				string username, password, role;
				cout << "Enter username : ";
				getline(cin, username);
				
				cout << "Enter password : "; 
				getline(cin, password);

				cout << "Select the role (admin/seller/buyer) : "; 
				cin >> role;

				login(username, password, role);
			}

			else if (choice == 3) {
				cin.ignore();

				string user_name, pass_word, role_;
				cout << "Enter username : "; 
				getline(cin, user_name);
				cout << "Enter password (password must contain a number, capital, lower char, symbol): ";
				getline(cin, pass_word);
				if (!valid_password(pass_word)) return;   // breaks the process if password is not valid, else just continues

				cout << "Select the role (seller/buyer) : ";
				cin >> role_;

				register_user(user_name, pass_word, role_);
			}
			else if (choice == 4) {
				return;
			}

			else { cout << "Invalid choice! try again\n"; }
		}


		// handling choices for the buyer
		else if (user->getRole() == "buyer") {
			if (choice == 1) {
				displayProducts();
			}

			else if (choice == 2) {
				int id, quantity;
				cout << "Enter product ID : "; cin >> id;
				cout << "Enter quantity : "; cin >> quantity;

				AddToCart(id, quantity);
			}

			else if (choice == 3)
				ViewCart();

			else if (choice == 4)
				checkout();

			else if (choice == 5)
				logout();

			else if (choice == 6)
				return;

			else
				cout << "Invalid input! try again\n";
		}



		// handling choices for the seller
		else if (user->getRole() == "seller") {
			string name;
			int previous_prod_counter;

			Seller* seller = dynamic_cast<Seller*>(user);   // downcasting to Seller class (basically got from VS copilot)

			switch (choice) {
			case 1: displayProducts(); break;

			case 2:   // adding product option
				double price;
				int stock, id;

				cin.ignore();
				cout << "Enter product name : "; 
				getline(cin, name);
				cout << "Enter product price : $"; cin >> price;
				cout << "Enter stock : "; cin >> stock;
				cout << "Enter product ID : "; cin >> id;

				previous_prod_counter = prod_counter;
				addProduct(name, price, id, stock);
				

				// if product is added to the store, then it's also added to 'my products' list
				// if product is added to the store, prod_counter increases
				if (previous_prod_counter < prod_counter) {
					user->AddMyProduct(name, id, stock, price);
				}
				
				break;

			case 3:  // updating stock option
				int new_stock, product_id;
				cout << "Enter product ID: "; cin >> product_id;
				cout << "Enter new stock : "; cin >> new_stock;
				if (seller) {
					update_stock(*seller, product_id, new_stock);
				}
				else {
					cout << "Error! not a seller\n";
				}
				break;

			case 4:
				user->ViewMyProds();
				break;

			case 5:
				logout();
				break;

			case 6: return;

			default:
				cout << "Invalid choice! try again\n";
				break;
			}

		}



		// handling choices for Admin
		else if (user->getRole() == "admin") {
			if (choice == 1) {
				displayProducts();
			}

			else if (choice == 2) {
				string name;
				int id, stock;
				double price;

				cin.ignore();
				cout << "Enter product name : "; 
				getline(cin, name);
				cout << "Enter product ID : "; cin >> id;
				cout << "Enter stock : "; cin >> stock;
				cout << "Enter price : $"; cin >> price;

				addProduct(name, price, id, stock);
			}

			else if (choice == 3) {
				int new_stock, product_id;
				cout << "Enter product ID : "; cin >> product_id;
				cout << "Enter new stock : "; cin >> new_stock;

				update_stock(product_id, new_stock);
			}

			// function to remove a user
			else if (choice == 4) {
				cin.ignore();
				string username;
				cout << "Enter username of the user you want to remove : "; 
				getline(cin, username);
				remove_user(username);
			}

			else if (choice == 5) {
				cin.ignore();
				string username, password, role;
				cout << "Enter username to add : "; 
				getline(cin, username);
				cout << "Enter password to add : "; 
				getline(cin, password);
				cout << "Select the role to add (admin/seller/buyer) : "; cin >> role;

				register_user(username, password, role);
			}

			else if (choice == 6) {
				read_file("records.txt");
			}

			else if (choice == 7) {
				for (int i = 0; i < user_counter; ++i)
					// using '*' because users is a pointer array and is overloaded with stream insertion operator
					cout << *users[i] << endl;   // outputting the result to the console
			}

			else if (choice == 8) {
				logout();
			}

			else if (choice == 9)
				return;

			

			else { cout << "Invalid input! try again\n"; }
		}

	}
};
