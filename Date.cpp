// Final Project Milestone 1
//
// Version 1.0
// Date		2018-03-21
// Author		
// Description
// 
// Milestone 1 - Date module 
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Yuseon Kang	      2018-03-12           To submit MS1
// Yuseon Kang        2018-04-12           To submit MS5
/////////////////////////////////////////////////////////////////
#include "Date.h"

namespace AMA {
	Date::Date() {

		expireYear = 0;
		expireMonth = 0;
		expireDay = 0;
		comparator = 0;
		errState = NO_ERROR;
		
	}
	// number of days in month mon_ and year year_
	//
	int Date::mdays(int mon, int year)const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}
	void Date::errCode(int eCode) {

		errState = eCode;

	}
	Date::Date(int year, int month, int day) { // Three argument constructor 
		
		int checkDay = 0; // to check the range of days

		if(year > max_year || year < min_year)
		{
			*this = Date();
			this->Date::errCode(YEAR_ERROR);
		}
		else
		{
		
			if (month < 1 && month > 12)
			{
				*this = Date();
				this->Date::errCode(MON_ERROR);
				
			}
			else
			{
				checkDay = Date::mdays(month, year);
				if(day < 1 && day > checkDay)
				{
					*this = Date();
					this->Date::errCode(DAY_ERROR);
				}
				else
				{
					this->expireYear = year;
					this->expireMonth = month;
					this->expireDay = day;
					this->comparator = year * 372 + month * 13 + day;
				}
				
			}
		}
	}
	bool Date::operator==(const Date& rhs) const { 
		Date temp(this->expireYear, this->expireMonth, this->expireDay);
		bool valid = temp.expireYear != 0 && rhs.expireYear != 0;

		if (temp.comparator == rhs.comparator && valid)
		{
			return true;
		}

		return false;


	}
	bool Date::operator!=(const Date& rhs) const {
		Date temp(this->expireYear, this->expireMonth, this->expireDay);
		bool valid = temp.expireYear != 0 && rhs.expireYear != 0;

		if (valid)
		{
			if (temp.comparator != rhs.comparator)
				return true;
			else
				return false;
		}
		
		return false;
	}
	bool Date::operator<(const Date& rhs) const {
		Date temp(this->expireYear, this->expireMonth, this->expireDay);
		bool valid = temp.expireYear != 0 && rhs.expireYear != 0;

		if (valid)
		{
			if (temp.comparator < rhs.comparator)
				return true;
			else
				return false;
		}
		
		return false;
	}
	bool Date::operator>(const Date& rhs) const {
		Date temp(this->expireYear, this->expireMonth, this->expireDay);
		bool valid = temp.expireYear != 0 && rhs.expireYear != 0;

		if (valid)
		{
			if (temp.comparator > rhs.comparator)
				return true;
			else
				return false;
		}
		
		return false;
	}
	bool Date::operator<=(const Date& rhs) const {
		Date temp(this->expireYear, this->expireMonth, this->expireDay);
		bool valid = temp.expireYear != 0 && rhs.expireYear != 0;

		if (valid)
		{
			if (temp.comparator <= rhs.comparator)
				return true;
			else
				return false;
		}
		
		return false;
	}
	bool Date::operator>=(const Date& rhs) const {
		Date temp(this->expireYear, this->expireMonth, this->expireDay);
		bool valid = temp.expireYear != 0 && rhs.expireYear != 0;

		if (valid)
		{
			if (temp.comparator >= rhs.comparator)
				return true;
			else
				return false;
		}
		
		return false;
	}
	int Date::errCode() const {

		return this->errState;
	}
	bool Date::bad() const{
		if (this->errState != 0)
			return true;
		
		return false;
	}

	std::istream& Date::read(std::istream& istr) { // to read formatted input 
		int y, m, d;

		istr >> y;
		istr.ignore(1,'/');
		istr >> m;
		istr.ignore(1,'/');
		istr >> d;
		
		
		Date temp(y, m, d);

		

		if (temp.expireYear == 0 || temp.expireMonth == 0 || temp.expireDay == 0)
		{
			*this = Date();
			errCode(temp.errState); 
		}
		else
		{
			this->expireYear = temp.expireYear;
			this->expireMonth = temp.expireMonth;
			this->expireDay = temp.expireDay;
		}
		

		if (istr.fail()) {

			this->errState = 1;
		}
		
		return istr;
		
	}
	std::ostream& Date::write(std::ostream& ostr) const {
		char c = '/';

		ostr << this->expireYear;
		ostr << c;
		ostr.width(1);
		ostr << this->expireMonth;
		ostr << c;
		ostr.width(2);
		ostr << this->expireDay;
		
		return ostr;
	}

	std::istream& operator>>(std::istream& istr, Date& rhs) {
		rhs.read(istr);
		return istr;
	}
	std::ostream& operator<<(std::ostream& ostr, Date& rhs) {
		rhs.write(ostr);
		return ostr;
	}
}
