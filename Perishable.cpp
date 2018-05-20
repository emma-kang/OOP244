// Final Project - Milestone 5 
// Date	2018-04-12
// Perishable.cpp
// Yuseon Kang (ID: 146831169)
// ykang39@myseneca.ca
// Instructor: Peter Liu
//

#include "Perishable.h"

namespace AMA {
	Perishable::Perishable() {
		//Product('P');
		this->pdType = 'P';
		this->expiry_date = Date();
	}
	std::fstream& Perishable::store(std::fstream& file, bool newLine) const {
		Product::store(file, false);

		file << ',' << expiry_date.expireYear << '/'
		<< '0' << expiry_date.expireMonth << '/' << expiry_date.expireDay;
		
		if (newLine)
		{
			file << '\n';
		}

		return file;
		
	}
	std::fstream& Perishable::load(std::fstream& file) {
		Product::load(file);
		file.ignore();

		expiry_date.read(file);
		
		return file;
	}
	std::ostream& Perishable::write(std::ostream& os, bool linear) const {
		Product::write(os, linear);
		/*
		if (!this->isEmpty() && this->isClear())
		{
			if (!linear)s
			{
				os << "Expiry date: ";
			}
			expiry_date.write(os);
		}
		*/
		
		if (!this->isEmpty() && this->isClear())
		{
			if (linear)
			{
				os.unsetf(std::ios::left);
				os << expiry_date.expireYear << '/';
				os.width(1);
				
				// os.fill('0');
				os << '0' << expiry_date.expireMonth << '/' << expiry_date.expireDay;
			}
			else if (!linear)
			{
				os << " Expiry date: ";
				os << expiry_date.expireYear << '/';
				os.width(1);
				
				// os.fill('0');
				os << '0' << expiry_date.expireMonth << '/' << expiry_date.expireDay;
			}
		}
		

		return os;
	}
	std::istream& Perishable::read(std::istream& is) {
		Product::read(is);
		// temporary Date class instance 
		Date temp;

		if (!is.fail()) {

			std::cout << " Expiry date (YYYY/MM/DD): ";
			temp.read(is); // call the read function of Date class 
			if (temp.errState == 1) // check the stored error state in the object 
			{
				// call the message function of Product module to store error message 
				message("Invalid Date Entry"); 
				is.clear();
				is.setstate(std::ios::failbit);
			}
			else if (temp.errState == 2)
			{
				message("Invalid Year in Date Entry");
				is.clear();
				is.setstate(std::ios::failbit);
			}
			else if (temp.errState == 3)
			{
				message("Invalid Month in Date Entry");
				is.clear();
				is.setstate(std::ios::failbit);
			}
			else if (temp.errState == 4)
			{
				message("Invalid Day in Date Entry");
				is.clear();
				is.setstate(std::ios::failbit);
			}
			
			// copy assignment 
			this->expiry_date = temp;

		}
		
		return is;

	}
	const Date& Perishable::expiry() const {

		return expiry_date;
	}

}
