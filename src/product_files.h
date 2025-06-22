#pragma once
#include "online_store.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


void create_data() {
	// creating a txt file with product name, price, id, stock

	// creating arrays for names, prices, IDs, and stocks
	string product_names[10] = { "bread", "milk", "cheese", "butter", "sausage", "broccoli", "cabbage", "carrot", "soda", "banana" };
	double prices[10] = { 8.0, 5, 13.99, 20, 32.55, 0.77, 4.23, 3.98, 1.50, 3 };
	int IDs[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int stocks[10] = { 50, 20, 30, 24, 40, 38, 30, 100, 120, 230 };

	ofstream file("products.txt");   // creating a file
	for (int i = 0; i < 10; i++) {
		// writing details to the file in the form : e.g. "bread 8.0 1 50"
		file << product_names[i] << " " << prices[i] << " " << IDs[i] << " " << stocks[i] << " \n";
	}
	file.close();

}



// a function to read from the file and store the data
void store_data(OnlineStore& store, string filename = "products.txt") {
	ifstream file(filename);   // opening the file
	string line;

	while (getline(file, line)) {
		string data[4];
		string word = "";
		int idx = 0;
		char ch;

		for (int i = 0; i < line.length(); ++i) {
			ch = line[i];

			if (isspace(ch)) {
				data[idx++] = word;
				word = "";
			}
			else
				word += ch;
		}

		if (!word.empty() && idx < 4) { // Store the last word
			data[idx++] = word;
		}

		string name = data[0];
		double price = stod(data[1]);
		int id = stoi(data[2]);
		int stock = stoi(data[3]);

		store.addProduct(name, price, id, stock, false);
	}
	file.close();
}