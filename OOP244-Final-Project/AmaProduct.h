// OOP244 Final Project - MS6
// File: AmaProduct.h
// Date: 2016/04/04
// David Lederle
// 104026158 dlederle@myseneca.ca

#ifndef SICT_AMAPRODUCT_H_
#define SICT_AMAPRODUCT_H_
#include "Product.h"
#include "ErrorMessage.h"

namespace sict{
  class AmaProduct : public Product{
  private:
	  char fileTag_;
	  char unit_[11];
  protected:
	  ErrorMessage err_;
  public:
	  AmaProduct(char fileTag = 'N');
	  const char* unit()const;
	  void unit(const char* value);
	  virtual std::fstream& store(std::fstream& file, bool addNewLine = true)const;
	  virtual std::fstream& load(std::fstream& file);
	  virtual std::ostream& write(std::ostream& os, bool linear)const;
	  virtual std::istream& read(std::istream& istr);

  };
}
#endif


