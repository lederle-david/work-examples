// OOP244 Final Project - MS6
// File: AmaPerishable.h
// Date: 2016/04/04
// David Lederle
// 104026158 dlederle@myseneca.ca
#include "AmaPerishable.h"
using namespace std;
namespace sict{
	AmaPerishable::AmaPerishable()
	:AmaProduct('P'){
	}

	const Date& AmaPerishable::expiry()const{
		return expiry_;
	}
	void AmaPerishable::expiry(const Date& value){
		expiry_ = value;
	}
	std::fstream& AmaPerishable::store(std::fstream& file, bool addNewLine)const{
		AmaProduct::store(file, false);
		file << ",";
		file << expiry_;
		if (addNewLine){
			file << endl;
		}
		return file;
	}
	std::fstream& AmaPerishable::load(std::fstream& file){
		char temp;
		AmaProduct::load(file);
		file.get(temp);
		expiry_.read(file);
		file.get(temp);
		return file;
	}
	std::ostream& AmaPerishable::write(std::ostream& os, bool linear)const{
		AmaProduct::write(os, linear);
		if (err_.isClear() && !isEmpty()){
			if (linear){
				os << expiry_;
			}
			else{
				os << endl << "Expiry date: " << expiry_;
			}
		}
		return os;
	}
	std::istream& AmaPerishable::read(std::istream& istr){
		AmaProduct::read(istr);
		Date temp;
		if (err_.isClear()){
			 cout << "Expiry date (YYYY/MM/DD): ";
		}
		istr >> temp;
		if (temp.errCode() == CIN_FAILED){
			err_ = "Invalid Date Entry";
			istr.setstate(ios::failbit);
		}
		else if (temp.errCode() == YEAR_ERROR){
			err_ = "Invalid Year in Date Entry";
			istr.setstate(ios::failbit);
		}
		else if (temp.errCode() == MON_ERROR){
			err_ = "Invalid Month in Date Entry";
			istr.setstate(ios::failbit);
		}
		else if (temp.errCode() == DAY_ERROR){
			err_ = "Invalid Day in Date Entry";
			istr.setstate(ios::failbit);
		}
		else{
			expiry_ = temp;
		}
		return istr;
	}

}
