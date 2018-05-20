// Final Project Milestone 1
//
// Version 1.0
// Date
// Author
// Description
//
// Date module header file 
// Student ID: 146831169
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Yuseon Kang		  2018-03-12		   To submit MS1
/////////////////////////////////////////////////////////////////
#ifndef AMA_DATE_H
#define AMA_DATE_H
#include <iostream>

const int min_year = 2000;
const int max_year = 2030;
const int NO_ERROR = 0; // No error - the date is valid
const int CIN_FAILED = 1; // istream failed on information entry
const int YEAR_ERROR = 2; // Year value is invalid
const int MON_ERROR = 3; // Month value is invalid
const int DAY_ERROR = 4; // Day value is invalid 

namespace AMA {

	class Date {

	public:
		int expireYear;
		int expireMonth;
		int expireDay;
		int comparator;
		int errState;
		int mdays(int, int)const;
		void errCode(int);

	public:
		Date();
		Date(int, int, int);
		bool operator==(const Date&) const;
		bool operator!=(const Date&) const;
		bool operator<(const Date&) const;
		bool operator>(const Date&) const;
		bool operator<=(const Date&) const;
		bool operator>=(const Date&) const;
		int errCode() const;
		bool bad() const;
		std::istream& read(std::istream&);
		std::ostream& write(std::ostream&) const;

	};
	std::istream& operator>>(std::istream&, Date&);
	std::ostream& operator<<(std::ostream&, Date&);

}
#endif
