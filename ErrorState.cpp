// Final Project Milestone 3
// ErrorState.cpp
// Version 1.0
// Date		2018-03-21
//
// Milestone 3
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Yuseon Kang	      2018-03-21           To submit MS3
// Yuseon Kang        2018-04-12           To submit MS5
/////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstring>
#include "ErrorState.h"

namespace AMA {

	ErrorState::ErrorState(const char* errorMessage)
	{
		if (errorMessage != nullptr)
		{
			this->pErrMsg = new char[strlen(errorMessage) + 1]; // allocate dynamic memory for errorMessage
			strncpy(this->pErrMsg, errorMessage, strlen(errorMessage) + 1); // copy the msg
		}
		else
			this->clear(); // make a safe empty state 
	}

	ErrorState::~ErrorState() 
	{
		delete [] pErrMsg; // deallocate the memory 
	}
	void ErrorState::clear() 
	{
		this->pErrMsg = nullptr; 
	}
	bool ErrorState::isClear() const 
	{
		if (pErrMsg == nullptr)
			return true;

		return false;
	}
	void ErrorState::message(const char* str) 
	{
		delete[] pErrMsg; // deallocate previously allocated memory 
		pErrMsg = new char[strlen(str) + 1]; // newly allocate dynamic memory 
		strncpy(this->pErrMsg, str, strlen(str) + 1);

	}
	const char* ErrorState::message()const 
	{
		if (this->pErrMsg != nullptr)
		{
			return this->pErrMsg;
		}

		return 0;
	
	}
	std::ostream& operator<<(std::ostream& os, ErrorState& rhs)
	{
		if (!rhs.isClear()) // if the data member of the object is not null pointer
		{
			os << rhs.message();
			return os;
		}

		return os;
	}

}

