// OOP244 Final Project - MS6
// File: AidApp.cpp
// Date: 2016/04/11
// David Lederle
// 104026158 dlederle@myseneca.ca

#include "AidApp.h"
#include <string.h>
#include <iostream>
using namespace std;
namespace sict{
	AidApp::AidApp(const char* filename){
		int i;
		strcpy(filename_, filename);
		for (i = 0; i < MAX_NO_RECS; i++){
			product_[i] = nullptr;
		}
		noOfProducts_ = 0;
		loadRecs();
	}
	void AidApp::pause()const{
		cout << "Press Enter to continue..." << endl;
		cin.ignore(1000, '\n');
	}
	int AidApp::menu(){
		int option;
		int result;
		cout << "Disaster Aid Supply Management Program" << endl;
		cout << "1- List products" << endl;
		cout << "2- Display product" << endl;
		cout << "3- Add non-perishable product" << endl;
		cout << "4- Add perishable product" << endl;
		cout << "5- Add to quantity of purchased products" << endl;
		cout << "0- Exit program" << endl;
		cout << "> ";
		cin >> option;
		cout << endl;
		if (option >= 0 && option <= 5){
			result = option;
		}
		else{
			result = -1;
		}
		return result;
	}
	void AidApp::loadRecs(){
		int readIndex = 0;
		char Id;
		datafile_.open(filename_, ios::in);
		if (datafile_.fail()){
			datafile_.clear();
			datafile_.close();
			datafile_.open(filename_, ios::out);
			datafile_.close();
		}
		else{
			while (!datafile_.fail()){
				if (!product_[readIndex]){
					delete product_[readIndex];
				}
				datafile_.get(Id);
				if (Id == 'P'){
					AmaPerishable* perishableProduct = new AmaPerishable;
					product_[readIndex] = perishableProduct;
				}
				else if (Id == 'N'){
					AmaProduct* nonperishableProduct = new AmaProduct;
					product_[readIndex] = nonperishableProduct;
				}
				if (Id == 'P' || Id == 'N') {
					datafile_.get(Id);//skips comma
					product_[readIndex]->load(datafile_);
					readIndex++;
				}
			}
			noOfProducts_ = readIndex;
		}
		datafile_.close();
	}
	void AidApp::saveRecs(){
		int i;
		datafile_.open(filename_, ios::out);
		for (i = 0; i < noOfProducts_ ; i++){
			product_[i]->store(datafile_);
		}
		datafile_.close();
	}
	void AidApp::listProducts()const{
		int i;
		double total = 0;
		cout << " Row | SKU    | Product Name       | Cost  | QTY| Unit     |Need| Expiry   " << endl;
		cout << "-----|--------|--------------------|-------|----|----------|----|----------" << endl;
		for (i = 0; i < noOfProducts_; i++){
			cout << setw(4) << setfill(' ') << right << i + 1;
			cout << " | " << *product_[i] << endl;
			total += product_[i]->cost() * product_[i]->quantity();
			if (i == DISPLAY_LINES - 1){
				cin.ignore(1000, '\n');
				pause();
			}
		}
		cout << "---------------------------------------------------------------------------" << endl;
		cout << "Total cost of support: $" << setprecision(2) << total << endl;
		if (i < DISPLAY_LINES){
			cout << endl;
		}
	}
	int AidApp::SearchProducts(const char* sku)const{
		int result = -1;
		int i;
		for (i = 0; i < noOfProducts_; i++){
			//if (product_[i]->sku() == sku){
			if (!strcmp(product_[i]->sku(), sku)){
				result = i;
			}
		}
		return result;
	}
	void AidApp::addQty(const char* sku){
		int i;
		int result;
		int qty;
		for (i = 0; i < noOfProducts_; i++){
			result = SearchProducts(sku);
		}
		if (result == -1){
			cout << "Not found!" << endl;
		}
		else{
			product_[result]->write(cout, false);
			cout << endl << endl;
			cout << "Please enter the number of purchased items: ";
			cin >> qty;
			if (cin.fail()){
				cout << "Invalid quantity value!" << endl;
			}
			else{
				if (qty <= product_[result]->qtyNeeded() - product_[result]->quantity()){
					product_[result]->quantity(product_[result]->quantity() + qty);
				}
				else{
					int extra = qty + product_[result]->quantity() - product_[result]->qtyNeeded();
					product_[result]->quantity(product_[result]->qtyNeeded());
					cout << "Too many items; only " << product_[result]->quantity() - product_[result]->qtyNeeded();
					cout << " is needed, please return the extra ";
					cout << extra << " items." << endl;
				}
				saveRecs();
				cout << endl << "Updated!" << endl << endl;
				cin.clear();
				fflush(stdin);
			}
		}
	}
	void AidApp::addProduct(bool isPerishable){
		noOfProducts_++;
		if (isPerishable){
			AmaPerishable* perishableProduct = new AmaPerishable;
			perishableProduct->read(cin);
			if (cin.fail()){
				cout << *perishableProduct << endl;
			}
			else{
				product_[noOfProducts_ - 1] = perishableProduct;
				saveRecs();
				cout << endl << "Product added" << endl << endl;
			}
			delete perishableProduct;
		}
		else{
			AmaProduct* nonperishableProduct = new AmaProduct;
			nonperishableProduct->read(cin);
			if (cin.fail()){
				cout << *nonperishableProduct << endl;
			}
			else{
				product_[noOfProducts_ - 1] = nonperishableProduct;
				saveRecs();
			}
			delete nonperishableProduct;
		}
		cin.clear();
		fflush(stdin);
	}
	int AidApp::run(){
		int choice;
		int result;
		char sku[MAX_SKU_LEN];
		do{
			choice = menu();
			if (choice == 1){
				listProducts();
				cin.ignore(1000, '\n');
				pause();
			}
			else if (choice == 2){
				cout << "Please enter the SKU: ";
				cin >> sku;
				cout << endl;
				result = SearchProducts(sku);
				if (result == -1){
					cout << "Not found!" << endl;
				}
				else{
					product_[result]->write(cout, false);
					cout << endl << endl;
				}
				cin.ignore(1000, '\n');
				pause();
			}
			else if (choice == 3){
				addProduct(false);
				loadRecs();
			}
			else if (choice == 4){
				addProduct(true);
				loadRecs();
			}
			else if (choice == 5){
				cout << "Please enter the SKU: ";
				cin >> sku;
				cout << endl;
				addQty(sku);
			}
			else if (choice == 0){
				cout << "Goodbye!!" << endl;
			}
			else{
				cout << "===Invalid Selection, try again.===";
			}
		} while (choice != 0);
		return 0;
	}
}