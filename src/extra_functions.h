#pragma once
// additional functions necessary for the project
#include <iostream>
#include <string>
#include "fstream"
#include "Header1.h"
using namespace std;

// a function to check if password is valid
bool valid_password(string password){
	if (password.length() < 8) {
		cout << "Password is too short (min 8 chars)! try again\n";
		return false;
	}

	bool has_number = false, has_symbol = false;    // symbol is non-alphanumberic character
	bool has_capital = false, has_lower = false;


	for (int i = 0; i < password.length(); ++i) {
		if (isdigit(password[i]))
			has_number = true;

		else if (!isalnum(password[i]) && !isspace(password[i]))
			has_symbol = true;

		else if (isupper(password[i]))
			has_capital = true;

		else if (islower(password[i]))
			has_lower = true;
	}

	if (!has_number) {
		cout << "Password must contain at least one number! try again\n";
		return false;
	}

	if (!has_symbol) {
		cout << "Password must contain at least one non-alphanumeric characters! try again\n";
		return false;
	}

	if (!has_capital) {
		cout << "Password must contain at least one uppercase letter! try again\n";
		return false;
	}

	if (!has_lower) {
		cout << "Password must contain at least one lowercase letter! try again\n";
		return false;
	}

	return true;
}


// a function to store the records of purchase
void record_file(CartItem* cart_items, string name, string address, int counter) {
	ofstream file("records.txt", ios::app);  // opening the file in append mode

	if (!file.is_open() || file.fail()) {  // checking for errors
		cout << "File is not open or failed to open!\n";
		return;
	}


	// getting details and writing them to files
	file << "Name : " << name << ", Address : " << address << endl; 
	for (int i = 0; i < counter; ++i) {
		file << cart_items[i].get_name() << " $" << cart_items[i].get_price();
		file << ", " << cart_items[i].getQuantity() << " in quantity";
		file << ", id : " << cart_items[i].get_id() << endl;
	}


	file << "\n\n";   // line to differentiate between details
	file.close();  // closing the file
}




// a function to read the contents of files
void read_file(string filename) { 
	ifstream file(filename);   // opening the file in read mode

	if (!file.is_open() || file.fail()) {   // checking for errors
		cout << "Fail is not open or failed to open!\n";
		return;
	}

	string line;
	while (getline(file, line)) {   // loop ends when there is not line to get
		cout << line << endl;    // printing each line to the console
	}

	file.close();   // closing the file
}
