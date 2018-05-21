// Final Project Milestone 3
// ErrorState.h
// Version 1.0
// Date		2018-03-29
//
// Milestone 3
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Yuseon Kang	      2018-03-21	   To submit MS3
/////////////////////////////////////////////////////////////////

#ifndef AMA_ERRORSTATE_H
#define AMA_EERORSTATE_H
#include <iostream>

namespace AMA {

	class ErrorState {
	private:
		char *pErrMsg;
	public:
		explicit ErrorState(const char* = nullptr);
		ErrorState(const ErrorState&) = delete;
		ErrorState& operator=(const ErrorState&) = delete;
		virtual ~ErrorState();
		void clear();
		bool isClear() const;
		void message(const char*);
		const char* message()const;
	};
	std::ostream& operator<<(std::ostream&, ErrorState&);
}

#endif
