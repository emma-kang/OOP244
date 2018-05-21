// Final Project - Milestone 5 
// Date	2018-04-12
// Perishable.h
// Yuseon Kang 

#ifndef AMA_PERISHABLE_H
#define AMA_PERISHABLE_H
#include "Product.h"
#include <iostream>
#include "Date.h"
#include "iProduct.h"

namespace AMA {

	class Perishable : public Product {
		Date expiry_date;
	public:
		Perishable();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		const Date& expiry() const;
	};

}
#endif // !AMA_PERISHABLE_H
