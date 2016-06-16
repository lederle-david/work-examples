// OOP244 Final Project - MS6
// File: AmaPerishable.h
// Date: 2016/04/04
// David Lederle
// 104026158 dlederle@myseneca.ca

#ifndef SICT_AMAPERISHABLE_H_
#define SICT_AMAPERISHABLE_H_
#include "AmaProduct.h"
#include "Date.h"

namespace sict{
  class AmaPerishable: public AmaProduct{
  private:
	  Date expiry_;
  public:
	  AmaPerishable();
	  const Date& expiry()const;
	  void expiry(const Date& value);
	  virtual std::fstream& store(std::fstream& file, bool addNewLine = true)const;
	  virtual std::fstream& load(std::fstream& file);
	  virtual std::ostream& write(std::ostream& os, bool linear)const;
	  virtual std::istream& read(std::istream& istr);
  };
}
#endif
