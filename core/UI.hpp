#ifndef UI_HPP
#define UI_HPP
#include "IView.hpp"
#include <iostream>

class CLI : public IView
{
public:
	

	// Inherited via IView
	virtual void ask_question(std::string question) override;

	virtual bool get_answer() override;

};

#endif