// OOP244 Final Project - MS6
// File: AmaProduct.h
// Date: 2016/04/04
// David Lederle
// 104026158 dlederle@myseneca.ca

#include "AmaProduct.h"
#include <cstring>
using namespace std;
namespace sict{

	AmaProduct::AmaProduct(char fileTag){
		fileTag_ = fileTag;
	}

	const char* AmaProduct::unit()const{
		return unit_;
	}
	void AmaProduct::unit(const char* value){
		strncpy(unit_, value, 11);
	}

	std::fstream& AmaProduct::store(std::fstream& file, bool addNewLine)const{
		file << fileTag_ << "," << sku() << "," << name() << "," << price() << "," 
		<< taxed() << "," << quantity() << "," << unit() << "," << qtyNeeded();
		if (addNewLine){
			file << endl;
		}
		return file;
	}
	std::fstream& AmaProduct::load(std::fstream& file){
		int intTemp = 0;
		double doubleTemp = 0.0;
		char stringTemp[MAX_PRODUCT_LEN] = "";
		char comma;
		file.getline(stringTemp, MAX_SKU_LEN, ',');
		sku(stringTemp);
		file.getline(stringTemp, MAX_PRODUCT_LEN, ',');
		name(stringTemp);
		file >> doubleTemp;
		price(doubleTemp);
		file.get(comma);
		file >> intTemp;
		taxed(intTemp);
		file.get(comma);
		file >> intTemp;
		quantity(intTemp);
		file.get(comma);
		file.getline(stringTemp, MAX_PRODUCT_LEN, ',');
		unit(stringTemp);
		file >> intTemp;
		qtyNeeded(intTemp);
		return file;
	}
	std::ostream& AmaProduct::write(std::ostream& os, bool linear)const{
		if (!err_.isClear()){
			os << err_;
		}
		else{
			if (linear){
				os << setw(MAX_SKU_LEN) << setfill(' ') << left << sku();
				os << '|';
				os << setw(20) << setfill(' ') << left << name();
				os << '|';
				os << setw(7) << setfill(' ') << fixed << setprecision(2) << right << cost();
				os << '|';
				os << setw(4) << setfill(' ') << right << quantity();
				os << '|';
				os << setw(10) << setfill(' ') << left << unit();
				os << '|';
				os << setw(4) << setfill(' ') << right << qtyNeeded();
				os << '|';
			}
			else{
				os << "Sku: " << sku() << endl;
				os << "Name: " << name() << endl;
				os << "Price: " << price() << endl;
				if (taxed()){
					os << "Price after tax: " << cost() << endl;
				}
				else{
					os << "Price after tax: " << "N/A" << endl;
				}
				os << "Quantity On Hand: " << quantity() << " " << unit() << endl;
				os << "Quantity Needed: " << qtyNeeded();
			}
		}
		return os;
	}
	std::istream& AmaProduct::read(std::istream& istr){
		int intTemp;
		double doubleTemp;
		char stringTemp[MAX_SKU_LEN + 1];
		char charTemp;
		bool error = false;
		err_.clear();
		cout << "Sku: ";
		istr >> stringTemp;
		sku(stringTemp);
		cout << "Name: ";
		istr >> stringTemp;
		name(stringTemp);
		cout << "Unit: ";
		istr >> stringTemp;
		unit(stringTemp);
		cout << "Taxed? (y/n): ";
		istr >> charTemp;
		if (charTemp == 'y' || charTemp == 'Y'
			|| charTemp == 'n' || charTemp == 'N'){
			if (charTemp == 'y' || charTemp == 'Y'){
				taxed(1);
			}
			else{
				taxed(0);
			}
			istr.clear();
		}
		else{
			error = true;
			err_ = "Only (Y)es or (N)o are acceptable";
			istr.setstate(ios::failbit);
		}
		cout << "Price: ";
		if (!error){
			
			istr >> doubleTemp;
			if (istr.fail()){
				error = true;
				err_ = "Invalid Price Entry";
			}
			else{
				price(doubleTemp);
			}
		}
		if (!error){
			cout << "Quantity On hand: ";
			istr >> intTemp;
			if (istr.fail()){
				error = true;
				err_ = "Invalid Quantity Entry";
			}
			else{
				quantity(intTemp);
			}
		}
		if (!error){
			cout << "Quantity Needed: ";
			istr >> intTemp;
			if (istr.fail()){
				error = true;
				err_ = "Invalid Quantity Needed Entry";
			}
			else{
				qtyNeeded(intTemp);
			}
		}
		return istr;
	}
}