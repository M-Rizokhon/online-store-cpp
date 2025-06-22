#pragma once
// including all necessary libraries
#include <iostream>
//#include <stdexcept>
//#include <exception>
#include <string>


using namespace std;


// product class
class Product {
private:
	// declaring all private members
	string name;
	double price;
	int id;
	int stock;   // quantity of the product

public:
	// constructor
	Product(string name = "", double price = 0.0, int id = 0, int stock = 0)
		: name(name), price(price), id(id), stock(stock) {
	}


	// getter functions
	string getName() const { return name; }
	double getPrice() const { return price; }
	int getID() const { return id; }
	int getStock() const { return stock; }


	// setter functions
	void setStock(int new_stock) { stock = new_stock; }


	// overloading '+' operator to add quantity to the Product
	void operator + (const Product& other) {
		if (id == other.id)
			stock += other.stock;    // basically increases stock if id and name are the same
	}


};


// Cart item class
class CartItem {
	// declaring private members
	Product product;
	int quantity;

public:
	// default constructor
	CartItem() : product(), quantity(0) {}

	// parametrized constructor
	CartItem(Product prod, int quantity = 0) : product(prod), quantity(quantity) {}

	// getter functions related to the product
	string get_name() const { return product.getName(); }
	double get_price() const { return product.getPrice(); }
	int get_stock() const { return product.getStock(); }
	int get_id() const { return product.getID(); }
	int getQuantity() const { return quantity; }



};




// user class 
class User {
protected:
	// declaring protected members
	string username, password;

public:
	// default constructor
	User() : username(""), password("") {}

	// parametrized constructor
	User(string username, string password) : username(username), password(password) {}

	// virtual destructor
	virtual ~User() {}

	// a function to display the menu in inherited classes
	virtual void displayMenu() {
		
	};   // (virtual function)

	// a function to get the role
	virtual string getRole() { return ""; }

	// functions to get username and passwords
	string getUsername() const { return username; }
	string getPassword() const { return password; }

	virtual void AddMyProduct(string n, int id, int q, double p) {
		// needed for seller class
	}

	virtual void ViewMyProds() const {}  // needed for seller class
	
	friend ostream& operator << (ostream& out, User& user);
};

ostream& operator << (ostream& out, User& user) {
	out << "Username : " << user.getUsername() << "\nPassword : " << user.getPassword() << "\nRole : " << user.getRole() << endl;
	return out;
}


// inheriting buyer class
class Buyer : public User {
private:
	string role = "buyer";   // fixed role "buyer"

public:
	// constructor
	Buyer(string name, string pass) : User(name, pass) {}

	// overriding displayMenu() function
	void displayMenu() override {
		cout << "1. View products\n";
		cout << "2. Add product to the cart\n";
		cout << "3. View cart\n";
		cout << "4. Checkout\n";
		cout << "5. Log out\n";
		cout << "6. Exit\n";
	}

	// overriding the role
	string getRole() override { return role; }

	bool operator == (Buyer& other) {
		return (other.getUsername() == username && other.getPassword() == password && other.getRole() == role);
	}

	friend ostream& operator << (ostream& out, Buyer& buyer);
};

ostream& operator << (ostream& out, Buyer& buyer) {
	out << "Username : " << buyer.getUsername() << "\nPassword : " << buyer.getPassword() << "\nRole : " << buyer.getRole() << endl;
	return out;
}


// inheriting seller class
class Seller : public User {
private:
	string role = "seller";   // fixed role seller
	int prod_counter = 0;

public:
	Product my_products[100];   // each seller will be given 100 products limit

	// constructor
	Seller(string name, string pass) : User(name, pass) {}

	// overriding displayMenu() function
	void displayMenu() override {
		cout << "1. View products\n";
		cout << "2. Add product\n";
		cout << "3. Update stock\n";
		cout << "4. View my products\n";
		cout << "5. Logout\n";
		cout << "6. Exit\n";
	}

	string getRole() override { return role; }
	int getCounter() const { return prod_counter; }

	void AddMyProduct(string name, int id, int quantity, double price) override {
		Product prod(name, price, id, quantity);
		if (prod_counter < 100) {
			my_products[prod_counter++] = prod;
			cout << "Product added successfully!\n";
		}
		else
			cout << "Cannot add more products! You have reached your limit!\n";
	}


	void ViewMyProds() const override {
		if (prod_counter == 0) {
			cout << "'My products' list is empty\n";
			return;
		}

		string Name, Price, Quantity, Id;

		cout << "\nMy products \n";
		cout << "Name                Price            Quantity       ID\n";
		cout << "---------------------------------------------------------\n";
		for (int i = 0; i < prod_counter; ++i) {
			Name = my_products[i].getName();
			Price = to_string(my_products[i].getPrice());
			Quantity = to_string(my_products[i].getStock());
			Id = to_string(my_products[i].getID());

			cout << Name;
			for (int i = Name.length(); i < 20; ++i)
				cout << " ";

			cout << "$" << Price;
			for (int i = Price.length(); i < 17; ++i)
				cout << " ";


			cout << Quantity;
			for (int i = Quantity.length(); i < 14; ++i)
				cout << " ";

			cout << Id;

			cout << endl;
		}
	}


	friend ostream& operator << (ostream& out, Seller& seller);
};

ostream& operator << (ostream& out, Seller& seller) {
	out << "Username : " << seller.getUsername() << "\nPassword : " << seller.getPassword() << "\nRole : " << seller.getRole() << endl;
	return out;
}




// inheriting admin class
class Admin : public User {
private:
	string role = "admin";

public:
	// constructor
	Admin(string name, string pass) : User(name, pass) {}


	// overriding displayMenu() function
	void displayMenu() override {
		cout << "1. View products\n";
		cout << "2. Add product\n";
		cout << "3. Update stock\n";
		cout << "4. Remove user\n";
		cout << "5. Add user\n";
		cout << "6. View purchase records\n";
		cout << "7. View user info\n";
		cout << "8. Logout\n";
		cout << "9. Exit\n";
	}


	string getRole() override { return role; }
};

