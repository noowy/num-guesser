#ifndef IVIEW_HPP
#define IVIEW_HPP
#include <string>

class IView
{
public:
	virtual void ask_question(std::string question) = 0;
	virtual bool get_answer() = 0;
};

#endif