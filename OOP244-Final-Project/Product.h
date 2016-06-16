// OOP244 Final Project - MS6
// File: Product.h
// Date: 2016/04/04
// David Lederle
// 104026158 dlederle@myseneca.ca

#ifndef SICT__Product_H_
#define SICT__Product_H_
#include "general.h"
#include "Streamable.h"
#include <iostream>
#include <iomanip>
#include <fstream>

namespace sict{
	class Product: public Streamable{
	private:
		char sku_[MAX_SKU_LEN + 1];
		char* name_;
		double price_;
		bool taxed_;
		int quantity_;
		int qtyNeeded_;
	public:
		Product();
		Product(const char* sku,const char* name, bool taxed = true, double price = 0, int qtyNeeded = 0);
		Product(const Product& P);
		virtual ~Product();
		Product& operator=(const Product& P);

		//setter functions
		void sku(const char* value);
		void price(double value);
		void name(const char* value);
		void taxed(bool value);
		void quantity(int value);
		void qtyNeeded(int value);

		//getter functions
		const char* sku()const;
		double price()const;
		const char* name()const;
		bool taxed()const;
		int quantity()const;
		int qtyNeeded()const;

		double cost()const;
		bool isEmpty()const;

		bool operator==(const char* value);
		int operator+=(int value);
		int operator-=(int value);
	};
	double operator+=(double& value, const Product& P);
	std::ostream& operator<<(std::ostream& ostr, const Product& P);
	std::istream& operator>>(std::istream& istr, Product& P);
}





#endif