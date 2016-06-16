// OOP244 Final Project - MS6
// File: Date.h
// Date: 2016/04/04
// David Lederle
// 104026158 dlederle@myseneca.ca

#ifndef SICT_DATE_H__
#define SICT_DATE_H__
#include <iostream>
namespace sict{



  class Date{
  private:
	int year_;
	int mon_;
	int day_;
	int readErrorCode_;
	int value()const;
	void errCode(int errorCode);
  public:
	Date();
	Date(int year, int month, int day);
	bool operator==(const Date& D)const; 
	bool operator!=(const Date& D)const; 
	bool operator<(const Date& D)const; 
	bool operator>(const Date& D)const; 
	bool operator<=(const Date& D)const; 
	bool operator>=(const Date& D)const;
	int mdays()const;
	int	errCode()const;
	bool bad()const;

	std::istream& read(std::istream& istr);
	std::ostream& write(std::ostream& ostr)const;
	
  };
  std::ostream& operator<<(std::ostream& ostr, const Date& D);
  std::istream& operator>>(std::istream& istr, Date& D);

}
#endif