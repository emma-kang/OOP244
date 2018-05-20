// Final Project - Milestone 3 - MyProduct and Test Modules
// Date	2018-03-29
// Product.h
// Yuseon Kang (ID: 146831169)
// ykang39@myseneca.ca
// Instructor: Peter Liu
//

#ifndef AMA_PRODUCT_H
#define AMA_PRODUCT_H
#include "ErrorState.h"
#include "iProduct.h"
#include <iostream>
#include <fstream>

const int max_sku_length = 7; // stock keeping unit
const int max_name_length = 10; 
const int max_unit_length = 75;
const double tax_rate = 0.13;

namespace AMA {
	
	class Product : public iProduct {
	//private:
	protected:
		char pdType; // for use in the file record
		char pdSku[max_sku_length+1];
		char pdUnit[max_unit_length+1];
		char* pd_name; // point to the address of name of product
		int qty_hand; // quantity (the number of units) on hand
		int qty_need; // quantity to need
		double single_price; // single unit's price 
		bool taxable; // if the product is taxable, it's true
		ErrorState err; // hold error state of product
	protected:
		void name(const char*);
		const char* name() const;
		double cost() const;
		void message(const char*);
		bool isClear() const;
	public:
		Product(char='N');
		// default value must be only in header file
		Product(const char*,const char*, const char*, int=0, bool=true, double=0.0, int=0); 
		Product(const Product&);
		Product& operator=(const Product&);
		~Product();
		std::fstream& store(std::fstream&, bool=true) const;
		std::fstream& load(std::fstream&);
		std::ostream& write(std::ostream&, bool=true) const;
		std::istream& read(std::istream&);
		bool operator==(const char*) const;
		double total_cost() const;
		void quantity(int);
		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;
		bool operator>(const char*) const; 
		bool operator>(const iProduct&) const; // change
		int operator+=(int);
		const char* sku() const;
		const char* unit() const;
		double price() const;
		bool taxed() const;
	};
	std::ostream& operator<<(std::ostream&, const iProduct&); // change
	std::istream& operator>>(std::istream&, iProduct&); // change
	double operator+=(double&, const iProduct&); // change

}

#endif // !AMA_PRODUCT_H

