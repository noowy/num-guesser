#ifndef PRESENTER_HPP
#define PRESENTER_HPP
#include "guesser.hpp"
#include "IView.hpp"
#include "UI.hpp"

class Presenter
{
private:
	IView *_view;

public:
	Presenter();
	void main_loop();
	void start_inquiry();
};

#endif