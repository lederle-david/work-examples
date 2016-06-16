// OOP244 Final Project - MS6
// File: ErrorMessage.cpp
// Date: 2016/04/04
// David Lederle
// 104026158 dlederle@myseneca.ca

#include "ErrorMessage.h"
#include <cstring>
namespace sict{

	ErrorMessage::ErrorMessage(){
		message_ = nullptr;
	}
	ErrorMessage::ErrorMessage(const char* errorMessage){
		message_ = nullptr;
		message(errorMessage);
	}
	ErrorMessage& ErrorMessage::operator=(const char* errorMessage){
		clear();
		message(errorMessage);
		return *this;
	}
	ErrorMessage::~ErrorMessage(){
		delete[] message_;
	}
	void ErrorMessage::clear(){
		delete[] message_;
		message_ = nullptr;
	}
	bool ErrorMessage::isClear()const{
		return !message_;
	}
	void ErrorMessage::message(const char* value){
		delete[] message_;
		message_ = new char[strlen(value) + 1];
		strcpy(message_, value);
	}
	const char* ErrorMessage::message()const{
		return message_;
	}
	std::ostream& operator<<(std::ostream& ostr, const ErrorMessage& E){
		if (!E.isClear()){
			ostr << E.message();
		}
		return ostr;
	}
}