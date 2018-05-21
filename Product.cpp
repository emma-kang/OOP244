// Final Project - Milestone 5 
// Date	2018-04-12
// Product.h
// Yuseon Kang 

#include <iostream>
#include <cstring>
#include <fstream>
#include "Product.h"

using namespace std;

namespace AMA {

	void Product::name(const char* product) {
		if (product != nullptr)
		{
			// allocate dynamic memory for product's name 
			this->pd_name = new char[strlen(product) + 1];
			strncpy(pd_name, product, strlen(product));
		}
		else
		{
			delete[] this->pd_name;
		}
	}
	const char* Product::name() const {
		if (this->pd_name[0] == '\n') {
			return nullptr;
		}
		return this->pd_name;
	}
	double Product::cost() const {

		if (taxed()) { // if the product is taxable 

			return (this->single_price*tax_rate) + this->single_price;
		}

		return this->single_price;

	}
	void Product::message(const char* errState) {

		// this function will store error message for Perishable class (derived class)
		this->err.message(errState);

	}

	bool Product::isClear() const {
		if (err.isClear())
		{
			return true;
		}

		return false;
	}

	Product::Product(char type) {
		
		this->pdType = type;
		// make a safe empty state 
		this->pd_name = nullptr;
		this->pdSku[0] = '\n';
		this->pdUnit[0] = '\n';
		this->qty_hand = 0;
		this->qty_need = 0;
		this->single_price = 0.0;
		this->err.clear();
		
	}

	Product::Product(const char* sku, const char* name, const char* unit, int hqty, bool tax, double beforetax, int needQty) {
		bool valid = sku != nullptr && name != nullptr && unit != nullptr;

		if (valid)
		{
			//allocate dynamic memory for name value
			pd_name = new char[strlen(name) + 1];

			strncpy(pd_name, name, strlen(name) + 1);
			strncpy(pdSku, sku, strlen(sku) + 1);
			strncpy(pdUnit, unit, strlen(unit) + 1);
			qty_hand = hqty;
			taxable = tax;
			single_price = beforetax;
			qty_need = needQty;
		}
		else
		{
			*this = Product();
		}

	}
	
	Product::Product(const Product& pd) {

		this->qty_hand = pd.qty_hand;
		this->qty_need = pd.qty_need;
		this->single_price = pd.single_price;
		this->taxable = pd.taxable;
		name(pd.pd_name);
		strncpy(pdSku, pd.pdSku, strlen(pd.pdSku) + 1);
		strncpy(pdUnit, pd.pdUnit, strlen(pd.pdUnit) + 1);

	}

	Product& Product::operator=(const Product& pd) {

		if (this != &pd)
		{
			this->qty_hand = pd.qty_hand;
			this->qty_need = pd.qty_need;
			this->single_price = pd.single_price;
			this->taxable = pd.taxable;
			
			// deallocate previously allocated dynamic memory
			//delete[] this->pd_name;
			
			// allocate new dynamic memory
			this->pd_name = new char[max_name_length + 1];
			strncpy(pd_name, pd.pd_name, strlen(pd.pd_name) + 1);
			strncpy(pdSku, pd.pdSku, strlen(pd.pdSku) + 1);
			strncpy(pdUnit, pd.pdUnit, strlen(pd.pdUnit) + 1);

			//if (pd.pd_name != nullptr)
			//{
			//	this->pd_name = new char[max_name_length + 1];
			//	strncpy(pd_name, pd.pd_name, strlen(pd.pd_name) + 1);

			//}
			//else
			//{
			//	this->pd_name = nullptr;
			//}
			
		}
		
		return *this;
	}

	double Product::price() const {

		return this->single_price;
	}

	bool Product::taxed() const {

		return this->taxable;
	}

	Product::~Product() {

		delete[] this->pd_name;

	}

	std::fstream& Product::store(std::fstream& file, bool newLine) const {

		// insert into fstream object the datas of current object in comma separated field
		if (!isEmpty())
		{
			file << this->pdType << "," << this->pdSku << "," << this->pd_name << "," << this->pdUnit << "," << this->taxable << ","
				<< this->single_price << "," << this->qty_hand << "," << this->qty_need;

			if (newLine)
			{
				file << endl;
			}
		}

		return file;

	}

	std::fstream& Product::load(std::fstream& file) {
		char t_sku[max_sku_length + 1];
		char t_name[max_name_length + 1];
		char t_unit[max_unit_length + 1];
		int t_hand;
		bool t_taxed;
		double t_price;
		int t_need;

		if (file.is_open())
		{
			//extract single record from fstrem
			file.getline(t_sku, max_sku_length, ','); 
			file.getline(t_name, max_name_length, ',');
			file.getline(t_unit, max_unit_length, ',');

			file >> t_taxed;
			// ignore single character ', or /'
			file.ignore();
			file >> t_price;
			file.ignore();
			file >> t_hand;
			file.ignore();
			file >> t_need;

			*this = Product(t_sku, t_name, t_unit, t_hand, t_taxed, t_price, t_need);

		}

		return file;

	}

	std::ostream& Product::write(std::ostream& os, bool linear) const {

		if (err.isClear())
		{
			if (linear)
			{
				os.width(max_sku_length);
				os.setf(ios::left);
				os << sku() << "|";
				os.width(20);
				os << name() << "|";
				os.width(7);
				os.unsetf(ios::left);
				os.setf(ios::fixed);
				os.precision(2);
				os << cost() << "|";
				os.width(4);
				os << quantity() << "|";
				os.width(10);
				os.setf(ios::left);
				os << unit() << "|";
				os.unsetf(ios::left);
				os.width(4);
				os << qtyNeeded() << "|";
			}
			else
			{
				if (taxed())
				{
					os << " Sku: " << sku() << endl;
					os << " Name (no spaces): " << name() << endl;
					os << " Price: " << price() << endl;
					os << " Price after tax: " << cost() << endl;
					os << " Quantity on Hand: " << quantity() << " " << unit() << endl;
					os << " Quantity needed: " << qtyNeeded();
					//os.flush(); 
					getchar();
				}
				else
				{
					os << " Sku: " << sku() << endl;
					os << " Name (no spaces): " << name() << endl;
					os << " Price: " << price() << endl;
					os << " Price after tax: " << " N/A" << endl;
					os << " Quantity on Hand: " << quantity() << " " << unit() << endl;
					os << " Quantity needed: " << qtyNeeded() << endl;

				}
			}
		}
		else
		{
			cout << err.message();
		}


		return os;

	}

	std::istream& Product::read(std::istream& is) {
		// temporary variable
		char sku[max_sku_length + 1];
		char name[max_name_length + 1];
		char unit[max_unit_length + 1];
		char taxed = '\0';
		double price;
		int handQty;
		int needQty;
		bool temp_taxable;

		// extract the data field for current object 
		cout << " Sku: ";
		is >> sku;
		cout << " Name (no spaces): ";
		is >> name;
		cout << " Unit: ";
		is >> unit;
		cout << " Taxed? (y/n): ";
		is >> taxed;
		if (taxed == 'Y' || taxed == 'y' || taxed == 'N' || taxed == 'n')
		{
			if (taxed == 'Y' || taxed == 'y')
			{
				temp_taxable = true;
			}
			else if (taxed == 'N' || taxed == 'n')
			{
				temp_taxable = false;
			}

			cout << " Price: ";
			is >> price;
			
			if (is.fail())
			{
				// store error message into the ErrState object err instance 
				err.message("Invalid Price Entry");
			}
			else
			{
				cout << " Quantity on hand: ";
				is >> handQty;
				if (is.fail())
				{
					err.message("Invalid Quantity Entry");
				}
				else
				{
					cout << " Quantity needed: ";
					is >> needQty;
					if (is.fail())
					{
						err.message("Invalid Quantity Needed Entry");
					}
					else
					{
						err.clear();
					}

				}
			}

		}
		else //if(taxed != 'Y' && taxed != 'y' && taxed != 'N' && taxed != 'n')
		{
			err.message("Only (Y)es or (N)o are acceptable");
			is.clear();
			is.setstate(std::ios::failbit);

		}

		// call the seven arguments constructor of Product class 
		Product temp(sku, name, unit, handQty, temp_taxable, price, needQty);

		// the temp copy assign to current object 
		*this = temp;

		return is;
	}

	bool Product::operator==(const char* str) const {
		if (strncmp(this->pdSku, str, strlen(this->pdSku) + 1) == 0)
		{
			return true;
		}

		return false;
	}

	double Product::total_cost() const {

		double total = 0;

		total = this->quantity() * this->cost();

		return total;

	}

	void Product::quantity(int nUnit_hand) {

		this->qty_hand = nUnit_hand;

	}

	bool Product::isEmpty() const {

		if (this->pdSku == nullptr && this->pd_name == nullptr && this->pdUnit)
		{
			return true;
		}

		return false;
	}

	int Product::qtyNeeded() const {

		return qty_need;

	}

	int Product::quantity() const {

		return qty_hand;
	}

	bool Product::operator>(const char* sku) const {
		if (strcmp(this->pdSku, sku) > 0)
		{
			return true;
		}

		return false;
	}

	bool Product::operator>(const iProduct& pd) const {


		if (strcmp(this->pd_name, pd.name()) > 0)
		{
			return true;
		}

		return false;

	}

	int Product::operator+=(int nUnit) {

		if (nUnit > 0)
		{
			this->qty_hand += nUnit;
			return this->qty_hand;
		}

		return this->qty_hand;

	}

	const char* Product::sku() const {

		return this->pdSku;

	}

	const char* Product::unit() const {

		return this->pdUnit;
	}

	std::ostream& operator<<(std::ostream& os, const iProduct& pd) {
		pd.write(os, true);
		return os;

	}

	std::istream& operator>>(std::istream& is, iProduct& pd) {
		pd.read(is);
		return is;
	}
	 
	double operator+=(double& add_cost, const iProduct& pd) {

		add_cost += pd.total_cost();

		return add_cost;

	}

}

