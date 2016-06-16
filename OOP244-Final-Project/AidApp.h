// OOP244 Final Project - MS6
// File: AidApp.h
// Date: 2016/04/04
// David Lederle
// 104026158 dlederle@myseneca.ca

#ifndef SICT_AMAPRODUCT_H__
#define SICT_AMAPRODUCT_H__
#include "AmaPerishable.h"
#include "AmaProduct.h"
#include "Product.h"
#include "Date.h"
#include "ErrorMessage.h"

namespace sict{
	class AidApp{
	private:
		char filename_[256];
		Product* product_[MAX_NO_RECS];
		std::fstream datafile_;
		int noOfProducts_;

	public:
		AidApp(const char* filename);
		AidApp(const AidApp& A) = delete;
		AidApp& operator=(const AidApp& A) = delete;
		void pause()const;
		int menu();
		void loadRecs();
		void saveRecs();
		void listProducts()const;
		int SearchProducts(const char* sku)const;
		void addQty(const char* sku);
		void addProduct(bool isPerishable);
		int run();
	};



}
#endif