// OOP244 Final Project - MS6
// File: Date.cpp
// Date: 2016/04/04
// David Lederle
// 104026158 dlederle@myseneca.ca

#include <iomanip>
#include <iostream>
using namespace std;
#include "Date.h"
#include "general.h"
namespace sict{
	Date::Date(){
		year_ = 0;
		mon_ = 0;
		day_ = 0;
		readErrorCode_ = NO_ERROR;
	}
	Date::Date(int year, int month, int day){
		year_ = year;
		mon_ = month;
		day_ = day;
		readErrorCode_ = NO_ERROR;
	}
  int Date::value()const{
    return year_ * 372 + mon_ * 31 + day_;
  }
  void Date::errCode(int errorCode){
	  readErrorCode_ = errorCode;
  }
  bool Date::operator==(const Date& D)const{
	  return (value() == D.value());
  }
  bool Date::operator!=(const Date& D)const{
	  return !(value() == D.value());
  }
  bool Date::operator<(const Date& D)const{
	  return (value() < D.value());
  }
  bool Date::operator>(const Date& D)const{
	  return (value() > D.value());
  }
  bool Date::operator<=(const Date& D)const{
	  return (value() <= D.value());
  }
  bool Date::operator>=(const Date& D)const{
	  return (value() >= D.value());
  }
  int Date::mdays()const{
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
    int mon = mon_ >= 1 && mon_ <= 12 ? mon_ : 13;
    mon--;
    return days[mon] + int((mon == 1)*((year_ % 4 == 0) && (year_ % 100 != 0)) || (year_ % 400 == 0));
  }
  int Date::errCode()const{
	  return readErrorCode_;
  }
  bool Date::bad()const{
	  return readErrorCode_;
  }

  std::istream& Date::read(std::istream& istr){
	  char placeHolder;
	  istr >> year_ >> placeHolder >> mon_ >> placeHolder >> day_;

	  if (cin.fail()){
		  errCode(CIN_FAILED);
	  }
	  else{
		  if (year_ < MIN_YEAR || year_ > MAX_YEAR){
			  errCode(YEAR_ERROR);
		  }
		  else if (mon_ < 1 || mon_ > 12){
			  errCode(MON_ERROR);
		  }
		  else if (day_ < 1 || day_ > mdays()){
			  errCode(DAY_ERROR);
		  }
	  }
	  return istr;
  }
  std::ostream& Date::write(std::ostream& ostr)const{
	  ostr << year_ << '/' << setw(2)<< setfill('0') << mon_ << '/' << setw(2) << setfill('0') << day_;
	  return ostr;
  }

  std::ostream& operator<<(std::ostream& ostr, const Date& D){
	  D.write(ostr);
	  return ostr;
  }
  std::istream& operator>>(std::istream& istr, Date& D){
	  D.read(istr);
	  return istr;
  }

}
