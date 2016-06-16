// OOP244 Final Project - MS6
// File: Product.cpp
// Date: 2016/04/04
// David Lederle
// 104026158 dlederle@myseneca.ca

#include "Product.h"
#include <string.h>

namespace sict{
	Product::Product(){
		sku_[0] = '\0';
		name_ = nullptr;
		price(0);
		taxed(true);
		quantity(0);
		qtyNeeded(0);
	}

	Product::Product(const char* sku, const char* name, bool taxed, double price, int qtyNeeded){
		this->sku(sku);
		this->name(name);
		quantity(0);
		this->price(price);
		this->qtyNeeded(qtyNeeded);
		this->taxed(taxed);
	}

	Product::Product(const Product& P){
		sku(P.sku());
		name(P.name());
		quantity(P.quantity());
		price(P.price());
		qtyNeeded(P.qtyNeeded());
		taxed(P.taxed());
	}
	Product::~Product(){
		delete[] name_;
	}
	Product& Product::operator=(const Product& P){
		sku(P.sku());
		name(P.name());
		quantity(P.quantity());
		price(P.price());
		qtyNeeded(P.qtyNeeded());
		taxed(P.taxed());
		return *this;
	}
	void Product::sku(const char* value){
		strncpy(sku_, value, MAX_SKU_LEN);
		sku_[MAX_SKU_LEN] = '\0';
	}
	void Product::price(double value){
		price_ = value;
	}
	void Product::name(const char* value){
		name_ = new char[strlen(value) + 1];
		strcpy(name_, value);
	}
	void Product::taxed(bool value){
		taxed_ = value;
	}
	void Product::quantity(int value){
		quantity_ = value;
	}
	void Product::qtyNeeded(int value){
		qtyNeeded_ = value;
	}
	const char* Product::sku()const{
		return sku_;
	}
	double Product::price()const{
		return price_;
	}
	const char* Product::name()const{
		return name_;
	}
	bool Product::taxed()const{
		return taxed_;
	}
	int Product::quantity()const{
		return quantity_;
	}
	int Product::qtyNeeded()const{
		return qtyNeeded_;
	}
	double Product::cost()const{
		double value = price();
		if (taxed()){
			value = value*1.13;
		}
		return value;
	}
	bool Product::isEmpty()const{
		return (name_ == nullptr);
	}
	bool Product::operator==(const char* value){
		return !(strcmp(sku_, value));
	}
	int Product::operator+=(int value){
		return (quantity_ += value);
	}
	int Product::operator-=(int value){
		return (quantity_ -= value);
	}
	double operator+=(double& value, const Product& P){
		return (value += (P.cost() * P.quantity()));
	}
	std::ostream& operator<<(std::ostream& ostr, const Product& P){
		P.write(ostr, true);
		return ostr;
	}
	std::istream& operator>>(std::istream& istr, Product& P){
		P.read(istr);
		return istr;
	}
}
